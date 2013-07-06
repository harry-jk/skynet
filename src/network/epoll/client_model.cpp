
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

#include <string.h> 
#include <unistd.h> 

#include <sys/epoll.h>

#include "network/epoll/client_model.h"

namespace skynet {
namespace network {
namespace epoll {
	ClientModel::ClientModel(std::shared_ptr<sock::Connector> _sock, int _epoll, int _buf_size)
		: BaseModel::BaseModel(_sock, _buf_size), m_epoll(_epoll)
	{}

	ClientModel::~ClientModel()
	{}

	void ClientModel::start()
	{
		connect();
	}

	void ClientModel::stop()
	{
		disconect();
	}

	void ClientModel::recive(const struct EpollMessage* _msg)
	{
		char buf[BUF_SIZE];
		memset(buf, 0x00, BUF_SIZE);
		int readn = read(_msg->fd, buf, BUF_SIZE);
		if(readn <= 0) {
			epoll_ctl(m_epoll, EPOLL_CTL_DEL, _msg->fd, _msg->events);
		} else {
			// TODO Linking Pipeline
		}
	}

	void ClientModel::exception(const char* _exception)
	{
		// TODO Exception Event
	}
}
}
}