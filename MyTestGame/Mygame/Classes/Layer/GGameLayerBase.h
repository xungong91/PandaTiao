#ifndef _G_GMAE_LAYER_BASE_
#define _G_GMAE_LAYER_BASE_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Sprite/PlayerSprite.h"
#include "Scene\GMapScene.h"
#include "Defines.h"
USING_NS_CC;
USING_NS_CC_EXT;


class GGameLayerBase:public CCLayer
{
public:
	///初始化
	GGameLayerBase();
	~GGameLayerBase();
	virtual void initTileMap();
	virtual void initPlayer();
	virtual void initEnemy();
	///必要字段
	CC_SYNTHESIZE(PlayerSprite*,_player,Player);
	CCArray *enemy;
	CCArray *array_Gold;
	CCTMXTiledMap *_tileMap;
	///必要方法
	virtual void heroSmitten(CCObject* object);   //英雄攻击回调
	virtual void EnemySmitten(CCObject* object);  //敌人攻击回调
	virtual void EnemyDeath(CCObject* object);

	virtual void UpdataSprite(float dt);		//更新精灵
	virtual void updatePositions();				//更新英雄位置  重载可以加上怪物的位置
	void reorderActors();						//z轴位置
	void setViewpointCenter( CCPoint position); //英雄为中心
	void PickupGold();							//拾取金币

	virtual void LayerWin();
	virtual void heroDeal();
	void GamePause();
	void GameResume();
	///基类方法
	virtual void draw();
	virtual void update(float delta);
	virtual void onEnter();
	virtual void onExit();

protected:
	CCLayer *_spriteLayer;
	float _tileMapSizex;
	float m_glod;                                 //金币
};

#endif