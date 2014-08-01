#ifndef _G_GAME_SCENE_H_
#define _G_GAME_SCENE_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Layer\GGameLayerBase.h"
#include "Layer\GHudLayer.h"
#include "Defines.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GGameScene:public CCScene
{
public:
	virtual bool init();
	CREATE_FUNC(GGameScene);
	GGameScene();
	~GGameScene();
	GHudLayer *hudlayer;
	GGameLayerBase *gamelayer;
	static GGameScene* _GGameScene;
	static GGameScene* Singleton();
	static _GameLayerType GameLayerType;
private:
	GGameLayerBase *FactoryGameLaye(_GameLayerType type);
};

#endif // !_G_GAME_SCENE_H_
