
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

#include "pipeline/pipeline.h"

namespace skynet {
namespace network {
namespace pipeline {
	Pipeline::Pipeline()
	{}
	
	Pipeline::~Pipeline()
	{}

	void Pipeline::add(Stage& _stage) final
	{
		addLast(TYPE::COMMON, _stage);	
	}
	
	bool Pipeline::add(int _index, Stage& _stage) final
	{
		return add(TYPE::COMMON, _index, _stage);	
	}

	void Pipeline::add(TYPE _type, Stage& _stage) final
	{
		addLast(_type, _stage);
	}

	bool Pipeline::add(TYPE _type, int _index, Stage& _stage) final
	{
		std::list<Stage> pipe;
		switch(_type){
		case INBOUND :
			pipe = m_in;
			break;
		case OUTBOUND :
			pipe = m_out;
			break;
		case COMMON :
			pipe = m_common;
			break;
		default :
			return false; // TYPE ERROR
		}
		if(pipe.size() <= _index) return false;
		std::list<Stage>iterator pos;
		pos = pipe.begin();
		for(int i=0; i<_index; ++i) ++pos;
		pipe.insert(pos, _stage);
		return true; 
	}
	
	void Pipeline::addFirst(Stage& _stage) final
	{
		addFirst(TYPE::COMMON, _stage);	
	}
	
	void Pipeline::addLast(Stage& _stage) final
	{
		addLast(TYPE::COMMON, _stage);
	}

	void Pipeline::addFirst(TYPE _type, Stage& _stage) final
	{
		switch(_type){
		case INBOUND :
			m_in.push_front(_stage);
			break;
		case OUTBOUND :
			m_out.push_front(_stage);
			break;
		case COMMON :
			m_common.push_front(_stage);
			break;
		}
	}

	void Pipeline::addLast(TYPE _type, Stage& _stage) final
	{
		switch(_type){
		case INBOUND :
			m_in.push_back(_stage);
			break;
		case OUTBOUND :
			m_out.push_back(_stage);
			break;
		case COMMON :
			m_common.push_back(_stage);
			break;
		}
	}
	
	bool Pipeline::remove(Stage& _stage) final
	{
		return remove(TYPE::COMMON, _stage);
	}
	
	bool Pipeline::remove(int _index) final
	{
		return remove(TYPE::COMMON, _index);
	}
	
	bool Pipeline::remove(TYPE _type, Stage& _stage) final
	{
		switch(_type){
		case INBOUND :
			break;
		case OUTBOUND :
			break;
		case COMMON :
			break;
		default :
			return false; // TYPE ERROR
		}
	}

	bool Pipeline::remove(TYPE _type, int _index) final
	{
		switch(_type){
		case INBOUND :
			break;
		case OUTBOUND :
			break;
		case COMMON :
			break;
		default :
			return false; // TYPE ERROR
		}
	}

	void Pipeline::removeFirst() final
	{
		removeFirst(TYPE::COMMON);
	}
	
	void Pipeline::removeLast() final
	{
		removeLast(TYPE::COMMON);
	}

	void Pipeline::removeFirst(TYPE _type) final
	{
		switch(_type){
		case INBOUND :
			break;
		case OUTBOUND :
			break;
		case COMMON :
			break;
		}
	}

	void Pipeline::removeLast(TYPE _type) final
	{
		switch(_type){
		case INBOUND :
			break;
		case OUTBOUND :
			break;
		case COMMON :
			break;
		}
	}
	
	void Pipeline::setPipeline(std::list<Stage> _pipeline) final
	{
		setPipeline(TYPE::COMMON, _pipeline);
	}

	void Pipeline::setPipeline(TYPE _type, std::list<Stage> _pipe) final
	{
		switch(_type){
		case INBOUND :
			break;
		case OUTBOUND :
			break;
		case COMMON :
			break;
		}
	}
	
	void Pipeline::clear() final
	{
		m_in.clear();
		m_out.clear();
		m_common.clear();
	}

	void Pipeline::clear(TYPE _type) final
	{
		switch(_type) {
		case INBOUND :
			m_in.clear();
			break;
		case OUTBOUND :
			m_out.clear();
			break;
		case COMMON :
			m_common.clear();
			break;
		}
	}
	
	void Pipeline::send(std::string& _msg) final
	{}
	
	void Pipeline::recive(std::string& _msg) final
	{}
}
}
}