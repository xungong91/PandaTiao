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
	virtual void onEnter();
	virtual void onExit();

	void run();
	bool jump();

	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _runAction, RunAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::Action*, _jumpAction, JumpAction);
	CC_SYNTHESIZE(cocos2d::Vec2, _desiredPosition, DesiredPosition);

	virtual void update(float dt);
private:
	_ActionState mActionState;
	//µØÇòÒýÁ¦
	float mFallSpeed;
	void onfreeFall(float dt);
};

#endif