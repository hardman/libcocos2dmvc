#ifndef __COCOS2D_CONTROLLER_H__
#define __COCOS2D_CONTROLLER_H__
#include "cocos2d_mvc.h"
namespace cocos2d_mvc{
	class View;
	class Model;
	class Controller: public CCNode, public EventDispatchHelper{
		View *v;
		Model* m;
		EEE(Controller)//½ûÖ¹¸³Öµ
		ECC(Controller)//½ûÖ¹copy
	protected:
		Controller(View *v, Model* m);
	public:
		virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) = 0;
		virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) = 0;
		virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) = 0;

		virtual void onUpdate(float f);
		virtual void onModelChanged();
		
		virtual ~Controller();
		//CREATE_FUNC(Controller);
	};
}

#endif