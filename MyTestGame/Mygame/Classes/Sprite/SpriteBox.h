#ifndef _SPRITE_BOX_H_
#define _SPRITE_BOX_H_

#include "cocos2d.h"
#include "Defines.h"
USING_NS_CC;

class BoxItem:public CCObject
{
public:
	BoxItem(CCPoint p1,CCSize s1,CCPoint p2,CCSize s2,_ActionState actionState,int num);
	~BoxItem();
	bool IsExist(_ActionState state,int num);
	CCRect _hitRect;
	CCRect _attackRect;
protected:
	_ActionState _actionState;
	int _num;
};

class SpriteBox
{
public:
	SpriteBox();
	~SpriteBox();
	void SetSpriteBox( CCPoint p1,CCSize s1,CCPoint p2,CCSize s2 );
	CCRect GetHitbox();
	virtual CCRect GetAttackBox();
	CCRect GetAttackBox(_ActionState state,int num);
	CCPoint GetCenterPoint();
	void UpdataBox(CCPoint point,float Vector);
	CCRect GetDefaultHitBox();
	CCArray* _boxItems;
	CCPoint GetCenterOriginalPoint();
protected:
	CCRect GetCCRect(CCPoint point,float Vector,CCRect original);
	BoundingBox _hitBox;
	BoundingBox _attackBox;
	CCPoint _point;
	float _Vector;
};



#endif