
/*
	Copyright 2013 Skynet Project

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	    http://www.apache.org/licenses/LICENSE-	2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

#include <iostream>
#include "common/network_info.h"

using namespace std;
using namespace skynet;

void printCase(NetworkInfo info, char* num);

int main(int argc, char const *argv[])
{
	cout << "network info test case" << endl;
	printCase(NetworkInfo("127.0.0.1", 80), "0");
	return 0;
}

void printCase(NetworkInfo info, char* num)
{
	cout << "case" << num << ": ";
	cout << info.addr << ", ";
	cout << info.port << endl;
}