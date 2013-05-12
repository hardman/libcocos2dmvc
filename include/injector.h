#ifndef __COCOS2D_INJECTOR_H__
#define __COCOS2D_INJECTOR_H__
#include "cocos2d_mvc.h"
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