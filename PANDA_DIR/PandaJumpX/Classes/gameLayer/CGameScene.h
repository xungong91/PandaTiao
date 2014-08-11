#ifndef _C_GAME_SCENE_H_
#define _C_GAME_SCENE_H_

#include "cocos2d.h"
#include "CHudLayer.h"

class CGameScene : public cocos2d::Scene
{
public:
	static CGameScene* gGameScene;
	CGameScene();
	~CGameScene();
	CREATE_FUNC(CGameScene);
	bool init();
private:

};

#endif