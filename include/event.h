#ifndef __COCOS2D_EVENT_H__
#define __COCOS2D_EVENT_H__

#include "cocos2d_mvc.h"

namespace cocos2d_mvc{
	class EventDispatcher;
	class Event:public CCObject{
		EEE(Event)
		ECC(Event)
		bool needClean;//表示data是否需要清理
	public:
		enum{
			EVENT_PRIORITY_LOWEST,
			EVENT_PRIORITY_LOW,
			EVENT_PRIORITY_DEFAULT,
			EVENT_PRIORITY_MID,
			EVENT_PRIORITY_HIGH,
			EVENT_PRIORITY_HIGHEST,
		};
		bool operator<(const Event & evt);
		EventDispatcher* dispatcher;
		string evt;
		EventDispatchHelper* target;
		EVT_CALLBACK func;
		CCObject * data;
		int priority;
		Event(EventDispatcher* dispatcher, string evt, EventDispatchHelper* target, EVT_CALLBACK func, CCObject * data, bool needClean = true, int priority = EVENT_PRIORITY_DEFAULT);
		virtual ~Event();
		//INIT_FOR_CREATE_FUNC();
		//CREATE_FUNC(Event);
	};
}

#endif