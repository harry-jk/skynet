
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

#ifndef _SKYNET_NETWORK_BASE_MODEL_H_
#define _SKYNET_NETWORK_BASE_MODEL_H_
#include "network/base_message.h"
#include "sock/sock.h"

namespace skynet {
namespace network {
	template<class MESSAGE=BaseMessage>
	class BaseModel
	{
	public:
		BaseModel(std::shared_ptr<sock::Sock> _sock, int _buf_size)
			: m_sock(_sock), BUF_SIZE(_buf_size)
		{};
		virtual ~BaseModel(){};
		virtual void start() = 0;
		virtual void stop() = 0;
		virtual void recive(const MESSAGE* _msg) = 0;
		// TODO change char to Exception 
		virtual void exception(const char* _exception) = 0;
		virtual void connect() final {
			// TODO Connect Event
			++COUNT;
		}
		virtual void disconect() final {
			// TODO Disconnect Event
			--COUNT;
		}
	protected:
		inline std::shared_ptr<sock::Sock> getSockPtr(){ return m_sock; }
		inline const sock::Sock* getSock(){ return m_sock.get(); }
		inline const Socket getSockFd(){ return m_sock.get()->getSock(); }

		const int BUF_SIZE;
		int COUNT;
	private:
		std::shared_ptr<sock::Sock> m_sock;
	};
}
}

#endif