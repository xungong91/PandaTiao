#ifndef _C_GAME_LAYER_H_
#define _C_GAME_LAYER_H_

#include "cocos2d.h"
#include "sprite/CPandaSprite.h"
#include "gameLayer/CHudLayer.h"
#include "Box2D/Box2D.h"
#include "box/GLES-Render.h"
#include <list>


#define PTM_RATIO 32

class MyContact
{
public:
    b2Fixture* fixtureA;
    b2Fixture* fixtureB;
};

class MyContactListener : public b2ContactListener
{
public:
    std::list<MyContact> contact_list;
    virtual void BeginContact(b2Contact* contact)
    {
        if (contact)
        {
            MyContact mc;
            mc.fixtureA = contact->GetFixtureA();
            mc.fixtureB = contact->GetFixtureB();
            
            contact_list.push_back(mc);
        }
        B2_NOT_USED(contact);
    }
    virtual void EndContact(b2Contact* contact)
    {
        contact_list.clear();
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
};

class CGameLayer : public cocos2d::Layer , public CHudDelegate
{
public:
	CGameLayer();
	~CGameLayer();
	CREATE_FUNC(CGameLayer);
	bool init();
	virtual void onEnter();
	virtual void onExit();

	virtual void onTouchBegan();

	virtual void update(float dt);
	void updatePositions();

	void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags);
private:
	CPandaSprite *mPanda;
	cocos2d::SpriteBatchNode *mPandaBatchNode;

	void initWorld();
	b2World *mWorld;
	b2Body *mPandaBody;
	GLESDebugDraw * mDebugDraw;
    MyContactListener *mContactListener;
};

#endif