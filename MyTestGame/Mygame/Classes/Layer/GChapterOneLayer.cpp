#include "GChapterOneLayer.h"
#include "Sprite/GTauren.h"
#include "Sprite/GTaurenBoss.h"
#include "Sprite/GHero.h"
#include "Sprite/EnemyZ.h"

bool GChapterOneLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	IsKillBoss=false;
	_mapMaxNum=3;
	_mapCurrentNum=1;
	_tileMapSizex=(float)1/2;
	strcpy(mapdata,"Map1_");
	initPlayer();
	initTileMap();
	initEnemy();
	return true;
}

void GChapterOneLayer::initBoss( int num )
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
void GChapterOneLayer::initEnemys( int num )
{
	for (int i=0;i<num;i++)
	{ 
		GTauren *tauren=GTauren::create();
		float mapw=_tileMap->getMapSize().width * _tileMap->getTileSize().width;
		tauren->setPosition(ccp(CCRANDOM_0_1()*mapw*2/3+mapw/3,
			CCRANDOM_0_1()*_tileMap->getMapSize().height * _tileMap->getTileSize().height*_tileMapSizex));
		tauren->setDesiredPosition(tauren->getPosition(),-1.0f);
		tauren->idle();
		//tauren->setColor(ccc3(255,0,0));
		_spriteLayer->addChild(tauren);
		enemy->addObject(tauren);
	}
}
