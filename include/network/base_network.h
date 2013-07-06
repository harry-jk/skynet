
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

#ifndef _SKYNET_NETWORK_BASE_NETWORK_H_
#define _SKYNET_NETWORK_BASE_NETWORK_H_

#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>

#include "common/uncopyable.h"
#include "network/base_model.h"
#include "network/base_config.h"
#include "sock/sock.h"

namespace skynet {
namespace network {
	template<class MESSAGE=BaseMessage>
	class BaseNetwork : private Uncopyable
	{
	public:
		BaseNetwork(std::shared_ptr<sock::Sock> _sock, BaseModel<MESSAGE>* _model, 
						const struct BaseConfig* _conf)
			: m_sock(_sock), m_model(std::unique_ptr<BaseModel<MESSAGE>>(_model)), 
				BUF_SIZE(_conf->buf_size)
		{}	
		virtual ~BaseNetwork(){};
		virtual void start() final;
		virtual void stop() final;
		virtual void wait() final;
		virtual void wake() final;

		inline const bool isRunning() { return __isRunning; }
		inline const bool isStop() { return __isStop; }
	protected:
		// invoke constructor
		virtual void setup() = 0;
		// invoke start
		virtual void init() = 0;
		// invoke stop
		virtual void close() = 0;
		
		virtual void __core_runable() = 0;
		
		inline std::shared_ptr<sock::Sock> getSockPtr(){ return m_sock; }
		inline sock::Sock* getSock(){ return m_sock.get(); }
		inline BaseModel<MESSAGE>* getModel(){ return m_model.get(); }
		inline const Socket getSockFd(){ return m_sock.get()->getSock(); }

		const int BUF_SIZE;
	private:
		virtual void __core_wait_check(std::unique_lock<std::mutex>* _lock) final;
		virtual void __core() final;

		std::shared_ptr<sock::Sock> m_sock;
		std::unique_ptr<BaseModel<MESSAGE>> m_model;

		// Main Core Thread
		std::thread m_core;
		std::mutex __core_m;
		std::condition_variable __core_wait;
		bool __isRunning = false;
		bool __isWait = false;
		bool __isStop = true;
	};

	template<class MESSAGE>
	void BaseNetwork<MESSAGE>::start()
	{
		if(!__isStop && __isRunning) return;
		__isStop = false;
		__isWait = false;
		if(!getSock()->active()){
			__isStop = true;
			return;	// TODO Exception
		}
		init();
		getModel()->start();
		m_core = std::thread(&BaseNetwork::__core, this);
	}

	template<class MESSAGE>
	void BaseNetwork<MESSAGE>::stop()
	{
		if(__isStop && !__isRunning) return;
		__isStop = true;
		__isWait = false;
		if(m_core.joinable()){
			m_core.join();
		} 
		getSock()->inactive(); // TODO Exception
		close();
		getModel()->stop();
	}

	template<class MESSAGE>
	void BaseNetwork<MESSAGE>::wait()
	{
		if(__isWait || !__isRunning) return;
		__isWait = true;
	}

	template<class MESSAGE>
	void BaseNetwork<MESSAGE>::wake()
	{
		if(!__isWait || !__isRunning) return;
		__isWait = false;
		std::unique_lock<std::mutex> lock(__core_m);
		__core_wait.notify_one();
	}

	template<class MESSAGE>
	void BaseNetwork<MESSAGE>::__core_wait_check(std::unique_lock<std::mutex>* _lock)
	{
		if(__isWait) {
			__core_wait.wait(*_lock);
		}
	}

	template<class MESSAGE>
	void BaseNetwork<MESSAGE>::__core()
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

#endif