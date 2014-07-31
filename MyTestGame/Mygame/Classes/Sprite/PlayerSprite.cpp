#include "Sprite/PlayerSprite.h"
#include "SpriteHurt.h"
#include "include/GFileHelper.h"
#include "SimpleAudioEngine.h"

PlayerSprite::PlayerSprite()
{
	_currentNum=0;
	_isBuff=false;
	_IsCombos=false;
	_isPaiji=false;
	_isNailuo=false;
	_attackInternal=1;
	buffSpeed=0.8;
}

PlayerSprite::~PlayerSprite()
{
	CC_SAFE_DELETE_ARRAY(CombosNames);
}

void PlayerSprite::animationEvent( CCArmature *armature, MovementEventType movementType, const char *movementID )
{
	ActionSprite::animationEvent(armature,movementType,movementID);
	if (movementType==COMPLETE)
	{
		for (int i=0;i<=_combosMaxNum;i++)
		{
			if (strcmp(movementID,CombosNames[i].c_str())==0)  //攻击的回调
			{
				if (_IsCombos)
				{
					this->StartCombos();
				}
				else
				{
					this->idle();
				}
				break;
			}
		}
		if (strcmp(movementID,"buff")==0)
		{
			this->idle();
		}
	}
}

void PlayerSprite::onCombos()
{
	if (_actionState == kActionStateIdle  || _actionState == kActionStateWalk)
	{
		_actionState = kActionStateCombos;
		_IsCombos=true;
		_currentNum=0;
		this->StartCombos();
	}
	else if (_actionState == kActionStateCombos)
	{
		if (_currentNum!=0)
		{
			_IsCombos=true;
		}
	}
}

void PlayerSprite::StartCombos()
{
	if (_actionState == kActionStateIdle || _actionState == kActionStateWalk|| _actionState == kActionStateCombos)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("audio/daojian.wav");
		this->getAnimation()->play(CombosNames[_currentNum].c_str());
		_currentNum++;
		_IsCombos=false;
		if (_currentNum>_combosMaxNum)
			_currentNum=0;
	}
}
cocos2d::CCRect PlayerSprite::GetAttackBox()
{
	return SpriteBox::GetAttackBox(this->getActionState(),this->_currentNum);
}

void PlayerSprite::onFrameEvent( CCBone *bone, const char *evt, int originFrameIndex, int currentFrameIndex )
{
	if (strcmp(evt,"SttackCallBack")==0)  //攻击的回调
	{
		CCNotificationCenter::sharedNotificationCenter()->postNotification(SMITTENCB,GetHurt());
	}
	else if(strcmp(evt,"PaijiCallBack")==0)
	{
		SpriteHurt* hurt=new SpriteHurt;
		hurt->damage=this->_damage*pSkill_3_damageX;
		hurt->hurttype=CCString::create(ATTACK_PAIJI_ATTACK);
		CCNotificationCenter::sharedNotificationCenter()->postNotification(SMITTENCB,hurt);

		CCScene* f = CCDirector::sharedDirector()->getRunningScene();
		CCMoveTo* left1 = CCMoveTo::create(0.05,ccp(5,0));
		CCMoveTo* right1 = CCMoveTo::create(0.05,ccp(-5,0));
		CCMoveTo* top1 = CCMoveTo::create(0.05,ccp(0,5));
		CCMoveTo* rom1 = CCMoveTo::create(0.05,ccp(0,-5));
		CCFiniteTimeAction* action3 = CCSequence::create(left1,right1,top1,rom1,left1->reverse(),right1->reverse(),top1->reverse(),rom1->reverse(),NULL);
		CCRepeat *action = CCRepeat::create(action3,1);

		f->runAction(action3);
	}
}

