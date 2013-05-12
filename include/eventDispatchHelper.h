#ifndef __COCOS2D_EVT_DISPATCH_HELP_H__
#define __COCOS2D_EVT_DISPATCH_HELP_H__

#include "cocos2d_mvc.h"

namespace cocos2d_mvc{
	class EventDispatcher;
	class Injector;
	class EventDispatchHelper{
	protected:
		EventDispatcher * evtDispatcher;
		Injector * injector;
		EventDispatchHelper();
	public:
		//CREATE_FUNC(EventDispatchHelper);
		void mapEventListener(Event *evt);
		void dispatch(Event * evt);
	};
}
#endif