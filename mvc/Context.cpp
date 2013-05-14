#include "cocos2d_mvc.h"

namespace cocos2d_mvc{
	Context::Context(){}
	void Context::registerInjectorMaps(){
		Injector::getGlobalInjector()->mapSingleton(trans_injector_create(EventDispatcher::create), "EventDispatcher");
	}
}