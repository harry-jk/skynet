
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

#ifndef _SKYNET_SOCK_SOCK_H_
#define _SKYNET_SOCK_SOCK_H_

#include <memory>

#include <arpa/inet.h>
#include <sys/socket.h>
typedef int Socket;

#include "common/network_info.h"
#include "common/uncopyable.h"

namespace skynet {
namespace sock {
	/**
	 * Defualt Socket Interface 
	 */
	class Sock : private Uncopyable
	{
	public:
		Sock();
		// You must be construct NetworkInfo using 'new' 
		Sock(NetworkInfo* _info);
		// You must be construct sockaddr_in using 'new' 
		Sock(sockaddr_in* _addr);
		virtual ~Sock();
		inline Socket getSock(){ return m_sock; }
		virtual bool active() = 0;
		virtual bool inactive() = 0;
		bool closeSock();

	protected:
		bool setSock() {
			m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			return m_sock != -1;
		}
		inline void setSock(Socket _sock){ m_sock = _sock; }
		// You must be construct sockaddr_in using 'new' 
		inline void setAddr(sockaddr_in* _addr){ m_addr = std::unique_ptr<sockaddr_in>(_addr); }
		// You must be construct NetworkInfo using 'new'
		inline void setNetworkInfo(NetworkInfo* _info){ m_info = std::unique_ptr<NetworkInfo>(_info); }
		inline sockaddr_in* getAddr(){ return m_addr.get(); }

	private:
		Socket m_sock;
		std::unique_ptr<NetworkInfo> m_info;
		std::unique_ptr<sockaddr_in> m_addr;
	};
}
}

#endif
