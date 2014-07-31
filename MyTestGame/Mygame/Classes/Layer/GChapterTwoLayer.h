#ifndef _G_CHAPTER_TWO_LAYER_
#define _G_CHAPTER_TWO_LAYER_

#include "GChapterLayerBase.h"
USING_NS_CC;

class GChapterTwoLayer:public GChapterLayerBase
{
public:
	CREATE_FUNC(GChapterTwoLayer);
	bool init();
private:
	virtual void initEnemys(int num);
	virtual void initBoss(int num);
};
#endif