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
#include "patterns/libJPReactor.hpp"


#include <iostream>
#include <algorithm>
#include <libJPLogger.hpp>

using namespace jpCppLibs;

Dispatcher::Dispatcher(){
}

int Dispatcher::registerHandler(Event::EventType ev, EventHandler * handler){

	if( eventHandlers.find(handler) == eventHandlers.end() ){
		std::vector<Event::EventType> events;
		events.push_back(ev);
		eventHandlers[handler] = events;
	}else
		eventHandlers[handler].push_back(ev);

	if( handles.find(handler->getHandle()) == handles.end())
		this->handles[handler->getHandle()] = 1;
	else
		this->handles[handler->getHandle()]++;

	return 0;
}

int Dispatcher::unregisterHandler(Event::EventType ev, EventHandler * handler){

	if( eventHandlers.find(handler) == eventHandlers.end() ){
		std::vector<Event::EventType>::iterator it = std::find(eventHandlers[handler].begin(), eventHandlers[handler].end(), ev);
		if (it != eventHandlers[handler].end()) // == vector.end() means the element was not found
			eventHandlers[handler].erase(it);
		if( eventHandlers[handler].size() == 0 )
			eventHandlers.erase(handler);
	}
	if( 1 == handles[handler->getHandle()] )
		handles.erase(handler->getHandle());


	return 0;
}

int Dispatcher::handleEventsLoop(){
	std::map<Handle*,int>::iterator it;
	for( it = handles.begin(); it != handles.end() ; it++ ){
		//Event::EventType ev = demuxEvents(it->first);
		Event::EventType ev = it->first->getEvent();
		for( _EVENTHANDLERS::iterator evH = eventHandlers.begin();
				evH != eventHandlers.end();
				evH++){
			std::vector<Event::EventType>::iterator it = std::find(evH->second.begin(), evH->second.end(), ev);
			if (it != evH->second.end()) {
				int result = evH->first->eventHandler(ev);
				if( result < 0 ){
					evH->first->close();
					delete evH->first;
				}
			}
		}
	}
	return 0;
}
