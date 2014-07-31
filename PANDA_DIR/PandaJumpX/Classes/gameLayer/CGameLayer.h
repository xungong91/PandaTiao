#ifndef _C_GAME_LAYER_H_
#define _C_GAME_LAYER_H_

#include "cocos2d.h"
#include "sprite/CPandaSprite.h"

class CGameLayer : public cocos2d::Layer
{
public:
	CGameLayer();
	~CGameLayer();
	CREATE_FUNC(CGameLayer);
	bool init();
private:
	CPandaSprite *mPanda;
	cocos2d::SpriteBatchNode *mPandaBatchNode;
};

#endif