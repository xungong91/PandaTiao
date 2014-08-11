#include "CGameLayer.h"
#include "Defines.h"
#include "cocos-ext.h"
#include "sprite/CBlockSprite.h"

USING_NS_CC;
using namespace GL;

CGameLayer::CGameLayer()
{

}

CGameLayer::~CGameLayer()
{
    delete mContactListener;
}

bool CGameLayer::init()
{
	if (!CWorldLayer::init())
	{
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("panda.plist");
	mPandaBatchNode = SpriteBatchNode::create("panda.png");
	this->addChild(mPandaBatchNode);

	mPanda = CPandaSprite::create();
	mPandaBatchNode->addChild(mPanda);
	mPanda->run();
	
	initWorld();
	this->schedule(schedule_selector(CGameLayer::addBlock), 3.0f);

	return true;
}

void CGameLayer::reset()
{

}

void CGameLayer::onEnter()
{
	Layer::onEnter();
	this->scheduleUpdate();
}

void CGameLayer::onExit()
{
	Layer::onExit();
}

void CGameLayer::onTouchBegan()
{
	if(mPanda->jump()) 
	{
		mPandaBody->SetLinearVelocity(b2Vec2(0, 8));

		this->addChild(CBlockSprite::create(mWorld));
	}
}

void CGameLayer::update( float dt )
{
	CWorldLayer::update(dt);
	updateCheck();
}

void CGameLayer::updateCheck()
{
}

void CGameLayer::addBlock( float dt )
{

}

void CGameLayer::initWorld()
{
	CWorldLayer::initWorld();

	Size winSize = Director::getInstance()->getWinSize();

    //碰撞
    mContactListener = new MyContactListener(this, (BEGIN_CALLBACK)(&CGameLayer::beginContact), (END_CALLBACK)(&CGameLayer::endContact));
    mWorld->SetContactListener(mContactListener);

	//sprite
	Size size = mPanda->getContentSize();
    
	b2BodyDef bodyDef;
	bodyDef.type=b2_dynamicBody;
	bodyDef.position.Set(mPanda->getPosition().x/PTM_RATIO,mPanda->getPosition().y/PTM_RATIO - size.height/2/PTM_RATIO);
	bodyDef.userData = mPanda;
	mPandaBody = mWorld->CreateBody(&bodyDef);
    
	b2PolygonShape shapeBox;
	shapeBox.SetAsBox(size.width/PTM_RATIO/2, size.height/PTM_RATIO/2);
    
	b2FixtureDef fixtureDef;
	fixtureDef.shape=&shapeBox;
	fixtureDef.density=1.5f;
	fixtureDef.friction=0.f;
    //fixtureDef.isSensor = true;

	mPandaBody->CreateFixture(&fixtureDef);
}

void CGameLayer::beginContact( MyContact contact )
{
	mPanda->run();
}

void CGameLayer::endContact( MyContact contact )
{

}
