
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

#include "network/epoll/epoll_network.h"
#include "network/epoll/epoll_message.h"

namespace skynet {
namespace network {
namespace epoll {
	EpollNetwork::EpollNetwork(std::shared_ptr<sock::Sock> _sock, BaseModel<struct EpollMessage>* _model, 
								int _epoll, const struct EpollConfig* _conf)
		: EpollNetwork(_sock, _model, _conf, _conf->epoll_size, _epoll) 
	{}

	EpollNetwork::EpollNetwork(std::shared_ptr<sock::Sock> _sock, BaseModel<struct EpollMessage>* _model, 
								const struct BaseConfig* _conf, const int _epoll_size, int _epoll)
		: BaseNetwork<struct EpollMessage>(_sock, _model, _conf), EPOLL_SIZE(_epoll_size), m_epoll(_epoll) 
	{
		setup();
	}

	EpollNetwork::~EpollNetwork()
	{
		stop();
	}

	void EpollNetwork::setup()
	{
		m_events = (struct epoll_event*) malloc(sizeof(struct epoll_event)*EPOLL_SIZE);
		if(m_epoll != -1) return;
		
		int try_count = 0;
		do{
			m_epoll = epoll_create(EPOLL_SIZE);
		} while(m_epoll == -1 && ++try_count < 4);
	}

	void EpollNetwork::init()
	{
		struct epoll_event m_ev;
		int socket = getSock()->getSock();
		memset(&m_ev, 0x00, sizeof(struct epoll_event));
		m_ev.events = EPOLLIN;
		m_ev.data.ptr = new std::shared_ptr<sock::Sock>(getSockPtr());
		epoll_ctl(m_epoll, EPOLL_CTL_ADD, socket, &m_ev);
	}

	void EpollNetwork::close()
	{

	}

	void EpollNetwork::__core_runable()
	{
		if((__eventn = epoll_wait(m_epoll, m_events, EPOLL_SIZE, 100)) == -1) {
			getModel()->exception("[Network] Epoll Wait Exception");
			stop();
			return;
		}
		for(int i=0; i<__eventn; ++i) {
			struct EpollMessage* msg = new struct EpollMessage();
			msg->fd = static_cast<std::shared_ptr<sock::Sock>*>(m_events[i].data.ptr)->get()->getSock();
			struct epoll_event m_ev;
			msg->ctl = &m_ev;
			msg->ev = m_events[i];
			msg->events = m_events;
			getModel()->recive(msg);
		}
	}
}
}
}