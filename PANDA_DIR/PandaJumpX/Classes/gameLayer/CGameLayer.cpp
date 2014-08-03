#include "CGameLayer.h"

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
	mPandaBatchNode = CCSpriteBatchNode::create("panda.png");
	this->addChild(mPandaBatchNode);

	mPanda = CPandaSprite::create();
	mPandaBatchNode->addChild(mPanda);
	mPanda->run();
	
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
	updatePositions();
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
