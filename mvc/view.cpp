#include "cocos2d_mvc.h"

namespace cocos2d_mvc{
		View::View(Controller *controller): controller(controller){
		}
		View::View(){
		}
		void View::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
			controller->ccTouchesBegan(pTouches,pEvent);
			cout<<"1"<<endl;
		}
		void View::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
			controller->ccTouchesMoved(pTouches,pEvent);
			cout<<"2"<<endl;
		}
		void View::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
			controller->ccTouchesEnded(pTouches,pEvent);
			cout<<"3"<<endl;
		}
		void View::onUpdate(float f){
		}
		View::~View(){
		}
		void View::setController(Controller *c){
			controller = c;
		}
}