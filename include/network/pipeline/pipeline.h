
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

#ifndef _SKYNET_PIPELINE_PIPELINE_H_
#define _SKYNET_PIPELINE_PIPELINE_H_

#include <list>
#include <string>

#include "network/base_message.h"
#include "network/pipeline/stage.h"

namespace skynet {
namespace network {
namespace pipeline {
	enum class TYPE { INBOUND, OUTBOUND, COMMON };

	class Pipeline
	{
	public:
		Pipeline();
		virtual ~Pipeline();
		virtual void add(Stage& _stage) final;
		virtual bool add(int _index, Stage& _stage) final;
		virtual void add(TYPE _type, Stage& _stage) final;
		virtual bool add(TYPE _type, int _index, Stage& _stage) final;
		virtual void addFirst(Stage& _stage) final;
		virtual void addLast(Stage& _stage) final;
		virtual void addFirst(TYPE _type, Stage& _stage) final;
		virtual void addLast(TYPE _type, Stage& _stage) final;
		virtual bool remove(Stage& _stage) final;
		virtual bool remove(int _index) final;
		virtual bool remove(TYPE _type, Stage& _stage) final;
		virtual bool remove(TYPE _type, int _index) final;
		virtual void removeFirst() final;
		virtual void removeLast() final;
		virtual void removeFirst(TYPE _type) final;
		virtual void removeLast(TYPE _type) final;
		virtual void setPipeline(std::list<Stage> _pipe) final;
		virtual void setPipeline(TYPE _type, std::list<Stage> _pipe) final;
		virtual void clear() final;
		virtual void clear(TYPE _type) final;
		virtual void send(std::string& _msg) final;
		virtual void recive(BaseMessage& _msg) final;
	protected:
	private:

		// Pipeline 
		// INBOUND (Recv)  : m_in -> m_common
		// OUTBOUNT (Send) : m_out -> revers m_common
		std::list<Stage> m_in;
		std::list<Stage> m_out;
		std::list<Stage> m_common;
	};
}
}
}

#endif