bool PlayerSprite::onBuff(float &cd,float mana)
{
	bool BCast=false;
	float autualMP=_manaPoints-mana;
	if (!_isBuff&&autualMP>=0)
	{
		_isBuff=true;
		this->_actionState=kActionStateBuff;
		this->getAnimation()->play("buff");
		float aninal=this->getAnimation()->getAnimationInternal();
		this->getAnimation()->setAnimationInternal(aninal*buffSpeed);
		setManaPoints(autualMP);
		this->_damage=(pDamage+GetWeapon().Damage)*pSkill_2_danageX;
		this->_walkSpeed=pWalkSpeed*pSkill_2_Walk;

		this->scheduleOnce(schedule_selector(PlayerSprite::BuffCancel),pSkill_2_time);
		this->scheduleOnce(schedule_selector(PlayerSprite::BuffTimeOff),pSkill_2_CD);

		//创建一个CCParticleSystem粒子系统  
		ParticleNode=CCNode::create();
		//创建一个CCParticleSystemQuad系统：每个粒子用4个点(Quad,矩形)表示的粒子系统  
		CCParticleSystemQuad* emitter1 = CCParticleSystemQuad::create("armature/Particle_Buff.plist");  
		emitter1->setBlendAdditive(false);//是否混合  
		emitter1->setPosition(this->GetCenterOriginalPoint());  
		ParticleNode->addChild(emitter1, 0, 1);
		this->addChild(ParticleNode,10);
		cd=pSkill_2_CD;
		BCast=true;
	}
	return BCast;
}
void PlayerSprite::BuffCancel( float dt )
{
	float aninal=this->getAnimation()->getAnimationInternal();
	this->getAnimation()->setAnimationInternal(aninal/buffSpeed);
	this->_damage=pDamage+GetWeapon().Damage;
	this->_walkSpeed=pWalkSpeed;
	this->removeChild(ParticleNode);
}
void PlayerSprite::BuffTimeOff( float dt )
{
	_isBuff=false;
}

bool PlayerSprite::onPaiji(float &cd)
{
	bool BCast=false;
	if (_actionState==kActionStateIdle||_actionState==kActionStateWalk)
	{
		if (!_isPaiji)
		{
			_isPaiji=true;
			this->getAnimation()->play("paiji");
			_actionState = kActionStateAttack;
			this->scheduleOnce(schedule_selector(PlayerSprite::PaijiTimeOff),pSkill_3_CD);
			cd=pSkill_3_CD;
			BCast=true;
		}
	}
	return BCast;
}

void PlayerSprite::PaijiTimeOff( float dt )
{
	_isPaiji=false;
}

bool PlayerSprite::onnailuo(float &cd)
{
	bool BCast=false;
	if (_actionState==kActionStateIdle||_actionState==kActionStateWalk)
	{
		if (!_isNailuo)
		{
			_isNailuo=true;
			this->getAnimation()->play("buff");
			SpriteHurt* hurt=new SpriteHurt;
			hurt->damage=pSkill_4_damage;
			hurt->hurttype=CCString::create(ATTACK_NAILUO_ATTACK);
			_actionState = kActionStateBuff;
			CCNotificationCenter::sharedNotificationCenter()->postNotification(SMITTENCB,hurt);
			this->scheduleOnce(schedule_selector(PlayerSprite::NailuoTimeOff),pSkill_4_CD);
			cd=pSkill_4_CD;
			BCast=true;
		}
	}
	return BCast;
}
void PlayerSprite::NailuoTimeOff( float dt )
{
	_isNailuo=false;
}

cocos2d::CCRect PlayerSprite::nailuorect()
{
	CCRect dataRect;
	float wi=pSkill_4_w;
	float he=pSkill_4_h;
	CCPoint datapoint=this->GetCenterPoint();
	CCPoint centerpoint;
	CCPoint centerpoint2;
	float juli;
	if (this->getScaleX()>0)
	{
		centerpoint= datapoint;
		centerpoint2=ccpAdd(centerpoint,ccp(wi,0));
		juli=50;
	}
	else
	{
		centerpoint2=datapoint;
		centerpoint=ccpAdd(centerpoint2,ccp(-wi,0));
		juli=-50;
	}
	centerpoint=ccpAdd(centerpoint,ccp(0,-he/3));
	dataRect.origin= centerpoint;
	dataRect.size=CCSizeMake(wi,he);
	return dataRect;
}

