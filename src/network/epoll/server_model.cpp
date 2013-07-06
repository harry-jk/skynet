
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

#include "network/epoll/server_model.h"
#include "sock/acceptor.h"

namespace skynet {
namespace network {
namespace epoll {
	ServerModel::ServerModel(std::shared_ptr<sock::Listener> _sock, int _epoll, int _buf_size)
		: BaseModel::BaseModel(_sock, _buf_size), m_epoll(_epoll)
	{}

	ServerModel::~ServerModel()
	{}

	void ServerModel::start()
	{
		COUNT = 0;
		// TODO Start Event
	}

	void ServerModel::stop()
	{
		COUNT = 0;
		// TODO Stop Event
	}

	void ServerModel::recive(const struct EpollMessage* _msg)
	{
		if(_msg->fd == getSockFd()) {
			listen(_msg);
		} else {
			reciveMsg(_msg);
		}
	}

	void ServerModel::exception(const char* _exception)
	{
		// TODO Exception Event
	}

	void ServerModel::listen(const struct EpollMessage* _msg)
	{
		sock::Acceptor* client = new sock::Acceptor(getSockFd(), new struct sockaddr_in()); 
		client->active();
		int socket = client->getSock();
		memset(_msg->ctl, 0x00, sizeof(struct epoll_event));
		_msg->ctl->events = EPOLLIN;
		_msg->ctl->data.ptr = new std::shared_ptr<sock::Sock>(client);
		epoll_ctl(m_epoll, EPOLL_CTL_ADD, socket, _msg->ctl);
		connect();
	}

	void ServerModel::reciveMsg(const struct EpollMessage* _msg)
	{
		char buf[BUF_SIZE];
		memset(buf, 0x00, BUF_SIZE);
		int readn = read(_msg->fd, buf, BUF_SIZE);
		if(readn <= 0) {
			epoll_ctl(m_epoll, EPOLL_CTL_DEL, _msg->fd, _msg->events);
			std::shared_ptr<sock::Sock>* client = static_cast<std::shared_ptr<sock::Sock>*>(_msg->ev.data.ptr);
			client->get()->inactive();
			delete client;
			disconect();
		} else {
			// TODO Linking Pipeline
			std::cout << "Read Msg: " << buf << std::endl;
		}
	}
}
}
}