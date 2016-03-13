
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

#include "sock/binder.h"
#include "sock/listener.h"
#include "sock/connector.h"
#include "sock/acceptor.h"

using namespace std;
using namespace skynet::sock;

int main(int argc, char const *argv[])
{
	Binder binder(new skynet::NetworkInfo(nullptr, 8888));
	cout << "Binder Active : " << binder.active() << endl; 
	cout << "Binder Socket : " << binder.getSock() << endl;
	Listener listener(new skynet::NetworkInfo(nullptr, 2000));
	cout << "Listener Active : " << listener.active() << endl;
	cout << "Listener Socket : " << listener.getSock() << endl;
	Connector connector(new skynet::NetworkInfo("127.0.0.1", 2000));
	cout << "Connector Active : " << connector.active() << endl;
	cout << "Connector Socket : " << connector.getSock() << endl;
	Acceptor acceptor(listener.getSock(), new sockaddr_in());
	cout << "Acceptor Active : " << acceptor.active() << endl;
	cout << "Acceptor Socket : " << acceptor.getSock() << endl;

	cout << endl;
	cout << "Binder Inactive : " << binder.inactive() << endl;
	cout << "Connector Inactive : " << connector.inactive() << endl;
	cout << "Acceptor Inactive : " << acceptor.inactive() << endl;
	cout << "Listener Inactive : " << listener.inactive() << endl;
	cout << endl;
	return 0;
}