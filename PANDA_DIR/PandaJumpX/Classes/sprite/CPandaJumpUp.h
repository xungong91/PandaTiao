#ifndef _C_PANDA_JUMP_UP_H_
#define _C_PANDA_JUMP_UP_H_

#include "cocos2d.h"

typedef void (cocos2d::Node::*CB_JUMP_UP)(float desired);

class CPandaJumpUp : public cocos2d::ActionInterval
{
public:
	CPandaJumpUp();
	~CPandaJumpUp();
	/** creates the action */
	static CPandaJumpUp* create(float duration, cocos2d::Node *Delegate, CB_JUMP_UP onCallBack);
	bool initWithDuration(float duration, cocos2d::Node *Delegate, CB_JUMP_UP onCallBack);
	virtual CPandaJumpUp* clone() const override;
	//
	// Overrides
	//
	virtual CPandaJumpUp* reverse(void) const  override;
	virtual void startWithTarget(cocos2d::Node *target) override;
	virtual void update(float time) override;
private:
	float _positionDelta;
	float _startPosition;
	float _previousPosition;
	cocos2d::Node* mDelegate;
	CB_JUMP_UP mCallBack;
};

#endif