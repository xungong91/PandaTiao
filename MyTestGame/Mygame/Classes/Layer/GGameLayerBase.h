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
	///��ʼ��
	GGameLayerBase();
	~GGameLayerBase();
	virtual void initTileMap();
	virtual void initPlayer();
	virtual void initEnemy();
	///��Ҫ�ֶ�
	CC_SYNTHESIZE(PlayerSprite*,_player,Player);
	CCArray *enemy;
	CCArray *array_Gold;
	CCTMXTiledMap *_tileMap;
	///��Ҫ����
	virtual void heroSmitten(CCObject* object);   //Ӣ�۹����ص�
	virtual void EnemySmitten(CCObject* object);  //���˹����ص�
	virtual void EnemyDeath(CCObject* object);

	virtual void UpdataSprite(float dt);		//���¾���
	virtual void updatePositions();				//����Ӣ��λ��  ���ؿ��Լ��Ϲ����λ��
	void reorderActors();						//z��λ��
	void setViewpointCenter( CCPoint position); //Ӣ��Ϊ����
	void PickupGold();							//ʰȡ���

	virtual void LayerWin();
	virtual void heroDeal();
	void GamePause();
	void GameResume();
	///���෽��
	virtual void draw();
	virtual void update(float delta);
	virtual void onEnter();
	virtual void onExit();

protected:
	CCLayer *_spriteLayer;
	float _tileMapSizex;
	float m_glod;                                 //���
};

#endif