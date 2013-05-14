#ifndef __COCOS2D_EVT_DISPATCHER_H__
#define __COCOS2D_EVT_DISPATCHER_H__
#include "cocos2d_mvc.h"
namespace cocos2d_mvc{
	class Event;
	class  EventDispatcher: public CCNode{
		CCDictionary * listeningEvts;
		CCDictionary * incomingReqEvts;
		static EventDispatcher * globalDispatcher;
		EventDispatcher();
	protected:
	public:
		static EventDispatcher *getNewEvtDispatcher();
		static EventDispatcher *getGlobalEvtDispatcher();
		//static void destroyGlobalEvtDispatcher();
		void addListener(Event *evt);
		void rmListener(Event *evt);
		void addIncomingReq(Event *evt);
		void onUpdate(float f);
		~EventDispatcher();
		CREATE_FUNC(EventDispatcher);
	};
}

#endif