#include "cocos2d_mvc.h"


namespace cocos2d_mvc{	
	class InjectorFuncWrapper: public CCObject{
	public:
		injectorCreate icfunc;
		operator injectorCreate(){
			return icfunc;
		}
	};

	Injector::Injector(){
		singletonDict = CCDictionary::create();
		CC_SAFE_RETAIN(singletonDict);
		classDict = CCDictionary::create();
		CC_SAFE_RETAIN(classDict);
		valueDict = CCDictionary::create();
		CC_SAFE_RETAIN(valueDict);
	}

	Injector * Injector::getGlobalInjector(){
		static Injector * xxx = 0;
		if(!xxx) {
			xxx = Injector::create();
			xxx->retain();
		}
		return xxx;
	}
	
	/*Injector * Injector::getNewInjector(){
		return Injector::create();
	}*/

	bool Injector::checkExist(string className){
		return 0 != singletonDict->objectForKey(className)||
			0 != classDict->objectForKey(className)||
			0 != valueDict->objectForKey(className);
	}

	CCObject * Injector::getInstance(string className){
		CCObject *finded = 0;
		finded = singletonDict->objectForKey(className);
		if(finded != 0){
			return finded;
		}else{
			finded = classDict->objectForKey(className);
			if(finded != 0){
				return ((InjectorFuncWrapper*)finded)->operator cocos2d_mvc::injectorCreate()();
			}else{
				finded = valueDict->objectForKey(className);
				if(finded != 0){
					return finded;
				}
			}
		}
		return 0;
	}
	
	void Injector::mapSingleton(injectorCreate createFunc, string className){
		if(false == checkExist(className)){
			CCObject* obj = createFunc();
			obj->retain();
			singletonDict->setObject(obj, className);
		}else{
			CCLog("in mapSingleton() 已经有%s这个类了，不能重复map，可以先unmap一下", className.c_str());
		}
	}

	void Injector::mapClass(injectorCreate createFunc, string className){
		if(false == checkExist(className)){
			InjectorFuncWrapper * funcWrapper = new InjectorFuncWrapper;
			funcWrapper->autorelease();
			funcWrapper->icfunc = createFunc;
			classDict->setObject(funcWrapper, className);
		}else{
			CCLog("in mapSingleton() 已经有%s这个类了，不能重复map，可以先unmap一下", className.c_str());
		}
	}
	
	void Injector::mapValue(CCObject * obj, string name){
		if(false == checkExist(name)){
			valueDict->setObject(obj, name);
		}else{
			CCLog("in mapSingleton() 已经有%s这个类了，不能重复map，可以先unmap一下", name.c_str());
		}
	}

	void Injector::unmap(string className){
		singletonDict->removeObjectForKey(className);
		classDict->removeObjectForKey(className);
		valueDict->removeObjectForKey(className);
	}
	Injector::~Injector(){
		CC_SAFE_RELEASE(singletonDict);
		CC_SAFE_RELEASE(classDict);
		CC_SAFE_RELEASE(valueDict);
	}
}