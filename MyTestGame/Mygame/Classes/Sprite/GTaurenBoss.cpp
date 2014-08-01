#include "Sprite/GTaurenBoss.h"

bool GTaurenBoss::init()
{
	if (!CCArmature::init("tauren"))
	{
		return false;
	}
	this->m_gold=200;
	this->m_goldPercentage=1.0f;
	this->setExperience(50);
	this->setHitPoints(300.0);   //受到的伤害
	this->setDamage(35.0);   
	this->setWalkSpeed(160.0);    //走路速速
	this->setScale(0.8);
	this->scale=-0.8;
	SetSpriteBox(ccp(-40,-110),CCSizeMake(130,160),ccp(-130,-100),CCSizeMake(130,100));
	this->getAnimation()->setFrameEventCallFunc(this, frameEvent_selector(GTaurenBoss::onFrameEvent));
	this->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(GTaurenBoss::animationEvent));
	return true;
}
void GTaurenBoss::hurtWithDamage( float damage,CCString* attackaction )
{
	if (_actionState == kActionStateKnockedDown||_actionState==kActionStateDead)
		return;
	else
	{
		_hitPoints -= damage;
		if (_hitPoints <= 0)
		{
			_actionState=kActionStateKnockedDown;
			_hitPoints=0;
			this->knockout();
		}
		else
		{
			bool Iscoma=_actionState==kActionStatecoma;
			const char* data=attackaction->getCString();
			if(strcmp(data,ATTACK_KNOCKDOWN_ATTACK)==0)
			{
				_actionState=kActionStateKnockedDown;
				this->KnockedDown();
			}
			else
			{
				if (!Iscoma)
				{
					if (strcmp(data,ATTACK_NORMAL_ATTACK)==0)
					{
						//this->getAnimation()->play("smitten");
						_actionState = kActionStateHurt;
					}
					else if (strcmp(data,ATTACK_COMA_ATTACK)==0)
					{
						coma();
					}
				}
				SetBeakBack();
			}
		}
	}
}
int GTaurenBoss::UpdataEnemy( CCPoint centerpoint )
{
	int alive = 0;         //活着的数量  为0游戏结束
	float distanceSQ;      //怪物和英雄的距离
	float randomChoice = 0;	//怪物的随机动作
	CCObject *pObject = NULL;
	if (_actionState==kActionStateDead){}
	else if(_actionState==kActionStatecoma||_actionState==kActionStateKnockedDown)
	{
		alive++;
	}
	else
	{
		//1                    存活的敌人
		alive++;
		if (CURTIME>this->getNextDecisionTime())
		{
			CCPoint pointHeroCenter=centerpoint;
			CCPoint pointSpriteCenter=this->GetCenterPoint();
			distanceSQ = ccpDistanceSQ(pointHeroCenter, pointSpriteCenter);
			if (distanceSQ <= 180 * 180)
			{
				this->setNextDecisionTime(CURTIME +CCRANDOM_0_1()*400+100);   //发呆的间隔时间
				randomChoice = CCRANDOM_0_1()*2;	
				if (randomChoice<1)                                            
				{
					if (pointHeroCenter.x >pointSpriteCenter.x)
					{
						this->setScaleX(1.0*this->scale);
					} 
					else
					{
						this->setScaleX(-1.0*this->scale);
					}
					this->setNextDecisionTime(this->getNextDecisionTime() + CCRANDOM_0_1()*500+500);
					this->attack();
				}
				else
				{
					this->idle();
				}
			}
			else
			{
				this->setNextDecisionTime(CURTIME + CCRANDOM_0_1()*400+100);               //追击持续时间
				randomChoice = CCRANDOM_0_1()*3;
				if (randomChoice <2)
				{
					CCPoint moveDirection = ccpNormalize(ccpSub(pointHeroCenter,pointSpriteCenter));
					this->walkWithDirection(moveDirection);
				} 
				else
				{
					this->idle();
				}
			}
		}
	}
	return alive;
}
