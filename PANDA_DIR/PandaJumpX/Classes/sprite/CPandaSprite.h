#ifndef _C_PANDA_SPRITE_H_
#define _C_PANDA_SPRITE_H_

#include "cocos2d.h"
#include "sprite/CPandaDefines.h"

class CPandaSprite : public cocos2d::Sprite
{
public:
	CPandaSprite();
	~CPandaSprite();
	CREATE_FUNC(CPandaSprite);
	bool init();

	void run();

	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _runAction, RunAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _jumpAction, JumpAction);

private:
	_ActionState mActionState;
};

#endif