#ifndef _C_GAME_LAYER_H_
#define _C_GAME_LAYER_H_

#include "cocos2d.h"
#include "sprite/CPandaSprite.h"
#include "gameLayer/CHudLayer.h"
#include "Box2D/Box2D.h"
#include "box/GLES-Render.h"

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

	void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags);
private:
	CPandaSprite *mPanda;
	cocos2d::SpriteBatchNode *mPandaBatchNode;

	void initWorld();
	b2World *mWorld;
	b2Body *mPandaBody;
	GLESDebugDraw * mDebugDraw;  
};

#endif