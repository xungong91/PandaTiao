#include "Sprite/EnemySprite.h"
#include <string>

using namespace std;

EnemySprite::EnemySprite()
{
	_nextDecisionTime = 0;
}

EnemySprite::~EnemySprite()
{
}

int EnemySprite::UpdataEnemy( CCPoint centerpoint )
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
			if (distanceSQ <= 60 * 60)
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
				if (randomChoice <1)
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

void EnemySprite::onFrameEvent( CCBone *bone, const char *evt, int originFrameIndex, int currentFrameIndex )
{
	if (strcmp(evt,"SttackCallBack")==0)  //攻击的回调
	{
		CCNotificationCenter::sharedNotificationCenter()->postNotification(ENEMYSTTACKCB,this);
	}
}
void EnemySprite::hurtWithDamage( float damage,CCString* attackaction )
{
	if (_actionState == kActionStateKnockedDown||_actionState==kActionStateDead)
		return;
	else
	{
		_hitPoints -= damage;
		if (_hitPoints <= 0)
		{
			_hitPoints=0;
			this->knockout();
		}
		else
		{
			bool Iscoma=_actionState==kActionStatecoma;
			const char* data=attackaction->getCString();
			if(strcmp(data,ATTACK_KNOCKDOWN_ATTACK)==0)
			{
				this->KnockedDown();
			}
			else
			{
				if (!Iscoma)
				{
					if (strcmp(data,ATTACK_NORMAL_ATTACK)==0)
					{
						_actionState = kActionStateHurt;
						this->getAnimation()->play("smitten");
					}
					else if (strcmp(data,ATTACK_COMA_ATTACK)==0)
					{
						this->unschedule(schedule_selector(EnemySprite::comaCB));
						coma();
					}
				}
				SetBeakBack();
			}
		}
	}
}
void EnemySprite::knockout()
{
	_actionState=kActionStateKnockedDown;
	this->getAnimation()->play("death");
	CCNotificationCenter::sharedNotificationCenter()->postNotification(ENEMYDEATH,CCString::createWithFormat("%d",_experience));
}

void EnemySprite::coma()
{
	this->_actionState=kActionStatecoma;
	this->getAnimation()->play("coma");
	this->scheduleOnce(schedule_selector(EnemySprite::comaCB),2.0f);
}
void EnemySprite::comaCB( float dt )
{
	if (_actionState==kActionStateKnockedDown||_actionState==kActionStateDead)
		return;
	this->idle();
}
void EnemySprite::KnockedDown()
{
	_actionState=kActionStateKnockedDown;
	this->getAnimation()->play("Knockdown");
}

void EnemySprite::animationEvent( CCArmature *armature, MovementEventType movementType, const char *movementID )
{
	ActionSprite::animationEvent(armature,movementType,movementID);
	if (movementType==COMPLETE)
	{
		if (strcmp(movementID,"Knockdown")==0)
		{
			this->idle();
		}
		if (strcmp(movementID,"death")==0)
		{
			_actionState=kActionStateDead;
		}
	}
}
void EnemySprite::SetBeakBack()
{
	float postion=this->getScaleX()>0?10:-10;
	_desiredPosition=ccpAdd(_desiredPosition,ccp(postion,0));
}

void EnemySprite::setDesiredPosition( cocos2d::CCPoint var,float Vector )
{
	float w=GetDefaultHitBox().size.width;
	float y=GetDefaultHitBox().origin.y;
	float x=Vector<0?GetDefaultHitBox().origin.x+w/2:-GetDefaultHitBox().origin.x-w/2;
 	CCPoint point=ccp(x,y);
	_desiredPosition=ccpSub(var,point);
}

bool EnemySprite::GetGold( int &gold )
{
	gold=(int)(CCRANDOM_0_1()*100)-50+m_gold;
	float data=CCRANDOM_0_1();
	if (data<m_goldPercentage)
	{
		return true;
	}
	return false;
}

