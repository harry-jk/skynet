
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

#ifndef _SKYNET_MANAGER_NETWORK_BOOTSTRAP_H_
#define _SKYNET_MANAGER_NETWORK_BOOTSTRAP_H_

#include <memory>

#include "common/uncopyable.h"
#include "common/network_info.h"
#include "factory/network_factory.h"
#include "service/service.h"

namespace skynet {
namespace bootstrap {
	class ServiceBootstrap : private Uncopyable
	{
	public:
		ServiceBootstrap(NetworkFactory* _factory, DefaultHandler* _handler);
		virtual ~ServiceBootstrap();
		virtual Service* build() = 0;
		virtual void setPipeline();
		virtual void addPipe();

	protected:

	private:
		std::unique_ptr<NetworkFactory> m_factory;
		std::unique_ptr<DefaultHandler> m_handler;
	};
}
}

#endif