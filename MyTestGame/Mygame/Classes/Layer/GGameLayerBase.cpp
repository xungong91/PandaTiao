#include "GGameLayerBase.h"
#include "Scene/GGameScene.h"
#include "Sprite/GHero.h"
#include "Sprite/EnemySprite.h"
#include "include/GFileHelper.h"
#include "Sprite/GGoldSprite.h"
#include "SimpleAudioEngine.h"

GGameLayerBase::GGameLayerBase()
{
	_tileMapSizex=1.0f;
	_spriteLayer=CCLayer::create();
	array_Gold=CCArray::create();
	array_Gold->retain();
	m_glod=CCUserDefault::sharedUserDefault()->getIntegerForKey("MY_Gold");
	this->addChild(_spriteLayer,_childSprite);
}
GGameLayerBase::~GGameLayerBase()
{
	CCObject *obj=NULL;
	CCARRAY_FOREACH(enemy,obj)
	{
		static_cast<ActionSprite*>(obj)->clean();
	}
	_player->clean();

	CC_SAFE_RELEASE(enemy);
	CC_SAFE_RELEASE(array_Gold);
	
	CCArmatureDataManager::purge();
	GUIReader::shareReader()->purgeGUIReader();
	SceneReader::sharedSceneReader()->purgeSceneReader();
	ActionManager::shareManager()->purgeActionManager();
}

void GGameLayerBase::initPlayer()
{
	_player=GHero::create();
	_player->setPosition(ccp(80, 80));
	_player->setDesiredPosition(_player->getPosition());
	_player->idle();
	_spriteLayer->addChild(_player);
}
void GGameLayerBase::initEnemy()
{

}
void GGameLayerBase::initTileMap()
{

}

void GGameLayerBase::draw()
{
	CCLayer::draw();
	//return;
	glLineWidth(1.5);
	CCRect dataRect;
	CCArray* arraychildren= _spriteLayer->getChildren();
	CCObject *obj=NULL;
	CCARRAY_FOREACH(arraychildren,obj)
	{
		ActionSprite *sprite=(ActionSprite*)obj;
		ccDrawColor4B(255, 0, 0, 255);
		dataRect=sprite->GetHitbox();
		ccDrawRect(dataRect.origin,ccp(dataRect.getMaxX(),dataRect.getMaxY()));
		ccDrawColor4B(0, 255, 0, 255);
		dataRect=sprite->GetAttackBox();
		ccDrawRect(dataRect.origin,ccp(dataRect.getMaxX(),dataRect.getMaxY()));
	}
	//float wi=150;
	//float he=100;
	//CCPoint datapoint=_player->GetCenterPoint();
	//CCPoint centerpoint;
	//CCPoint centerpoint2;
	//if (_player->getScaleX()>0)
	//{
	//	centerpoint= datapoint;
	//	centerpoint2=ccpAdd(centerpoint,ccp(wi,0));
	//}
	//else
	//{
	//	centerpoint2=datapoint;
	//	centerpoint=ccpAdd(centerpoint2,ccp(-wi,0));
	//}
	//dataRect.origin= centerpoint;
	//dataRect.size=CCSizeMake(wi,he);
	dataRect=_player->nailuorect();
	ccDrawRect(dataRect.origin,ccp(dataRect.getMaxX(),dataRect.getMaxY()));

	CCPoint points[] = {ccpAdd(_player->GetCenterPoint(),ccp(_player->getScaleX()>0?50:-50,0)) };
	ccPointSize(10);
	ccDrawColor4B(0,255,255,255);
	ccDrawPoints(points,1);
}


void GGameLayerBase::onEnter()
{ 
	CCLayer::onEnter();
	this->scheduleUpdate();
	CCObject *obj1=NULL;
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
		callfuncO_selector(GGameLayerBase::heroSmitten),SMITTENCB,obj1);    
	CCObject *obj2=NULL;
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,                         
		callfuncO_selector(GGameLayerBase::EnemySmitten),ENEMYSTTACKCB,obj2);
	CCObject *obj3=NULL;
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,                         
		callfuncO_selector(GGameLayerBase::EnemyDeath),ENEMYDEATH,obj3);
}

