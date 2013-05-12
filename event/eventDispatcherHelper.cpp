#include "cocos2d_mvc.h"

namespace cocos2d_mvc{
	EventDispatchHelper::EventDispatchHelper()
	:evtDispatcher(0){
		injector = Injector::getGlobalInjector();
	}
	void EventDispatchHelper::mapEventListener(Event *evt){
		if(evtDispatcher){
			evtDispatcher->addListener(evt);
		}else{
			EventDispatcher::getGlobalEvtDispatcher()->addListener(evt);
		}
	}
	void EventDispatchHelper::dispatch(Event * evt){
		if(evtDispatcher){
			evtDispatcher->addIncomingReq(evt);
		}else{
			EventDispatcher::getGlobalEvtDispatcher()->addIncomingReq(evt);
		}
	}
}