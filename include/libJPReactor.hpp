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
#include <map>
#include <string>
#include <vector>
#include <exception>

namespace jpCppLibs{



	class Event{
	public:
		enum EventType{
			NOTHING = 0,
			END,
			__LAST
		};
		bool operator==(Event ev){ return this->event == ev.event;}
		void operator=(Event ev){ this->event = ev.event;}
		operator Event::EventType() { return (EventType)event; }
	private:
		int event;
	};

	class Handle{
	public:
		Event::EventType virtual getEvent() = 0;
	};
	template<class T>
	Event::EventType demuxEvents(T *v);

	/**template<>
	Event::EventType demuxEvents<Handle>(Handle * v){
		throw std::string("This method need to be implemented for the handle");
	}**/



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