void GGameLayerBase::onExit()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,SMITTENCB);
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,ENEMYSTTACKCB);     
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this,ENEMYDEATH);    
	CCLayer::onExit();
}
void GGameLayerBase::EnemyDeath( CCObject* object )
{
	int a;
	CCString* ccstring=static_cast<CCString*>(object);
	stringstream ss;
	ss.str(ccstring->getCString());
	ss>>a;
	_player->SetExperience(a);
}
void GGameLayerBase::heroSmitten( CCObject* object )
{
	if (_player->getActionState()==kActionStateAttack||_player->getActionState()==kActionStateCombos||_player->getActionState()==kActionStateBuff)
	{
		SpriteHurt* hurt=static_cast<SpriteHurt*>(object);
		float damage=hurt->damage;
		CCString* string=hurt->hurttype;
		CCRect rect=_player->GetAttackBox();
		CCObject *obj;
		CCARRAY_FOREACH_REVERSE(enemy,obj)
		{
			EnemySprite *sprite=(EnemySprite*)obj;
			if (sprite->getActionState()!=kActionStateKnockedDown)
			{
				float heroY=_player->GetCenterPoint().y;
				if (strcmp(string->getCString(),ATTACK_NAILUO_ATTACK)==0)
				{
					CCRect rect1=sprite->GetHitbox();
					CCPoint pointmidx=ccpAdd(_player->nailuopoint(),ccp(0,sprite->GetDefaultHitBox().size.height));
					CCPoint worldpoint= convertToWorldSpace(pointmidx);
					if (_player->nailuorect().intersectsRect(rect1))
					{
						sprite->setDesiredPosition(_player->nailuopoint(),-_player->getScaleX());
						sprite->hurtWithDamage(damage,CCString::create(ATTACK_COMA_ATTACK));
						GGameScene::Singleton()->hudlayer->SetDamageLable(worldpoint,damage);
					}
				}
				else if(strcmp(string->getCString(),ATTACK_LVUP_ATTACK)==0)
				{
					CCPoint pointmidx=ccpAdd(sprite->GetCenterPoint(),ccp(0,sprite->GetDefaultHitBox().size.height));
					CCPoint worldpoint= convertToWorldSpace(pointmidx);
					CCPoint heropoint=_player->GetCenterPoint();
					CCPoint spritepoint=sprite->GetCenterPoint();
					float dustance= ccpDistance(heropoint,spritepoint);
					if (dustance<200)
					{
						sprite->hurtWithDamage(damage,CCString::create(ATTACK_COMA_ATTACK));
						GGameScene::Singleton()->hudlayer->SetDamageLable(worldpoint,damage);
					}
				}
				else
				{
					CCPoint pointmidx=ccpAdd(sprite->GetCenterPoint(),ccp(0,sprite->GetDefaultHitBox().size.height));
					CCPoint worldpoint= convertToWorldSpace(pointmidx);
					float sizeh=_player->getRadiusY();
					if (heroY>sprite->GetCenterPoint().y-sizeh&&heroY<sprite->GetCenterPoint().y+sizeh)
					{
						CCRect rect1=sprite->GetHitbox();
						if (rect.intersectsRect(rect1))
						{
							if (strcmp(string->getCString(),ATTACK_PAIJI_ATTACK)==0)
							{
								float hp=_player->getHitPoints()+_player->pSkill_3_ConvertedHp;
								if(hp>_player->pHitPoints)
								{
									hp=_player->pHitPoints;
								}
								_player->setHitPoints(hp);

								sprite->hurtWithDamage(damage,CCString::create(ATTACK_KNOCKDOWN_ATTACK));
								GGameScene::Singleton()->hudlayer->SetDamageLable(worldpoint,damage);
							}
							else if (strcmp(string->getCString(),ATTACK_NORMAL_ATTACK)==0||strcmp(string->getCString(),ATTACK_KNOCKDOWN_ATTACK)==0)
							{
								sprite->hurtWithDamage(damage,string);
								GGameScene::Singleton()->hudlayer->SetDamageLable(worldpoint,damage);
							}
						}
					}
				}
			}
		}
	}
	CC_SAFE_DELETE(object);
}
void GGameLayerBase::EnemySmitten( CCObject* object )
{
	EnemySprite *sprite=(EnemySprite*)object;
	float spriteY=sprite->GetHitbox().origin.y;
	if (sprite->GetAttackBox().intersectsRect(_player->GetHitbox()))
	{
		_player->hurtWithDamage(sprite->getDamage(),static_cast<CCString*>(object));
	}
}
void GGameLayerBase::LayerWin()
{
	this->unscheduleUpdate();
	int Chapter= CCUserDefault::sharedUserDefault()->getIntegerForKey("My_Chapter");
	Chapter++;
	if (Chapter==4)
		Chapter=3;
	CCUserDefault::sharedUserDefault()->setIntegerForKey("My_Chapter",Chapter);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("MY_Gold",m_glod);
	CCUserDefault::sharedUserDefault()->flush();
	GGameScene::Singleton()->hudlayer->SetPause(_PlayerWin);
}

void GGameLayerBase::heroDeal()
{
	this->unscheduleUpdate();
	GGameScene::Singleton()->hudlayer->SetPause(_EnemyWin);
}

