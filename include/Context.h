#ifndef __COCOS2D_CONTEXT_H__
#define __COCOS2D_CONTEXT_H__
#include "cocos2d_mvc.h"

namespace cocos2d_mvc{
	class Context: public EventDispatchHelper{
	protected:
		EC(Context)
	public:
		virtual void registerInjectorMaps();
	};
}
#endif