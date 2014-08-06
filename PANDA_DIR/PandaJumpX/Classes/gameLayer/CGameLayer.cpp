#include "CGameLayer.h"
#include "Defines.h"

USING_NS_CC;

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
	auto ground = Node::create();
	ground->setPhysicsBody(PhysicsBody::createEdgeSegment(Vec2(0, 20), Vec2(960, 20)));
	this->addChild(ground);

	auto box = Node::create();
	Vec2 points[4] = {Vec2(-100, -100), Vec2(-100, 100), Vec2(100, 100), Vec2(100, -100)};
	box->setPhysicsBody(PhysicsBody::createPolygon(points, 4));
	box->setPosition(WINSIZE.width/2, WINSIZE.height/2);
	addChild(box);
}
