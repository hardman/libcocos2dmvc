#ifndef __COCOS2D_CONTROLLER_H__
#define __COCOS2D_CONTROLLER_H__
#include "cocos2d_mvc.h"
namespace cocos2d_mvc{
	class View;
	class Model;
	class  Controller: public CCNode, public EventDispatchHelper{
	protected:
		View *v;
		Model* m;
		Controller(bool doSchedule = false);
	public:
		virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
			cout<<""<<endl;
		};
		virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){};
		virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent) {};

		virtual void onUpdate(float f);
		virtual void onModelChanged();
		View* getView();
		void setView(View * v);
		CCScene * scene();

		virtual ~Controller();
		//CREATE_FUNC(Controller);
	};
}

#endif