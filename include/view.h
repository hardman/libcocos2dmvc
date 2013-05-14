#ifndef __COCOS2D_VIEW_H__
#define __COCOS2D_VIEW_H__

#include "cocos2d_mvc.h"

namespace cocos2d_mvc{
	//class Model;
	class Controller;
	//class EventDispatcher;
	class  View :public CCLayer, public EventDispatchHelper{
	protected:
		EventDispatcher *eventDispatcher;
		Controller* controller;
		View();
		View(Controller *controller);
	public:
		void setController(Controller *c);
		void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
		void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
		void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
		virtual void refreshView(Model*model) = 0;
		virtual void onUpdate(float f);
		virtual ~View();
		//CREATE_FUNC(View);
	};
}

#endif