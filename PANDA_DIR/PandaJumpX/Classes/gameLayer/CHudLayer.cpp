#include "CHudLayer.h"

USING_NS_CC;

CHudLayer::CHudLayer()
{

}

CHudLayer::~CHudLayer()
{

}

bool CHudLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CHudLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool CHudLayer::onTouchBegan( Touch *touch, Event *unused_event )
{
	Vec2 point = touch->getLocation();

	mHudDelegate->onTouchBegan();
	return false;
}

void CHudLayer::onEnter()
{
	Layer::onEnter();
}

void CHudLayer::onExit()
{
	Layer::onExit();
}

void CHudLayer::setHudDelegate( CHudDelegate *hudDelegate )
{
	mHudDelegate = hudDelegate;
}
