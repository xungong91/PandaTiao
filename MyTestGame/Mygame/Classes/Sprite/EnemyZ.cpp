#include "EnemyZ.h"

bool EnemyZ::init()
{
	if (!CCArmature::init("EnemyZAnimation"))
	{
		return false;
	}
	this->m_gold=80;
	this->m_goldPercentage=0.5f;
	this->setExperience(20);
	this->setHitPoints(100.0);   //受到的伤害
	this->setDamage(10.0);   
	this->setWalkSpeed(100.0);    //走路速速
	this->setScale(0.4);
	this->scale=-0.4;

	//_spriteBox=new SpriteBox(ccp(-20,-55),CCSizeMake(65,80),ccp(-65,-50),CCSizeMake(65,50));
	SetSpriteBox(ccp(-20,-55),CCSizeMake(65,80),ccp(-65,-50),CCSizeMake(65,50));
	//this->setHitbox(createBoundingBoxWithOrigin(ccp(-20,-55),CCSizeMake(65,80)));
	//this->setAttackBox(createBoundingBoxWithOrigin(ccp(-65,-50),CCSizeMake(65,50)));

	this->getAnimation()->setFrameEventCallFunc(this, frameEvent_selector(EnemyZ::onFrameEvent));
	this->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(EnemyZ::animationEvent));
	return true;
}