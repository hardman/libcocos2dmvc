#ifndef __COCOS2D_MODEL_H__
#define __COCOS2D_MODEL_H__
#include "cocos2d_mvc.h"

namespace cocos2d_mvc{
	class Controller;
	class Model: public CCObject, public EventDispatchHelper{
		EEE(Model)
		ECC(Model)
		Controller* controller;
	protected:
		Model(Controller* controller);
	public:
		void notifyModelChanged();
		virtual void onUpdate(float f) = 0;
		//CREATE_FUNC(Model);
	};
}
#endif