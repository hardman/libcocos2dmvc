#include "cocos2d_mvc.h"

namespace cocos2d_mvc{
	void Model::notifyModelChanged(){
		controller->onModelChanged();
	}
}