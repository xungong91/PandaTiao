#include "GChapterLayerBase.h"
#include <string>
using namespace std;
GChapterLayerBase::GChapterLayerBase()
{
	mapdata=new char[10];
}
GChapterLayerBase::~GChapterLayerBase()
{
	CC_SAFE_DELETE_ARRAY(mapdata);
}
void GChapterLayerBase::initEnemys( int num )
{

}
void GChapterLayerBase::initBoss( int num )
{

}
void GChapterLayerBase::initEnemy()
{
	enemy=CCArray::create();
	enemy->retain();
	initEnemys(10);
}
void GChapterLayerBase::initTileMaps(int num)
{
	string s;
	ostringstream oss;
	oss<<mapdata<<num<<".tmx";
	s=oss.str();
	_tileMap=CCTMXTiledMap::create(s.c_str());
	CCObject *pObject = NULL;
	CCARRAY_FOREACH(_tileMap->getChildren(), pObject)
	{
		CCTMXLayer *child = (CCTMXLayer*)pObject;
		child->getTexture()->setAliasTexParameters();
	}
	this->addChild(_tileMap,_other);

	CCTMXObjectGroup *objects=_tileMap->objectGroupNamed("player");//获取对象层  
	CCDictionary  *PortalPoint=objects->objectNamed("Portal");//获取对象 
	float pox = PortalPoint->valueForKey("x")->floatValue(); 
	float poy = PortalPoint->valueForKey("y")->floatValue(); 
	UiAnimation->setPosition(ccp(pox,poy));
	UiAnimation->setVisible(false);

	CCDictionary  *heroPoint=objects->objectNamed("hero");//获取对象 
	float px = heroPoint->valueForKey("x")->floatValue(); 
	float py = heroPoint->valueForKey("y")->floatValue(); 
	_player->setPosition(ccp(px, py));
	_player->setDesiredPosition(_player->getPosition());
}

void GChapterLayerBase::initTileMap()
{
	UiAnimation=CCArmature::create("UiAnimation");
	UiAnimation->getAnimation()->play("Portal");
	UiAnimation->setAnchorPoint(ccp(0.5,0));
	this->addChild(UiAnimation,_uiAnimation);
	GChapterLayerBase::initTileMaps(1);
}

void GChapterLayerBase::intoPortalCallback( float dt )
{
	CCPoint armupoint=UiAnimation->getPosition();
	CCPoint playerpoint=_player->GetCenterPoint();
	float distance= ccpDistance(armupoint,playerpoint);
	if (distance<20)
	{
		this->unschedule(schedule_selector(GChapterLayerBase::intoPortalCallback));
		//清楚所有敌人
		CCObject *obj=NULL;
		CCARRAY_FOREACH(enemy,obj)
		{
			ActionSprite* sprite=static_cast<ActionSprite*>(obj);
			sprite->clean();
			_spriteLayer->removeChild(sprite);
		}
		enemy->removeAllObjects();
		//加载下一个地图数据
		_mapCurrentNum+=1;
		if (_mapMaxNum==_mapCurrentNum)
		{
			IsKillBoss=true;
		}
		if (_mapCurrentNum<_mapMaxNum)
		{
			this->removeChild(_tileMap);
			initTileMaps(_mapCurrentNum);
			initEnemys(10);
		}
		else if(_mapCurrentNum==_mapMaxNum)
		{
			this->removeChild(_tileMap);
			initTileMaps(_mapCurrentNum);
			initEnemys(10);
			initBoss(1);
		}
	}
}

void GChapterLayerBase::LayerWin()
{
	if (IsKillBoss)
	{
		this->scheduleOnce(schedule_selector(GChapterLayerBase::WinCallBack),3.0f);
		return;
	}
	UiAnimation->setVisible(true);
	this->schedule(schedule_selector(GChapterLayerBase::intoPortalCallback));
	initEnemys(10);
}

void GChapterLayerBase::WinCallBack( float dt )
{
	GGameLayerBase::LayerWin();
}

