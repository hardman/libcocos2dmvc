#include "cocos2d_mvc.h"

namespace cocos2d_mvc{
		Controller::Controller(bool doSchedule):v(0),m(0)
		{
			if(doSchedule == true){
				schedule(schedule_selector(Controller::onUpdate));
			}
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
		Controller::~Controller(){
			CC_SAFE_RELEASE(m);
			CC_SAFE_RELEASE(v);
		}
		View* Controller::getView(){
			CCAssert(v != NULL, "v ½ûÖ¹Îª¿Õ!");
			return v;
		}
		void Controller::setView(View * v){
			this->v = v;
		}
}