void GGameLayerBase::update( float delta )
{
	UpdataSprite(delta);
	this->updatePositions(); //改变位置
	this->reorderActors();   //改变z轴
	this->setViewpointCenter(_player->getPosition());  //中心视角
	this->PickupGold();		//拾取金币
}
void GGameLayerBase::updatePositions()
{
	CCArray* arraychildren= _spriteLayer->getChildren();
	CCObject *obj=NULL;
	CCARRAY_FOREACH(arraychildren,obj)
	{
		ActionSprite* sprite=static_cast<ActionSprite*>(obj);
		float y=_tileMap->getMapSize().height * _tileMap->getTileSize().height*_tileMapSizex;
		sprite->updatePositions(_tileMap->getMapSize().width * _tileMap->getTileSize().width,y);
	}
}
void GGameLayerBase::reorderActors()
{
	CCArray* arraychildren= _spriteLayer->getChildren();
	CCObject *obj=NULL;
	CCARRAY_FOREACH(arraychildren,obj)
	{
		float y;
		ActionSprite *data = (ActionSprite*)obj;
		y=data->GetHitbox().origin.y;
		_spriteLayer->reorderChild(data, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - y);
	}
}
void GGameLayerBase::PickupGold()
{
	CCPoint heropoint=_player->GetCenterPoint();
	CCObject* obj=NULL;
	CCARRAY_FOREACH_REVERSE(array_Gold,obj)
	{
		GGoldSprite* gold=static_cast<GGoldSprite*>(obj);
		float distance=ccpDistance(gold->getPosition(),heropoint);
		if (distance<0)
		{
			//CCArmature* arm=CCArmature::create();
			//GGoldSprite *g=dynamic_cast<GGoldSprite*>(obj);
			//GGoldSprite *h=dynamic_cast<GGoldSprite*>(arm);
			//GGoldSprite *i=static_cast<GGoldSprite*>(arm);
		}
		if (distance<20)
		{
			int intgold=gold->PickUp();
			m_glod+=intgold;
			array_Gold->removeObject(obj);
			CCPoint pointmidx=ccpAdd(_player->GetCenterPoint(),ccp(0,_player->GetDefaultHitBox().size.height));
			CCPoint worldpoint= convertToWorldSpace(pointmidx);
			GGameScene::Singleton()->hudlayer->SetGoldLable(worldpoint,intgold);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("audio/bgm_coin_01.mp3");
		}
	}
}
void GGameLayerBase::setViewpointCenter( CCPoint position )
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	CCPoint actualPosition = ccp(x, y);

	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
	this->setPosition(viewPoint);
}

void GGameLayerBase::UpdataSprite( float dt )
{
	int alive=0;
	_player->SpriteUpdate(dt);

	CCPoint playerCenter=_player->GetCenterPoint();
	CCObject* obj=NULL;
	CCARRAY_FOREACH_REVERSE(enemy,obj)
	{
		EnemySprite *sprite=static_cast<EnemySprite*>(obj);
		if (sprite->getActionState()==kActionStateDead)
		{
			GGoldSprite* goldsprite=GGoldSprite::create();
			int gold;
			if (sprite->GetGold(gold))
			{
				goldsprite->SetShow(gold);
				goldsprite->setPosition(sprite->GetCenterPoint());
				array_Gold->addObject(goldsprite);                   //掉落金币
				this->addChild(goldsprite,_uiAnimation);
			}

			sprite->clean();
			enemy->removeObject(sprite);
			_spriteLayer->removeChild(sprite);
		}
		else
		{
			EnemySprite *sprite=static_cast<EnemySprite*>(obj);
			sprite->SpriteUpdate(dt);
			alive+=sprite->UpdataEnemy(playerCenter);
		}
	}
	alive=enemy->count();
	if (alive==0)
	{
		LayerWin();
	}
	if (_player->getActionState()==kActionStateDead)
		heroDeal();
}
void GGameLayerBase::GamePause()
{
	double AnimationInterval= CCDirector::sharedDirector()->getAnimationInterval();
	CCDirector::sharedDirector()->pause();
	CCDirector::sharedDirector()->setAnimationInterval(AnimationInterval);
	GGameScene::Singleton()->hudlayer->SetPause(_gamePause);
	return;
	this->unscheduleUpdate();
	CCArray* arr= GGameScene::Singleton()->hudlayer->getChildren();
	CCObject* obj;
	CCARRAY_FOREACH(arr,obj)
	{
		CCNode* node=static_cast<CCNode*>(obj);
		node->pauseSchedulerAndActions();
	}
}

void GGameLayerBase::GameResume()
{
	CCDirector::sharedDirector()->resume();
	return;
	this->scheduleUpdate();
	CCArray* arr= GGameScene::Singleton()->hudlayer->getChildren();
	CCObject* obj;
	CCARRAY_FOREACH(arr,obj)
	{
		CCNode* node=static_cast<CCNode*>(obj);
		node->resumeSchedulerAndActions();
	}
}