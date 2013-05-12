#ifndef __COCOS2D_MVC_H__
#define __COCOS2D_MVC_H__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;
namespace cocos2d_mvc{
}
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
	#define REGISTER_INJECTOR_FOR_CLASS(className) \

}

#ifndef __COCOS2D_EVT_DISPATCHER_H__
#define __COCOS2D_EVT_DISPATCHER_H__
namespace cocos2d_mvc{
	class Event;
	class EventDispatcher: public CCNode{
		CCDictionary * listeningEvts;
		CCDictionary * incomingReqEvts;
		static EventDispatcher * globalDispatcher;
		EventDispatcher();
		EEE(EventDispatcher)
		ECC(EventDispatcher)
	protected:
	public:
		static EventDispatcher *getNewEvtDispatcher();
		static EventDispatcher *getGlobalEvtDispatcher();
		static void destroyGlobalEvtDispatcher();
		void addListener(Event *evt);
		void rmListener(Event *evt);
		void addIncomingReq(Event *evt);
		void onUpdate(float f);
		~EventDispatcher();
		CREATE_FUNC(EventDispatcher);
	};
}
#endif

#ifndef __COCOS2D_EVENT_H__
#define __COCOS2D_EVENT_H__

namespace cocos2d_mvc{
	class EventDispatcher;
	class Event:public CCObject{
		EEE(Event)
		ECC(Event)
		bool needClean;//表示data是否需要清理
	public:
		enum{
			EVENT_PRIORITY_LOWEST,
			EVENT_PRIORITY_LOW,
			EVENT_PRIORITY_DEFAULT,
			EVENT_PRIORITY_MID,
			EVENT_PRIORITY_HIGH,
			EVENT_PRIORITY_HIGHEST,
		};
		bool operator<(const Event & evt);
		EventDispatcher* dispatcher;
		string evt;
		EventDispatchHelper* target;
		EVT_CALLBACK func;
		CCObject * data;
		int priority;
		Event(EventDispatcher* dispatcher, string evt, EventDispatchHelper* target, EVT_CALLBACK func, CCObject * data, bool needClean = true, int priority = EVENT_PRIORITY_DEFAULT);
		virtual ~Event();
		//INIT_FOR_CREATE_FUNC();
		//CREATE_FUNC(Event);
	};
}

#endif
#ifndef __COCOS2D_EVT_DISPATCH_HELP_H__
#define __COCOS2D_EVT_DISPATCH_HELP_H__

namespace cocos2d_mvc{
	class EventDispatcher;
	class Injector;
	class EventDispatchHelper{
	protected:
		EventDispatcher * evtDispatcher;
		Injector * injector;
		EventDispatchHelper();
	public:
		//CREATE_FUNC(EventDispatchHelper);
		void mapEventListener(Event *evt);
		void dispatch(Event * evt);
	};
}
#endif

#ifndef __COCOS2D_CONTROLLER_H__
#define __COCOS2D_CONTROLLER_H__
namespace cocos2d_mvc{
	class View;
	class Model;
	class Controller: public CCNode, public EventDispatchHelper{
		View *v;
		Model* m;
		EEE(Controller)//禁止赋值
		ECC(Controller)//禁止copy
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
#ifndef __COCOS2D_MODEL_H__
#define __COCOS2D_MODEL_H__

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
#ifndef __COCOS2D_VIEW_H__
#define __COCOS2D_VIEW_H__


namespace cocos2d_mvc{
	//class Model;
	class Controller;
	//class EventDispatcher;
	class View :public CCLayer, public EventDispatchHelper{
		EventDispatcher *eventDispatcher;
		Controller* controller;
	protected:
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

#ifndef __COCOS2D_INJECTOR_H__
#define __COCOS2D_INJECTOR_H__
namespace cocos2d_mvc{
	class Injector: public CCObject{
		CCDictionary* singletonDict;
		CCDictionary* classDict;
		CCDictionary* valueDict;
		ECC(Injector)
		EEE(Injector)
		Injector(){
			singletonDict = CCDictionary::create();
			CC_SAFE_RETAIN(singletonDict);
			classDict = CCDictionary::create();
			CC_SAFE_RETAIN(classDict);
			valueDict = CCDictionary::create();
			CC_SAFE_RETAIN(valueDict);
		}
	public:
		static Injector * getGlobalInjector();
		//static Injector * getNewInjector();
		CCObject * getInstance(string className);
		bool checkExist(string className);

		void mapSingleton(injectorCreate createFunc, string className);
		void mapClass(injectorCreate createFunc, string className);
		void mapValue(CCObject * obj, string name);//retain

		void unmap(string className);//release
		
		~Injector(){
			CC_SAFE_RELEASE(singletonDict);
			CC_SAFE_RELEASE(classDict);
			CC_SAFE_RELEASE(valueDict);
		}
		INIT_FOR_CREATE_FUNC();
		CREATE_FUNC(Injector);
	};
}

#endif

#ifndef __COCOS2D_CONTEXT_H__
#define __COCOS2D_CONTEXT_H__

namespace cocos2d_mvc{
	class Context: public EventDispatcherHelper{
	protected:
		EC(Context)
	public:
		virtual void registerInjectorMaps();
	};
}
#endif

#endif