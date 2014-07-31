#include "Sprite/ActionSprite.h"


ActionSprite::ActionSprite()
{
	scale=1.0f;
}
void ActionSprite::animationEvent( CCArmature *armature, MovementEventType movementType, const char *movementID )
{
	if (movementType==COMPLETE)
	{
		if (strcmp(movementID,"paiji")==0)
		{
			this->idle();
		}
		else if (strcmp(movementID,"smitten")==0)
		{
			this->idle();
		}
	}
}
void ActionSprite::onFrameEvent( CCBone *bone, const char *evt, int originFrameIndex, int currentFrameIndex )
{

}
SpriteHurt* ActionSprite::GetHurt()
{
	SpriteHurt* hurt=new SpriteHurt();
	hurt->damage=this->_damage;
	hurt->hurttype=CCString::create(ATTACK_NORMAL_ATTACK);
	return hurt;
}
ActionSprite::~ActionSprite()
{
	//CC_SAFE_DELETE(_spriteBox);
}
void ActionSprite::clean()
{
	CCArmatureAnimation *adnimation=this->getAnimation();
	CC_SAFE_DELETE(adnimation);
	this->setAnimation(CCArmatureAnimation::create(this));
	int count =this->retainCount();
}
void ActionSprite::idle()
{
	if (_actionState != kActionStateIdle)
	{
		this->getAnimation()->play("loading");
		_actionState = kActionStateIdle;
		_velocity = CCPointZero;
	}
}

void ActionSprite::attack()
{
	if (_actionState == kActionStateIdle || _actionState == kActionStateWalk)
	{
		this->getAnimation()->play("attack");
		_actionState = kActionStateAttack;
	}
}
void ActionSprite::walkWithDirection( cocos2d::CCPoint direction )
{
	if (_actionState == kActionStateIdle)
	{
		this->getAnimation()->play("run");
		_actionState = kActionStateWalk;
	}
	if (_actionState == kActionStateWalk)
	{
		_velocity = ccp(direction.x * _walkSpeed, direction.y * _walkSpeed);
		if (_velocity.x >= 0)
		{
			this->setScaleX(1.0*scale);
		} 
		else
		{
			this->setScaleX(-1.0*scale);
		}
	}
}
void ActionSprite::hurtWithDamage( float damage,CCString* attackaction )
{
	if (_actionState == kActionStateKnockedDown||_actionState==kActionStateDead)
		return;
	else
	{
		float autualHp=_hitPoints-damage;
		if (autualHp <= 0)
		{
			this->knockout();
		}
		else
		{
			this->getAnimation()->play("smitten");
			_actionState = kActionStateHurt;
			this->setHitPoints(autualHp);
		}
	}
}
void ActionSprite::knockout()
{
	this->getAnimation()->play("death");
	this->setHitPoints(0);
	_actionState = kActionStateDead;
}
void ActionSprite::trick1()
{

}

void ActionSprite::SpriteUpdate( float dt )
{
	if (_actionState == kActionStateWalk)
	{
		_desiredPosition = ccpAdd(this->getPosition(), ccpMult(_velocity, dt));
	}
}

void ActionSprite::setPosition( CCPoint position )
{
	CCArmature::setPosition(position);
	UpdataBox(position,this->getScaleX());
}

void ActionSprite::setScale( float scale )
{
	CCArmature::setScale(scale);
	this->scale=scale;
}

BoundingBox ActionSprite::createBoundingBoxWithOrigin(CCPoint origin, CCSize size)   //碰撞盒子位置大小 
{
	BoundingBox boundingBox;
	boundingBox.original.origin = origin;
	boundingBox.original.size = size;
	boundingBox.actual.origin = ccpAdd(this->getPosition(), ccp(boundingBox.original.origin.x, boundingBox.original.origin.y));
	boundingBox.actual.size = size;
	return boundingBox;
}
void ActionSprite::updatePositions(float w,float h)
{
	CCRect DefaultRect=GetDefaultHitBox();
	float height= h-DefaultRect.origin.y;
	float miny=MIN(_desiredPosition.y,height);
	float posY=MAX(miny,-DefaultRect.origin.y);

	float width=w-DefaultRect.origin.x;
	float maxx=MIN(_desiredPosition.x,width-DefaultRect.size.width-DefaultRect.origin.x);
	float posX=MAX(maxx,-DefaultRect.origin.x);

	this->setPosition(ccp(posX,posY));
}