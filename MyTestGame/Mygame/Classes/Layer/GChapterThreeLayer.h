#ifndef _G_CHAPTER_THREE_LAYER_
#define _G_CHAPTER_THREE_LAYER_

#include "GGameLayerBase.h"
USING_NS_CC;

class GChapterThreeLayer:public GGameLayerBase
{
public:
	CREATE_FUNC(GChapterThreeLayer);
	bool init();

	virtual void initTileMap();
	virtual void initEnemy();
};
#endif