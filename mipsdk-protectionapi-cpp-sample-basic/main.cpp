﻿/**
*
* Copyright (c) Microsoft Corporation.
* All rights reserved.
*
* This code is licensed under the MIT License.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files(the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions :
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
*/

#include <cstdio>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>


#include "action.h"
#include "mip/common_types.h"
#include "utils.h"

using std::make_shared;
using std::shared_ptr;
using std::string;

using std::cout;
using std::cin;
using std::endl;

using sample::file::Action;

int main()
{
	// local variables to store target file and the label that will be applied to the file.
	
	string templateToApply;
	string plaintext;
	string ciphertext;
	string decryptedText;

	// Create the mip::ApplicationInfo object. 
	// Client ID should be the client ID registered in Azure AD for your custom application.
	// Friendly Name should be the name of the application as it should appear in reports.
	// Version should should be version number of the application you're writing. This data will show in logs. 
	mip::ApplicationInfo appInfo{ "YOUR CLIENT ID HERE", "YOUR APP NAME HERE", "YOUR APP VERSION HERE" };
	
	// All actions for this tutorial project are implemented in samples::file::Action
	// Source files are Action.h/cpp.
	// "File" was chosen because this example is specifically for the MIP SDK File API. 
	// Action's constructor takes in the mip::ApplicationInfo object and uses the client ID for auth.
	// Username and password are required in this sample as the oauth2 token is obtained via Python script and basic auth.
	Action action = Action(appInfo, "YOUR TEST USERNAME HERE","YOUR TEST USE PASSWORD HERE");

	while (true)
	{
		templateToApply = "";

		// Call action.ListLabels() to display all available labels, then pause.
		action.ListTemplates();
		system("pause");

		// Prompt the user to copy the Label ID from a displayed label. This will be stored
		// then applied later to a file.

		cout << "Copy a template ID from above to apply to a new string or q to quit." << endl;
		cout << endl << "Template ID: ";
		cin >> templateToApply;

		if (templateToApply == "q")
		{
			return 0;
		}

		auto publishingLicense = action.GetPublishingLicense(templateToApply);

		// Prompt the user to enter a file. A labeled copy of this file will be created.
		cout << "Enter some text to encrypt: ";
		std::getline(std::cin >> std::ws, plaintext);
		
		// Show action plan
		cout << "Applying Label ID " + templateToApply + " to: " << endl << plaintext << endl;

		action.ProtectString(plaintext, ciphertext, publishingLicense);

		cout << "Protected output: " << endl << ciphertext << endl;

		cout << endl << "Decrypting string: " << endl << endl;

		action.DecryptString(decryptedText, ciphertext, publishingLicense);

		cout << decryptedText << endl;

		system("pause");
	}
		
	return 0;
}


