#ifndef _C_WORLD_LAYER_H_
#define _C_WORLD_LAYER_H_

#include "Box2D/Box2D.h"
#include "box/GLES-Render.h"
#include "cocos2d.h"

USING_NS_CC;

class MyContact
{
public:
	b2Fixture* fixtureA;
	b2Fixture* fixtureB;
};

typedef void (cocos2d::Object::*BEGIN_CALLBACK)(MyContact contact);

typedef void (cocos2d::Object::*END_CALLBACK)(MyContact contact);


class MyContactListener : public b2ContactListener
{
public:
	MyContactListener(cocos2d::Object *Delegate, BEGIN_CALLBACK begin, END_CALLBACK end) 
		: mDelegate(Delegate)
		, mBegin(begin)
		, mEnd(end)
	{

	}

	virtual void BeginContact(b2Contact* contact)
	{
		MyContact mc;
		mc.fixtureA = contact->GetFixtureA();
		mc.fixtureB = contact->GetFixtureB();

		(mDelegate->*mBegin)(mc);
		B2_NOT_USED(contact);
	}

	virtual void EndContact(b2Contact* contact)
	{
		MyContact mc;
		mc.fixtureA = contact->GetFixtureA();
		mc.fixtureB = contact->GetFixtureB();

		(mDelegate->*mEnd)(mc);
		B2_NOT_USED(contact);
	}

	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(oldManifold);
	}

	virtual void PostSolve(const b2Contact* contact, const b2ContactImpulse* impulse)
	{
		B2_NOT_USED(contact);
		B2_NOT_USED(impulse);
	}
private:
	cocos2d::Object *mDelegate;
	BEGIN_CALLBACK mBegin;
	END_CALLBACK mEnd;
};

class CWorldLayer : public Layer
{
public:
	CWorldLayer();
	virtual ~CWorldLayer();
	CREATE_FUNC(CWorldLayer);
	bool init();

	void onEnter();
	void onExit();
	void update(float dt);
	void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags);
	virtual void initWorld();
protected:
	b2World *mWorld;
	GLESDebugDraw * mDebugDraw;
};

#endif