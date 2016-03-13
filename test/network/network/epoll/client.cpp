
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
#include <chrono>

#include "common/network_info.h"

#include "network/network/epoll/epoll_config.h"
#include "network/network/epoll/epoll_network.h"
#include "network/network/epoll/client_model.h"

#include "sock/listener.h"

using namespace std;
using namespace skynet::sock;
using namespace skynet::network::epoll;

bool isStop;

void sendMsg(Socket sock){
	string buf("Test");
	while(!isStop){
		if(send(sock, buf.c_str(), buf.length(), 0) <= 0){
			cout << "Fail Send" << endl;
		}
	}
}

int main(int argc, char const *argv[])
{
	std::shared_ptr<Connector> connector 
		= std::shared_ptr<Connector>(new Connector(new skynet::NetworkInfo("117.17.102.20", 2000)));

	struct EpollConfig* conf = new struct EpollConfig();
	conf->epoll_size = 1000;
	conf->buf_size = 100;

	int try_count = 0;
	int epoll = -1;
	do{
		epoll = epoll_create(conf->epoll_size);
	} while(epoll == -1 && ++try_count < 4);

	EpollNetwork* client = new EpollNetwork(connector, new ClientModel(connector, epoll, conf->buf_size), 
												epoll, conf);
	cout << "End Setup" << endl;
	client->start();
	isStop = false;
	std::thread t(sendMsg, connector.get()->getSock()); 
	std::chrono::seconds dura(10);
	cout << "Sleep" << endl;
	std::this_thread::sleep_for(dura);
	cout << "End Sleep" << endl;
	isStop = true;
	t.join();
	client->stop();
	cout << "Exit" << endl;
	return 0;
}