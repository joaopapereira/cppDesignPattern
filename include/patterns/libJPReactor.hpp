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
#ifndef libJPReactor_H
#define libJPReactor_H
#include "patterns/reactor/EventHandler.hpp"
#include "patterns/reactor/Event.hpp"
#include "patterns/reactor/Handle.hpp"
#include <map>
#include <string>
#include <vector>
#include <exception>

namespace jpCppLibs{

	class Dispatcher{
	public:
		Dispatcher();
		int registerHandler(Event::EventType ev, EventHandler * handler);
		int unregisterHandler(Event::EventType ev, EventHandler * handler);
		int handleEventsLoop();
	private:
		typedef std::map<EventHandler*,std::vector<Event::EventType> > _EVENTHANDLERS;
		std::map<Handle*,int> handles;
		_EVENTHANDLERS eventHandlers;

	};

};
#endif
