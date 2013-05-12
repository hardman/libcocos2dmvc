#include "cocos2d_mvc.h"

namespace cocos2d_mvc{
		View::View(Controller *controller): controller(controller){
		}
		bool View::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
			return controller->ccTouchBegan(pTouch, pEvent);
		}
		void View::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
			controller->ccTouchMoved(pTouch, pEvent);
		}
		void View::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
			controller->ccTouchEnded(pTouch, pEvent);
		}
		View::~View(){
		}
}