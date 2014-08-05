#ifndef _C_GAME_LAYER_H_
#define _C_GAME_LAYER_H_

#include "cocos2d.h"
#include "sprite/CPandaSprite.h"
#include "gameLayer/CHudLayer.h"
#include <Box2D/Box2D.h>

#define PTM_RATIO 32

class CGameLayer : public cocos2d::Layer , public CHudDelegate
{
public:
	CGameLayer();
	~CGameLayer();
	CREATE_FUNC(CGameLayer);
	bool init();
	virtual void onEnter();
	virtual void onExit();

	virtual void onTouchBegan();

	virtual void update(float dt);
	void updatePositions();
private:
	CPandaSprite *mPanda;
	cocos2d::SpriteBatchNode *mPandaBatchNode;

	//box2d
	void initWorld();
	b2World *world;
};

#endif