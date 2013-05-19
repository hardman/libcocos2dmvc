#include "cocos2d_mvc.h"

namespace cocos2d_mvc{
		Controller::Controller(bool doSchedule):v(0),m(0)
		{
			if(doSchedule == true){
				schedule(schedule_selector(Controller::onUpdate));
			}
			//this->addChild(EventDispatcher::getGlobalEvtDispatcher());
			EventDispatcher::getGlobalEvtDispatcher()->setParent(this);
		}
		void Controller::onUpdate(float f){
			if(m)
				m->onUpdate(f);
			if(v)
				v->onUpdate(f);
		}
		void Controller::onModelChanged(){
			if(v)
				v->refreshView(m);
		}
		CCScene * Controller::scene(){
			static CCScene* sc = 0;
			if(sc == 0){
				sc = CCScene::create();
				CC_SAFE_RETAIN(sc);
			}
			return sc;
		}
		Controller::~Controller(){
			CC_SAFE_RELEASE(m);
			CC_SAFE_RELEASE(v);
		}
		View* Controller::getView(){
			int a = 10;
			CCAssert(v != NULL, "v ½ûÖ¹Îª¿Õ!");
			int b = 12;
			return v;
		}
		void Controller::setView(View * v){
			if(this->v != 0){
				this->v->removeFromParentAndCleanup(true);
				CC_SAFE_RELEASE(this->v);
				this->v = 0;
			}
			this->v = v;
			CC_SAFE_RETAIN(this->v);
			this->addChild(v);
		}
}