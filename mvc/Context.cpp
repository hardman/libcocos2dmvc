#include "cocos2d_mvc.h"

namespace cocos2d_mvc{
	void Context::registerInjectorMaps(){
		Injector::getGlobalInjector()->mapSingleton(trans_injector_create(EventDispatcher::create), "EventDispatcher");
	}
}