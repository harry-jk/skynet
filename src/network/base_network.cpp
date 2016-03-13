
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

#include "network/base_network.h"

namespace skynet {
namespace network {
	BaseNetwork::BaseNetwork(std::shared_ptr<sock::Sock> _sock, BaseModel<struct BaseMessage>* _model, 
								const struct BaseConfig* _conf) 
		: m_sock(_sock), m_model(std::unique_ptr<BaseModel<struct BaseMessage>>(_model)), BUF_SIZE(_conf->buf_size)
	{
		setup();
	}	

	void BaseNetwork::start()
	{
		if(!__isStop && __isRunning) return;
		__isStop = false;
		if(!getSock()->active()){
			__isStop = true;
			return;	// TODO Exception
		}
		init();
		getModel()->start();
		m_core = std::thread(&BaseNetwork::__core, this);
	}

	void BaseNetwork::stop()
	{
		if(__isStop && !__isRunning) return;
		__isStop = true;
		if(m_core.joinable()) m_core.join();
		getSock()->inactive(); // TODO Exception
		close();
		getModel()->stop();
	}

	void BaseNetwork::wait()
	{
		if(__isWait || !__isRunning) return;
		__isWait = true;
	}

	void BaseNetwork::wake()
	{
		if(!__isWait || !__isRunning) return;
		__isWait = false;
		std::unique_lock<std::mutex> lock(__core_m);
		__core_wait.notify_one();
	}

	void BaseNetwork::__core_wait_check(std::unique_lock<std::mutex>* _lock)
	{
		if(__isWait) {
			__core_wait.wait(*_lock);
		}
	}

	void BaseNetwork::__core()
	{
		__isRunning = true;
		std::unique_lock<std::mutex> lock(__core_m);
		while(!__isStop) {
			__core_wait_check(&lock);
			__core_runable();
		}
		__isStop = true;
		__isRunning = false;
	}
}
}