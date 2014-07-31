#ifndef _G_GAME_LAYER_H_
#define _G_GAME_LAYER_H_

#include <Box2D/Box2D.h>
#include "./include/GLES-Render.h"
#include "cocos-ext.h"
#include "cocos2d.h"
#include "string"
#include "SimpleDPad.h"
#include "Sprite/GHero.h"
#include "Defines.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class Contact
{
public:
	b2Fixture *fixtureA;
	b2Fixture *fixtureB;
};

class ContactListener : public b2ContactListener
{
	//! Callbacks for derived classes.
	virtual void BeginContact(b2Contact *contact)
	{
		if (contact)
		{
			Contact c;
			c.fixtureA = contact->GetFixtureA();
			c.fixtureB = contact->GetFixtureB();

			contact_list.push_back(c);
		}
		B2_NOT_USED(contact);
	}
	virtual void EndContact(b2Contact *contact)
	{
		contact_list.clear();
		B2_NOT_USED(contact);
	}
	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(oldManifold);
	}
	virtual void PostSolve(const b2Contact *contact, const b2ContactImpulse *impulse)
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(impulse);
	}

public:
	std::list<Contact> contact_list;
};


class GGameLayer:public CCLayer
{
public:
	virtual bool init();
	CREATE_FUNC(GGameLayer);
	virtual void draw();
	virtual void update(float delta);
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void onEnter();
	virtual void onExit();
	void heroSmitten(CCObject* object);
	void initTileMap();
	CCArray *enemy;

	CCTMXTiledMap *_tileMap;
	CCArmature *armature;
	CCSpriteBatchNode *_action;
	CC_SYNTHESIZE(GHero*,hero,Hero);
	CCRect rect;
	void updatePositions();
	void setViewpointCenter(CCPoint ccp);

	void SetWeaponint(int weaponint);
	void SetHeroAttack();
private:
	CCPhysicsSprite *bullet;
	void initWorld();
	void setViewpointCenter();
	b2World *world;
	ContactListener *listener;
	GLESDebugDraw *debugDraw;
};

#endif