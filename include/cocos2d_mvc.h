#ifndef __COCOS2D_MVC_H__
#define __COCOS2D_MVC_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

namespace cocos2d_mvc{
	#define EMPTY_CONSTRUCT(className) \
		className(){}
	#define EMPTY_EQUAL_EXPR(className) \
		className & operator=(const className&){}
	#define EMPTY_COPY_CONSTRUCT(className) \
		className(const className&){}

	#define EC EMPTY_CONSTRUCT
	#define EEE EMPTY_EQUAL_EXPR
	#define ECC EMPTY_COPY_CONSTRUCT
	
	class EventDispatchHelper;

	typedef void (EventDispatchHelper::*EVT_CALLBACK)(CCObject *data);
	#define trans_evt_callback(callback) (EVT_CALLBACK)(callback)
	//for injector begin
	typedef CCObject* (*injectorCreate)();
	#define trans_injector_create(create) (injectorCreate)(create)
	//for injector end

	#define INIT_FOR_CREATE_FUNC() \
		bool init(){return true;}
}
#include "eventDispatcher.h"
#include "event.h"
#include "eventDispatchHelper.h"
#include "controller.h"
#include "model.h"
#include "view.h"
#include "injector.h"
#include "Context.h"

#endif