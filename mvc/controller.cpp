#include "cocos2d_mvc.h"

namespace cocos2d_mvc{
		Controller::Controller(View *v, Model* m)
			:v(v),
			m(m)
		{
		}
		void Controller::onUpdate(float f){
			m->onUpdate(f);
			v->onUpdate(f);
		}
		void Controller::onModelChanged(){
			v->refreshView(m);
		}
		Controller::~Controller(){
			CC_SAFE_RELEASE(m);
			CC_SAFE_RELEASE(v);
		}
}