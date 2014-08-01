#include "CPandaSprite.h"

USING_NS_CC;
using namespace std;

CPandaSprite::CPandaSprite() : 
	_runAction(NULL),
	_jumpAction(NULL)
{

}

CPandaSprite::~CPandaSprite()
{
	CC_SAFE_RELEASE(_runAction);
	CC_SAFE_RELEASE(_jumpAction);
}

bool CPandaSprite::init()
{
	if (!Sprite::initWithSpriteFrameName("runPanda0.png"))
	{
		return false;
	}
	int i;
	//run animation
	Vector<SpriteFrame*> runFrames;
	for (i = 0; i < 8; i++)
	{
		SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(
			CCString::createWithFormat("runPanda%d.png", i)->getCString());
		runFrames.pushBack(frame);
	}
	Animation *idleAnimation = Animation::createWithSpriteFrames(runFrames, 0.06f);
	this->setRunAction(RepeatForever::create(Animate::create(idleAnimation)));

	return true;
}

void CPandaSprite::run()
{
	if (true)
	{
		this->stopAllActions();
		this->runAction(_runAction);
		mActionState = _ActionState::run;
	}
}
