
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

#ifndef _SKYNET_SERVICE_SERVER_H_
#define _SKYNET_SERVICE_SERVER_H_

#include "service/service.h"

namespace skynet {
	class Client : public Service
	{
	public:
		inline bool start(){ return connect(); }
		inline bool stop(){ return disconnect(); }
		inline bool clear(){
			if(stop()){
				return close();
			}
			return false;
		}
		bool connect();
		bool disconnect();
		bool sendMsg(const char* _msg);
	protected:
		bool close();
	private:
	};
}

#endif