#include "Sprite/SpriteBox.h"

SpriteBox::SpriteBox()
{
}

void SpriteBox::SetSpriteBox( CCPoint p1,CCSize s1,CCPoint p2,CCSize s2 )
{
	this->_hitBox.original.origin=p1;
	this->_hitBox.original.size=s1;
	this->_attackBox.original.origin=p2;
	this->_attackBox.original.size=s2;
	_boxItems=CCArray::create();
	_boxItems->retain();
}
SpriteBox::~SpriteBox()
{
	CC_SAFE_RELEASE(_boxItems);
}
cocos2d::CCRect SpriteBox::GetHitbox()
{
	return _hitBox.actual;
}

cocos2d::CCRect SpriteBox::GetAttackBox()
{
	return _attackBox.actual;
}

cocos2d::CCRect SpriteBox::GetAttackBox(_ActionState state,int num )
{
	CCObject* obj=NULL;
	CCARRAY_FOREACH(_boxItems,obj)
	{
		BoxItem* box=static_cast<BoxItem*>(obj);
		if (box->IsExist(state,num))
		{
			return GetCCRect(_point,_Vector,box->_attackRect);
		}
	}
	return _attackBox.actual;
}

cocos2d::CCRect SpriteBox::GetCCRect( CCPoint point,float Vector,CCRect original )
{
	CCPoint actualccp = ccpAdd(point, ccp(
		(Vector < 0
		?(- original.origin.x - original.size.width) 
		: original.origin.x)
		,original.origin.y));
	original.origin=actualccp;
	return original;
}

cocos2d::CCPoint SpriteBox::GetCenterPoint()
{
	CCPoint _point=ccp(_hitBox.actual.getMidX(),_hitBox.actual.getMinY());
	return _point;
}

cocos2d::CCPoint SpriteBox::GetCenterOriginalPoint()
{
	CCPoint _point=ccp(_hitBox.original.getMidX(),_hitBox.original.getMinY());
	return _point;
}
void SpriteBox::UpdataBox( CCPoint point,float Vector )
{
	_point=point;
	_Vector=Vector;
	_attackBox.actual=GetCCRect(point,Vector,_attackBox.original);
	_hitBox.actual= GetCCRect(point,Vector,_hitBox.original);
}

cocos2d::CCRect SpriteBox::GetDefaultHitBox()
{
	return _hitBox.original;
}


bool BoxItem::IsExist( _ActionState state,int num )
{
	if (this->_actionState==state&&this->_num==num)
		return true;
	else
		return false;
}

BoxItem::BoxItem(CCPoint p1,CCSize s1,CCPoint p2,CCSize s2,_ActionState actionState,int num)
{
	this->_hitRect.origin=p1;
	this->_hitRect.size=s1;
	this->_attackRect.origin=p2;
	this->_attackRect.size=s2;
	_actionState=actionState;
	_num=num;
	this->autorelease();
}

BoxItem::~BoxItem()
{

}
