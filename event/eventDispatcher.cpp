#include "cocos2d_mvc.h"

namespace cocos2d_mvc{
	EventDispatcher* EventDispatcher::globalDispatcher = EventDispatcher::create();
	EventDispatcher::EventDispatcher(){
		listeningEvts = CCDictionary::create();
		CC_SAFE_RETAIN(listeningEvts);
		incomingReqEvts = CCDictionary::create();
		CC_SAFE_RETAIN(incomingReqEvts);

		schedule(schedule_selector(EventDispatcher::onUpdate));
	}
	EventDispatcher *EventDispatcher::getNewEvtDispatcher(){//获取之后要retain
		return EventDispatcher::create();
	}
	EventDispatcher *EventDispatcher::getGlobalEvtDispatcher(){
		static EventDispatcher *globalDispatcher = 0;
		if(!globalDispatcher){
			globalDispatcher = EventDispatcher::create();
			CC_SAFE_RETAIN(globalDispatcher);
		}
		return globalDispatcher;
	}
	
	void EventDispatcher::destroyGlobalEvtDispatcher(){//获取之后要retain
		CC_SAFE_RELEASE(globalDispatcher);
	}

	/**
	listeningEvts的结构：
	CCDictionary{
		evt1 = CCDictionary{
			priority1 = CCArray{Event,...,Event},
			priority2 = CCArray{Event,...,Event},
			... ...
			priorityn = CCArray{Event,...,Event},
		},
		evt2 = CCDictionary{
			priority1 = CCArray{Event,...,Event},
			priority2 = CCArray{Event,...,Event},
			... ...
			priorityn = CCArray{Event,...,Event},
		},
		... ...
		evtn = CCDictionary{
			priority1 = CCArray{Event,...,Event},
			priority2 = CCArray{Event,...,Event},
			... ...
			priorityn = CCArray{Event,...,Event},
		}
	}
	**/
	//增加一个监听，
	void EventDispatcher::addListener(Event *evt){
		CCDictionary * dict = dynamic_cast<CCDictionary*>(listeningEvts->objectForKey(evt->evt));
		if(!dict){
			dict = CCDictionary::create();
			CC_SAFE_RETAIN(dict);
			listeningEvts->setObject(dict,evt->evt);
		}
		//现在已经找出了evt对应的所有dict了。
		CCArray * arr = dynamic_cast<CCArray*>(dict->objectForKey(evt->priority));
		if(!arr){
			arr = CCArray::create();
			CC_SAFE_RETAIN(arr);
			dict->setObject(arr, evt->priority);
		}
		//现在找到dict中evt相同优先级的数组了。
		CC_SAFE_RETAIN(evt);
		arr->addObject(evt);//加到尾部,取的时候 从头取
	}

	void EventDispatcher::rmListener(Event *evt){
		CCAssert(evt != 0, "evt 不能为空!");
		CCDictionary * dict = dynamic_cast<CCDictionary*>(listeningEvts->objectForKey(evt->evt));
		if(dict != 0){
			CCArray* arr = dynamic_cast<CCArray*>(dict->objectForKey(evt->priority));
			if(arr != 0){
				arr->removeObject(evt);
				CC_SAFE_RELEASE(evt);
			}
		}
	}
	
	/**
	incomingReqEvts的结构：
	CCDictionary{
		priority1 = CCArray{Event,...,Event},
		priority2 = CCArray{Event,...,Event},
		... ...
		priorityn = CCArray{Event,...,Event},
	}
	**/
	void EventDispatcher::addIncomingReq(Event *evt){
		CCArray * arr = dynamic_cast<CCArray*>(incomingReqEvts->objectForKey(evt->priority));
		if(!arr){
			arr = CCArray::create();
			CC_SAFE_RETAIN(arr);
			incomingReqEvts->setObject(arr, evt->priority);
		}
		CC_SAFE_RETAIN(evt);
		arr->addObject(evt);
	}

	void EventDispatcher::onUpdate(float f){
		//不同的优先级需要同时判断
		for(int i = Event::EVENT_PRIORITY_HIGHEST; i >= Event::EVENT_PRIORITY_LOWEST; i--){
			CCArray * arr = dynamic_cast<CCArray*>(incomingReqEvts->objectForKey(i));
			CCObject * incomingEvt;
			CCARRAY_FOREACH(arr,incomingEvt){
				Event *innerEvt = dynamic_cast<Event*>(incomingEvt);
				if(innerEvt){
					CCArray * listeningArr = dynamic_cast<CCArray*>(listeningEvts->objectForKey(innerEvt->evt));
					CCObject* listeningEvt;
					CCARRAY_FOREACH(listeningArr,listeningEvt){
						Event* leInner = dynamic_cast<Event*>(listeningEvt);
						(leInner->target->*leInner->func)(innerEvt->data);
					}
				}
			}
			arr->removeAllObjects();
			incomingReqEvts->removeObjectForKey(i);
		}
	}

	EventDispatcher::~EventDispatcher(){
		//处理listeningEvts
		CCArray* keys = listeningEvts->allKeys();
		CCObject *oneKey;
		CCARRAY_FOREACH(keys,oneKey){
			Event *evt = dynamic_cast<Event*>(oneKey);
			if(evt){
				CCDictionary* dict = dynamic_cast<CCDictionary*>(listeningEvts->objectForKey(evt->evt));
				for(int i = Event::EVENT_PRIORITY_HIGHEST; i >= Event::EVENT_PRIORITY_LOWEST; i--){
					CCArray * arr = dynamic_cast<CCArray*>(dict->objectForKey(i));
					CCObject *obj;
					CCARRAY_FOREACH(arr, obj){
						Event* evt = dynamic_cast<Event *>(obj);
						if(evt){
							CC_SAFE_RELEASE(evt);
						}
					}
					CC_SAFE_RELEASE(arr);
				}
				CC_SAFE_RELEASE(dict);
			}
		}
		CC_SAFE_RELEASE(listeningEvts);
		//处理incomingReqEvts
		for(int i = Event::EVENT_PRIORITY_HIGHEST; i >= Event::EVENT_PRIORITY_LOWEST; i--){
			CCArray * arr = dynamic_cast<CCArray*>(incomingReqEvts->objectForKey(i));
			CCObject *obj;
			CCARRAY_FOREACH(arr, obj){
				Event* evt = dynamic_cast<Event *>(obj);
				if(evt){
					CC_SAFE_RELEASE(evt);
				}
			}
			CC_SAFE_RELEASE(arr);
		}
		CC_SAFE_RELEASE(incomingReqEvts);
	}
}
