#ifndef _G_CHAPTER_LAYER_BASE_H_
#define _G_CHAPTER_LAYER_BASE_H_

#include "GGameLayerBase.h"

class GChapterLayerBase:public GGameLayerBase
{
protected:
	GChapterLayerBase();
	~GChapterLayerBase();
	virtual void initEnemys(int num);
	virtual void initBoss(int num);
	virtual void initTileMaps(int num);
	virtual void LayerWin();
	virtual void initTileMap();
	virtual void initEnemy();
	CCArmature* UiAnimation;
	virtual void intoPortalCallback(float dt);
	int _mapMaxNum;
	int _mapCurrentNum;
	bool IsKillBoss;
	char* mapdata;
	void WinCallBack(float dt);
};

#endif