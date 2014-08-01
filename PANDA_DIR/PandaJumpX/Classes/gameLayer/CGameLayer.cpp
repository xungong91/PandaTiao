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
	mPanda->setPosition(Vec2(200, 200));
	mPandaBatchNode->addChild(mPanda);
	mPanda->run();

	return true;
}
