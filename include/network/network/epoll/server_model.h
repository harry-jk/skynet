
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

#ifndef _SKYNET_NETWORK_EPOLL_SERVER_MODEL_H_
#define _SKYNET_NETWORK_EPOLL_SERVER_MODEL_H_

#include "network/network/base_model.h"
#include "network/network/epoll/epoll_message.h"
#include "sock/listener.h"

namespace skynet {
namespace network {
namespace epoll {
	class ServerModel : public BaseModel<struct EpollMessage>
	{
	public:
		ServerModel(std::shared_ptr<sock::Listener> _sock, int _epoll, int _buf_size);
		virtual ~ServerModel();
		virtual void start() override;
		virtual void stop() override;
		virtual void recive(const struct EpollMessage* _data) override;
		virtual void exception(const char* _exception) override;
	protected:
	private:
		void listen(const struct EpollMessage* _msg);
		void reciveMsg(const struct EpollMessage* _msg);

		int m_epoll;
	};
}
}
}

#endif