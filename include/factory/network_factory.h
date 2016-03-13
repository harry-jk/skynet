
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

#ifndef _SKYNET_FACTORY_NETWORK_FACTORY_H_
#define _SKYNET_FACTORY_NETWORK_FACTORY_H_

#include <memory>

#include "common/uncopyable.h"
#include "common/network_info.h"
#include "controller/network_controller.h"
#include "factory/option.h"
#include "sock/sock.h"

namespace skynet {
namespace factory {
	class NetworkFactory : private Uncopyable
	{
	public:
		NetworkFactory(Option* _option);
		virtual ~NetworkFactory();
		virtual BaseNetwork* build() = 0;

	protected:

	private:
		std::shared_ptr<BaseNetwork> m_network;
		std::unique_ptr<Option> m_option;
	};
}
}

#endif	