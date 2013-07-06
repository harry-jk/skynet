
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

#ifndef _SKYNET_NETWORK_EPOLL_EPOLL_NETWORK_H_
#define _SKYNET_NETWORK_EPOLL_EPOLL_NETWORK_H_

#include <sys/epoll.h>

#include "network/base_network.h"
#include "network/epoll/epoll_config.h"
#include "network/epoll/epoll_message.h"

namespace skynet {
namespace network {
namespace epoll {
	class EpollNetwork : public BaseNetwork<struct EpollMessage>
	{
	public:
		EpollNetwork(std::shared_ptr<sock::Sock> _sock, BaseModel<struct EpollMessage>* _model, 
						int _epoll, const struct EpollConfig* _conf);
		
		~EpollNetwork();
		
	protected:
		void setup() override;
		void init() override;
		void close() override;
		void __core_runable() override;
	private:
		EpollNetwork(std::shared_ptr<sock::Sock> _sock, BaseModel<struct EpollMessage>* _model, 
						const struct BaseConfig* _conf, const int _epoll_size, int _epoll);

		int m_epoll;
		struct epoll_event* m_events;
		
		// using __core_runable
		int __eventn;

		const int EPOLL_SIZE;
	};
}
}
}

#endif