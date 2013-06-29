
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

#ifndef _SKYNET_SOCK_ACCEPTOR_H_
#define _SKYNET_SOCK_ACCEPTOR_H_

#include "sock/sock.h"

namespace skynet {
namespace sock {
	class Acceptor : public Sock
	{
	public:
		Acceptor() : Sock() {}
		Acceptor(NetworkInfo* _info) : Sock(_info) {}
		Acceptor(sockaddr_in* _addr) : Sock(_addr) {}
		Acceptor(Socket _sock, sockaddr_in* _addr) : Sock(_addr), m_listen(_sock) {}
		bool active() override;
		bool inactive() override;
	protected:
	private:
		Socket m_listen;
	};
}
}

#endif