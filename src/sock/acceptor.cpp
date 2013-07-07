
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

#include "sock/acceptor.h"

namespace skynet {
namespace sock {
	const bool Acceptor::active()
	{
		const struct sockaddr_in* _addr = getAddr();
		socklen_t len = sizeof(struct sockaddr);
		setSock(accept(m_listen, (struct sockaddr*) _addr, &len));
		return getSock() != -1;
	}

	const bool Acceptor::inactive()
	{
		return closeSock();
	}
}
}