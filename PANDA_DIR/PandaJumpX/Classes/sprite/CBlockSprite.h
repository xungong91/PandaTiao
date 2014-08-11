#ifndef _C_BLOCK_SPRITE_H_
#define _C_BLOCK_SPRITE_H_

#include "cocos2d.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

class CBlockSprite : public Sprite
{
public:
	CBlockSprite();
	~CBlockSprite();
	static CBlockSprite *create(b2World *mWorld);
	bool init(b2World *mWorld);

	void update(float dt);
private:
	b2Body *groundBody;
	Vec2 mStartPoint;
};

#endif