#include "cocos2d_mvc.h"

namespace cocos2d_mvc{
	Event::Event(EventDispatcher* dispatcher, string evt, EventDispatchHelper* target, EVT_CALLBACK func, CCObject * data, bool needClean, int priority)
		:dispatcher(dispatcher)
		,evt(evt)
		,target(target)
		,func(func)
		,data(data)
		,needClean(needClean)
		,priority(priority)
	{
		CC_SAFE_RETAIN(data);
	}
	bool Event::operator<(const Event & evt){
		return this->priority < evt.priority;
	}
	Event::~Event(){
		if(needClean && data != 0){
			CC_SAFE_RELEASE(data);
		}
	}
}