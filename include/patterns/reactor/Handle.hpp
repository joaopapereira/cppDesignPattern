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
#ifndef libJPHandle_H
#define libJPHandle_H
#include "patterns/reactor/Event.hpp"

namespace jpCppLibs{
	/**
	 * This class represents an handled object. 
	 * Should be inherited by all the resources that need to be handled by the Reactor
	 */
	class Handle{
	public:
		/**
		 * Method to check for any event that could have happened in this handled 
		 * resource
		 * @return Event that ocurred in the handled resource
		 */
		Event::EventType virtual getEvent() = 0;
	};
	template<class T>
	Event::EventType demuxEvents(T * v){return Event::NOTHING;};

};
#endif
