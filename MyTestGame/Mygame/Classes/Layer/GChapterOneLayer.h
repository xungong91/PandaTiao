#ifndef _G_CHAPTER_ONE_LAYER_
#define _G_CHAPTER_ONE_LAYER_

#include "GChapterLayerBase.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;

class GChapterOneLayer:public GChapterLayerBase
{
public:
	CREATE_FUNC(GChapterOneLayer);
	bool init();
private:
	virtual void initEnemys(int num);
	virtual void initBoss(int num);
};
#endif