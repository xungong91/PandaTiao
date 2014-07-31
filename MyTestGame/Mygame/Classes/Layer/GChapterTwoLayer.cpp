#include "GChapterTwoLayer.h"
#include "Sprite/GTauren.h"
#include "Sprite/GTaurenBoss.h"

bool GChapterTwoLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	IsKillBoss=false;
	_mapMaxNum=3;
	_mapCurrentNum=1;
	_tileMapSizex=(float)3/7;
	strcpy(mapdata,"Map2_");
	initPlayer();
	initTileMap();
	initEnemy();
	return true;
}

void GChapterTwoLayer::initEnemys( int num )
{
	for (int i=0;i<num;i++)
	{ 
		GTauren *tauren=GTauren::create();
		float mapw=_tileMap->getMapSize().width * _tileMap->getTileSize().width;
		tauren->setPosition(ccp(CCRANDOM_0_1()*mapw*2/3+mapw/3,
			CCRANDOM_0_1()*_tileMap->getMapSize().height * _tileMap->getTileSize().height*_tileMapSizex));
		tauren->setDesiredPosition(tauren->getPosition(),-1.0f);
		tauren->idle();
		_spriteLayer->addChild(tauren);
		enemy->addObject(tauren);
	}
}
void GChapterTwoLayer::initBoss( int num )
{
	for (int i=0;i<num;i++)
	{
		GTaurenBoss *boss=GTaurenBoss::create();
		boss->setPosition(ccp(_tileMap->getMapSize().width * _tileMap->getTileSize().width-200,50));
		boss->setDesiredPosition(boss->getPosition(),-1.0f);
		boss->idle();
		_spriteLayer->addChild(boss);
		enemy->addObject(boss);
	}
}
