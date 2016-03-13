
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

#ifndef _SKYNET_SERVICE_NETWORK_H_
#define _SKYNET_SERVICE_NETWORK_H_

#include "common/uncopyable.h"
#include "sock/sock.h"

namespace skynet {
	class Service : private Uncopyable
	{
	public:
		Service();
		virtual ~Service();
		virtual inline bool start() = 0;
		virtual inline bool stop() = 0;
		virtual inline bool clear() = 0;
		virtual bool send(const char* _msg) = 0;
	protected:
		virtual bool close();
		inline Socket getSock(){ return m_sock; }
	private:
		Sock m_sock;
	};
}

#endif