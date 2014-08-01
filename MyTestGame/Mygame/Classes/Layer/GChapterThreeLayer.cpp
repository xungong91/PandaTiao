#include "GChapterThreeLayer.h"
#include "Sprite/GTaurenBoss.h"

bool GChapterThreeLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	initTileMap();
	initPlayer();
	initEnemy();
	_tileMapSizex=(float)1/3;
	return true;
}

void GChapterThreeLayer::initTileMap()
{
	_tileMap=CCTMXTiledMap::create("Map3.tmx");
	CCObject *pObject = NULL;
	CCARRAY_FOREACH(_tileMap->getChildren(), pObject)
	{
		CCTMXLayer *child = (CCTMXLayer*)pObject;
		child->getTexture()->setAliasTexParameters();
	}
	this->addChild(_tileMap,_other);
}
void GChapterThreeLayer::initEnemy()
{
	enemy=CCArray::create();
	enemy->retain();
	for (int i=0;i<20;i++)
	{ 
		GTaurenBoss *tauren=GTaurenBoss::create();
		float mapw=_tileMap->getMapSize().width * _tileMap->getTileSize().width;
		tauren->setPosition(ccp(CCRANDOM_0_1()*mapw*2/3+mapw/3,
			CCRANDOM_0_1()*_tileMap->getMapSize().height * _tileMap->getTileSize().height*_tileMapSizex));
		tauren->setDesiredPosition(tauren->getPosition(),-1.0f);
		tauren->idle();
		_spriteLayer->addChild(tauren);
		enemy->addObject(tauren);
	}
}