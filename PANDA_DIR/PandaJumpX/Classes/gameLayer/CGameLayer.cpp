#include "CGameLayer.h"
#include "Defines.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

CGameLayer::CGameLayer()
{

}

CGameLayer::~CGameLayer()
{

}

bool CGameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("panda.plist");
	mPandaBatchNode = SpriteBatchNode::create("panda.png");
	this->addChild(mPandaBatchNode);

	mPanda = CPandaSprite::create();
	mPandaBatchNode->addChild(mPanda);
	mPanda->run();

	auto body = PhysicsBody::createBox(mPanda->getContentSize());  
	body->setDynamic(true);
	mPanda->setPhysicsBody(body);
	
	//initWorld();
	return true;
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
	mPanda->jump();
}

void CGameLayer::update( float dt )
{
	Layer::update(dt);
	//updatePositions();
}

void CGameLayer::updatePositions()
{
	float pointX = mPanda->getDesiredPosition().x;
	float pointY = mPanda->getDesiredPosition().y;
	if (pointY < 0)
	{
		mPanda->run();
		pointY = 0;
	}
	mPanda->setPosition(mPanda->getDesiredPosition().x, pointY);
}

void CGameLayer::initWorld()
{
	// Create a world
	b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
	mWorld  = new b2World(gravity);
}
