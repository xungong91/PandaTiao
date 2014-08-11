#include "CBlockSprite.h"
#include "Defines.h"


CBlockSprite::CBlockSprite()
{

}

CBlockSprite::~CBlockSprite()
{

}

CBlockSprite * CBlockSprite::create(b2World *mWorld)
{
	CBlockSprite *pRet = new CBlockSprite(); 
	if (pRet && pRet->init(mWorld)) 
	{ 
		pRet->autorelease(); 
		return pRet; 
	} 
	else 
	{ 
		delete pRet; 
		pRet = NULL; 
		return NULL; 
	} 
}

bool CBlockSprite::init(b2World *mWorld)
{
	if (!Sprite::init())
	{
		return false;
	}
	Sprite::setPosition(WINSIZE.width / 2, 350);
	mStartPoint = Vec2(WINSIZE.width / 2, 350);

	float minH = 300.0f;
	float maxH = 400.0f;

	//world box
	b2BodyDef groundBodyDef;
	groundBodyDef.position.SetZero();
	groundBodyDef.type = b2_kinematicBody;
	//create body
	groundBody=mWorld->CreateBody(&groundBodyDef);
	//create Edges
	b2EdgeShape groundBox;
	groundBox.Set(b2Vec2(0,minH/PTM_RATIO),b2Vec2(WINSIZE.width/PTM_RATIO,minH/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);

	groundBox.Set(b2Vec2(0,minH/PTM_RATIO),b2Vec2(0,maxH/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);

	groundBox.Set(b2Vec2(0,maxH/PTM_RATIO),b2Vec2(WINSIZE.width/PTM_RATIO,maxH/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);

	groundBox.Set(b2Vec2(WINSIZE.width/PTM_RATIO,maxH/PTM_RATIO),b2Vec2(WINSIZE.width/PTM_RATIO,minH/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);

	b2Vec2 bvec2 = groundBody->GetPosition();
	this->runAction(Sequence::create(MoveTo::create(5.0f, Vec2(0, 350)), NULL));
	const float gPlatformMovingFactor = 1.066681f;
	groundBody->SetLinearVelocity(b2Vec2(gPlatformMovingFactor, 0));
	this->scheduleUpdate();
	return true;
}

void CBlockSprite::update(float dt)
{
	Sprite::update(dt);
}
