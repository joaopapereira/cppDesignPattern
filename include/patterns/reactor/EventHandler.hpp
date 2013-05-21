/**
       Licensed to the Apache Software Foundation (ASF) under one
       or more contributor license agreements.  See the NOTICE file
       distributed with this work for additional information
       regarding copyright ownership.  The ASF licenses this file
       to you under the Apache License, Version 2.0 (the
       "License"); you may not use this file except in compliance
       with the License.  You may obtain a copy of the License at

         http://www.apache.org/licenses/LICENSE-2.0

       Unless required by applicable law or agreed to in writing,
       software distributed under the License is distributed on an
       "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
       KIND, either express or implied.  See the License for the
       specific language governing permissions and limitations
       under the License.
 */
#ifndef libJPEventHandler_H
#define libJPEventHandler_H
#include "patterns/reactor/Event.hpp"
#include "patterns/reactor/Handle.hpp"
#include <map>
#include <string>
#include <vector>
#include <exception>

namespace jpCppLibs{
	/**
	 * Class used to implement a unique counter
	 * for the identifier of the semaphores
	 */
	class EventHandler{
	public:
		EventHandler(){handle = NULL;}
		/**
		 * Handle a specific event
		 * @param ev Event that need to be handled
		 */
		int virtual eventHandler( Event::EventType ev ) = 0;

		/**
		 * Retrieve the handle this event has
		 * @return HANDLE
		 */
		Handle * getHandle(){ return handle ;}

		void setHandle( Handle * h){ handle = h ;}

		int virtual close() = 0;

		virtual ~EventHandler(){};

	protected:
		/**
		 * Actual value of the identifier
		 */
		Handle * handle;
	};

}
#endif
