#ifndef _C_GAME_LAYER_H_
#define _C_GAME_LAYER_H_

#include "cocos2d.h"
#include "sprite/CPandaSprite.h"
#include "gameLayer/CHudLayer.h"
#include "Box2D/Box2D.h"
#include "box/GLES-Render.h"
#include <list>
#include "box/CWorldLayer.h"

class CGameLayer : public CWorldLayer, public CHudDelegate
{
public:
	CGameLayer();
	~CGameLayer();
	CREATE_FUNC(CGameLayer);
	bool init();
	virtual void onEnter();
	virtual void onExit();
	//reset
	void reset();
	//touch
	virtual void onTouchBegan();
	//time
	virtual void update(float dt);
	void updateCheck();
	void addBlock(float dt);
private:
	//sprite panda
	CPandaSprite *mPanda;
	b2Body *mPandaBody;
	//sprite node
	cocos2d::SpriteBatchNode *mPandaBatchNode;
	//init world
	void initWorld();
	//contact
    MyContactListener *mContactListener;
	void beginContact(MyContact contact);
	void endContact(MyContact contact);
};

#endif