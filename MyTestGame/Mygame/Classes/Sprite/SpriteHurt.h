#ifndef _SPRITE_HURT_H_
#define _SPRITE_HURT_H_

#include "cocos2d.h"
USING_NS_CC;
class SpriteHurt:public CCObject
{
public:
	float damage;
	CCString* hurttype;
};

#endif