#include "cocos2d_mvc.h"


namespace cocos2d_mvc{	
	Injector * Injector::getGlobalInjector(){
		static Injector * xxx = 0;
		if(!xxx) {
			xxx = Injector::create();
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
				return ((injectorCreate)finded)();
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
			singletonDict->setObject(createFunc(), className);
		}else{
			CCLog("in mapSingleton() 已经有%s这个类了，不能重复map，可以先unmap一下", className.c_str());
		}
	}

	void Injector::mapClass(injectorCreate createFunc, string className){
		if(false == checkExist(className)){
			classDict->setObject((CCObject*)createFunc, className);
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
}