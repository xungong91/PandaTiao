#include "GGoldSprite.h"
GGoldSprite::GGoldSprite()
{

}

GGoldSprite::~GGoldSprite()
{

}

bool GGoldSprite::init()
{
	if (!CCArmature::init("UiAnimation"))
	{
		return false;
	}
	this->setAnchorPoint(ccp(0.5,0));
	this->setScale(0.4f);
	return true;
}

void GGoldSprite::SetShow( int gold)
{
	this->gold=gold;
	if (gold<100)
	{
		this->getAnimation()->play("Dollar");
	}
	else
	{
		this->getAnimation()->play("Coins");
	}
}

void GGoldSprite::SetShow( int gold,CCPoint point )
{
	SetShow(gold);
	this->setPosition(point);
}

int GGoldSprite::PickUp()
{
	CCMoveBy* moveby=CCMoveBy::create(0.4,ccp(0,20));
	CCActionInterval* actionFadeOut =CCFadeOut::create(0.3);
	this->runAction(CCSequence::create(moveby,actionFadeOut,CCCallFunc::create(this,callfunc_selector(GGoldSprite::removeforparent)),NULL));
	return gold;
}

void GGoldSprite::removeforparent()
{
	this->getParent()->removeChild(this);
}

