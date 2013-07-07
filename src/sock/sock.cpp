
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
#include <unistd.h>

#include "sock/sock.h"

namespace skynet {
namespace sock {
	Sock::Sock() :
		m_sock(-1),
		m_addr(nullptr)
	{}

	Sock::Sock(struct NetworkInfo* _info) :
		m_sock(-1),
		m_addr(nullptr)
	{
		struct sockaddr_in* _addr = new struct sockaddr_in();
		_addr->sin_family = AF_INET;
		if(_info->addr == nullptr) {
			_addr->sin_addr.s_addr = htonl(INADDR_ANY);
		} else{
			_addr->sin_addr.s_addr = inet_addr(_info->addr);
		}
		_addr->sin_port = htons(_info->port);
		setNetworkInfo(_info);
		setAddr(_addr);
	}

	Sock::Sock(struct sockaddr_in* _addr) :
		m_sock(-1),
		m_addr(std::unique_ptr<struct sockaddr_in>(_addr))
	{}

	Sock::~Sock()
	{
		closeSock();
		if(m_addr != nullptr){
			m_addr.reset();
			m_addr = nullptr;
		}
	}

	const bool Sock::closeSock()
	{
		if(m_sock == -1) return true;
		return close(m_sock) == 0; 
	}
}
}