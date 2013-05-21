/**
 ============================================================================
 Name        : exampleProgram.c
 Author      : Joao Pereira
 Version     :
 Copyright   : This library is creating under the ASF License Version 2.0
 Description : Uses shared library to print greeting
               To run the resulting executable the LD_LIBRARY_PATH must be
               set to ${project_loc}/libJPReactor/.libs
               Alternatively, libtool creates a wrapper shell script in the
               build directory of this program which can be used to run it.
               Here the script will be called exampleProgram.
 ============================================================================
 */
#include "libJPLogger.hpp"
#include "patterns/libJPReactor.hpp"
#include <unistd.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace jpCppLibs;

Dispatcher disp;

class QueueEvents: public Event{
public:
	enum EventType{
		FULL = Event::__LAST,
		EMPTY,
		NEW_VALUE,
		__LAST_QUEUE
	};
};
class Queue: public Handle{
public:
	Queue(int max){
		this->max = max;
		newValues = 0;
	}
	~Queue(){
	}
	int put( char  value){
		if( queue.size() ==max )
			return -1;
		if( value <= 0 )
			return -2;
		queue.push_back(value);
		newValues++;
		return 0;
	}
	char get(){
		if(queue.empty() )
			return -1;
		newValues--;
		char c = queue.back();
		queue.pop_back();
		return c;
	}
	Event::EventType getEvent(){
		if( newValues > 0 )
			return (Event::EventType)QueueEvents::NEW_VALUE;
		if( queue.size() == max )
			return (Event::EventType)QueueEvents::FULL;
		if(queue.size() == 0 )
			return (Event::EventType)QueueEvents::EMPTY;
		return (Event::EventType)QueueEvents::NOTHING;
	}

private:
	std::vector<char> queue;
	int max;
	int newValues;
};

namespace jpCppLibs{
template<>
Event::EventType demuxEvents<Queue>(Queue * v){
	return v->getEvent();
}
}

class Feeder: public EventHandler{
public:
	Feeder( Queue *q) {
		this->handle = q;
		disp.registerHandler((Event::EventType)QueueEvents::EMPTY,this);
		disp.registerHandler((Event::EventType)QueueEvents::FULL,this);
		disp.registerHandler((Event::EventType)QueueEvents::END,this);
	}
	~Feeder(){

	}
	int eventHandler(Event::EventType ev){
		if( ev == QueueEvents::FULL ){
			sleep(1);
			return 1;
		}else if( ev == QueueEvents::EMPTY ){
			int n = rand() % 26;
			char c = (char)(n+65);
			OneInstanceLogger::instance()->log("Feeder",M_LOG_NRM,M_LOG_DBG,"will add char %c",c);
			((Queue*)this->handle)->put(c);
			return 0;
		}else if( ev == QueueEvents::END ){
			return -1;
		}
		return 0;
	}
	int close(){
		disp.unregisterHandler((Event::EventType)QueueEvents::EMPTY,this);
		disp.unregisterHandler((Event::EventType)QueueEvents::FULL,this);
		disp.unregisterHandler((Event::EventType)QueueEvents::END,this);
		return 0;
	}
};
class Eater: public EventHandler{
public:
	Eater( Queue *q, std::string name) {
		this->handle = q;
		disp.registerHandler((Event::EventType)QueueEvents::EMPTY,this);
		disp.registerHandler((Event::EventType)QueueEvents::FULL,this);
		disp.registerHandler((Event::EventType)QueueEvents::NEW_VALUE,this);
		disp.registerHandler((Event::EventType)QueueEvents::END,this);
		this->name = name;
	}
	~Eater(){

	}
	int eventHandler(Event::EventType ev){
		if( ev ==  QueueEvents::NEW_VALUE ||
			ev == QueueEvents::FULL ){

			char c = ((Queue*)this->handle)->get();
			if( c == -1)
				OneInstanceLogger::instance()->log("Eater",M_LOG_NRM,M_LOG_DBG,"Nothing to eat by %s",name.c_str());
			else
				OneInstanceLogger::instance()->log("Eater",M_LOG_NRM,M_LOG_DBG,"Retrieved char %c , %s",c,name.c_str());
		}else if( ev == QueueEvents::EMPTY ){
			sleep(1);
			return 1;
		}else if( ev == QueueEvents::END ){
			return -1;
		}
		return 0;
	}
	int close(){
		disp.unregisterHandler((Event::EventType)QueueEvents::EMPTY,this);
		disp.unregisterHandler((Event::EventType)QueueEvents::FULL,this);
		disp.unregisterHandler((Event::EventType)QueueEvents::NEW_VALUE,this);
		disp.unregisterHandler((Event::EventType)QueueEvents::END,this);
		return 0;
	}
private:
	std::string name;
};


int main(void) {
  Logger log("/tmp/test.log");
  log.setLogLvl("REA", M_LOG_MIN , M_LOG_ALLLVL);
  log.setLogLvl("Eater", M_LOG_MIN , M_LOG_ALLLVL);
  log.setLogLvl("Feeder", M_LOG_MIN , M_LOG_ALLLVL);
  OneInstanceLogger::instance()->copyLoggerDef(&log);
  Queue queue(10);

  Eater eater( &queue , "eater1");
  Eater eater1( &queue, "eater2" );
  Feeder feeder( &queue );
  for( int i = 0 ; i < 10; i++)
	  disp.handleEventsLoop();

  OneInstanceLogger::instance()->log("Ended APP","REA",M_LOG_NRM,M_LOG_DBG);
  return 0;
}