cocos2d::CCPoint PlayerSprite::nailuopoint()
{
	float w=CCRANDOM_0_1()*20+50;
	float h=CCRANDOM_0_1()*20-10;
	return ccpAdd(this->GetCenterPoint(),ccp(this->getScaleX()>0?w:-w,h));
}

void PlayerSprite::SetPlayerDelegate( PlayerDelegate* _delegate )
{
	m_PlayerDelegate=_delegate;
}

void PlayerSprite::setHitPoints( float var )
{
	this->_hitPoints=var;
	m_PlayerDelegate->OnSetHitPoints(var);
}
void PlayerSprite::setManaPoints(float var)
{
	this->_manaPoints=var;
	m_PlayerDelegate->OnSetManeaPoints(var);
}

float PlayerSprite::getManaPoints()
{
	return _manaPoints;
}

void PlayerSprite::SetExperience( int ex )
{
	int num=ex+pExp;
	if (num>pExperience)
	{
		if (pLV<10)
		{
			pLV+=1;
			pExp=num-pExperience;

			float Internal=this->getAnimation()->getAnimationInternal();
			this->getAnimation()->setAnimationInternal(Internal/pAttackSpeed); //攻击速度改回来
			SetLv(pLV);
			///增加技能点
			GFileHelper::Singleton()->SetAddSkillPoints(pSkillPoints);
			SetPower();					//更改能力
			this->_hitPoints=pHitPoints;
			this->_manaPoints=pManaPoints;   //改变血量

			m_PlayerDelegate->OnLVUP(pLV,pHitPoints,pManaPoints,pExperience);
			m_PlayerDelegate->OnSetHitPoints(_hitPoints);
			m_PlayerDelegate->OnSetManeaPoints(_manaPoints);

			GFileHelper::Singleton()->UpdataModels(pLV);

			SpriteHurt* hurt=new SpriteHurt;
			hurt->damage=1.0f;
			hurt->hurttype=CCString::create(ATTACK_LVUP_ATTACK);
			CCNotificationCenter::sharedNotificationCenter()->postNotification(SMITTENCB,hurt);

			ParticleNode2=CCNode::create();
			CCParticleSystemQuad* emitter2 = CCParticleSystemQuad::create("armature/lvup.plist");  
			emitter2->setBlendAdditive(false);//是否混合  
			emitter2->setPosition(ccpAdd(this->GetCenterOriginalPoint(),ccp(0,this->GetDefaultHitBox().size.height)));  
			ParticleNode2->addChild(emitter2, 0, 1);  
			this->addChild(ParticleNode2,11);
			this->scheduleOnce(schedule_selector(PlayerSprite::DeleteEmitter),4.0f);
		}
		else
		{
			pExp=pExperience;
		}
	}
	else
	{
		pExp+=ex;
	}
	m_PlayerDelegate->OnSetExp(pExp);
}
void PlayerSprite::DeleteEmitter( float dt )
{
	this->removeChild(ParticleNode2);
}
void PlayerSprite::SetPower()
{
	float data=pDamage+GetWeapon().Damage;
	this->_damage=_isBuff?data*pSkill_2_danageX:data;
	this->_walkSpeed=_isBuff?pWalkSpeed*pSkill_2_Walk:pWalkSpeed;
	SetAttackSpeed(GetWeapon().Speed);
	this->_radiusX=GetWeapon().RadiusX;
	this->_radiusY=20*GetWeapon().RadiusY;

	CCBone* bone=this->getBone("Layer17");
	bone->changeDisplayByIndex(GetWeapon().Index,true);
}
void PlayerSprite::SetAttackSpeed( float _internal )
{
	float Internal=this->getAnimation()->getAnimationInternal();
	float OriginalInternal=Internal/_attackInternal;
	this->getAnimation()->setAnimationInternal(OriginalInternal*_internal);
	_attackInternal=_internal;
}
int PlayerSprite::OnChangeWeapon()
{
	pWeaponType=pWeaponType==1?2:1;
	SetPower();
	return GetWeapon().Index;
}
