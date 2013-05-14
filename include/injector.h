#ifndef __COCOS2D_INJECTOR_H__
#define __COCOS2D_INJECTOR_H__
#include "cocos2d_mvc.h"
namespace cocos2d_mvc{
	class  Injector: public CCObject{
		CCDictionary* singletonDict;
		CCDictionary* classDict;
		CCDictionary* valueDict;
		Injector();
	public:
		static Injector * getGlobalInjector();
		//static Injector * getNewInjector();
		CCObject * getInstance(string className);
		bool checkExist(string className);
		void mapSingleton(injectorCreate createFunc, string className);
		void mapClass(injectorCreate createFunc, string className);
		void mapValue(CCObject * obj, string name);//retain

		void unmap(string className);//release
		
		~Injector();
		INIT_FOR_CREATE_FUNC();
		CREATE_FUNC(Injector);
	};
}

#endif