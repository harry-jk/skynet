
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
#include "sock/binder.h"

namespace skynet {
namespace sock {
	bool Binder::active()
	{
		setSock();
		int _sock = getSock();
		sockaddr_in* _addr = getAddr();
		socklen_t len = sizeof(*_addr);
		int isBind = bind(_sock, (struct sockaddr*) _addr, len);
		return isBind != -1;
	}

	bool Binder::inactive()
	{
		return closeSock();
	}
}
}