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
#ifndef libJPEvent_H
#define libJPEvent_H

namespace jpCppLibs{
	/**
	 * Class that creates 
	 * 
	 */
	class Event{
	public:
		/**
		 * Event type
		 */
		enum EventType{
			NOTHING = 0,
			END,
			__LAST
		};
		/**
		 * Comparation operator
		 * @param ev Event to compare with
		 * @return Boolean
		 */
		bool operator==(Event ev){ return this->event == ev.event;}
		/**
		 * Assignment operator operator
		 * @param ev Event to assign 
		 */
		void operator=(Event ev){ this->event = ev.event;}
		/**
		 * Type convertion
		 * @return Event type
		 */
		operator Event::EventType() { return (EventType)event; }
	private:
		/**
		 * Event 
		 */
		int event;
	};

};
#endif
/* vim:set tabstop=3 expandtab: */
