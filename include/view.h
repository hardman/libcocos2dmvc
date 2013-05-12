#ifndef __COCOS2D_VIEW_H__
#define __COCOS2D_VIEW_H__

#include "cocos2d_mvc.h"

namespace cocos2d_mvc{
	//class Model;
	class Controller;
	//class EventDispatcher;
	class View :public CCLayer, public EventDispatchHelper{
	protected:
		EventDispatcher *eventDispatcher;
		Controller* controller;
	public:
		View(Controller *controller);
		bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
		void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
		void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
		virtual void refreshView(Model*model) = 0;
		virtual void onUpdate(float f);
		virtual ~View();
		//CREATE_FUNC(View);
	};
}

#endif