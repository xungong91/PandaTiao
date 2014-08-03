#include "CPandaJumpUp.h"

USING_NS_CC;

CPandaJumpUp::CPandaJumpUp()
{

}

CPandaJumpUp::~CPandaJumpUp()
{

}

CPandaJumpUp* CPandaJumpUp::create( float duration, cocos2d::Node *Delegate, CB_JUMP_UP onCallBack )
{
	CPandaJumpUp *ret = new CPandaJumpUp();
	ret->initWithDuration(duration, Delegate, onCallBack);
	ret->autorelease();

	return ret;
}

bool CPandaJumpUp::initWithDuration( float duration, cocos2d::Node *Delegate, CB_JUMP_UP onCallBack )
{
	if (!ActionInterval::initWithDuration(duration))
	{
		return false;
	}
	this->mDelegate = Delegate;
	this->mCallBack = onCallBack;

	return true;
}

CPandaJumpUp* CPandaJumpUp::clone() const 
{
	// no copy constructor
	auto a = new CPandaJumpUp();
	a->initWithDuration(_duration, mDelegate, mCallBack);
	a->autorelease();
	return a;
}

void CPandaJumpUp::startWithTarget( cocos2d::Node *target )
{
	ActionInterval::startWithTarget(target);
	_previousPosition = _startPosition = target->getPosition();
}
