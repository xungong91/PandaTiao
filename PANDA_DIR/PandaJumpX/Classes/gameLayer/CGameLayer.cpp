#include "CGameLayer.h"
#include "Defines.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace GL;

#define PTM_RATIO 32

CGameLayer::CGameLayer()
{

}

CGameLayer::~CGameLayer()
{
	delete mWorld;
	delete mDebugDraw;
    delete mContactListener;
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
	
	initWorld();
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
	mPandaBody->SetLinearVelocity(b2Vec2(0, 8));
}

void CGameLayer::update( float dt )
{
	Layer::update(dt);
    
	int32 velocityIterations = 8;
	int32 positionIteratoins = 1;
	mWorld->Step( dt, velocityIterations, positionIteratoins);
	for( b2Body *b = mWorld->GetBodyList(); b; b = b->GetNext() )
	{
		if(b->GetUserData() != NULL)
		{
			Sprite *myActor = (Sprite*)b->GetUserData();
			myActor->setPosition(Vec2((b->GetPosition().x )* PTM_RATIO,
                                      (b->GetPosition().y * PTM_RATIO - myActor->getContentSize().height/2)));
            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
		}
	}
    
    std::list<b2Body*> toDestroy_list;
    
    for( std::list<MyContact>::iterator it = mContactListener->contact_list.begin();
        it != mContactListener->contact_list.end();
        ++it)
    {
        MyContact& contact = *it;
        
        b2Body* bodyA = contact.fixtureA->GetBody();
        b2Body* bodyB = contact.fixtureB->GetBody();
        
        Sprite* sa = (Sprite*)bodyA->GetUserData();
        Sprite* sb = (Sprite*)bodyB->GetUserData();
        if (sa && sb)
        {
            if (sa == mPanda) {
                mPanda->run();
            }
            else if (sb == mPanda)
            {
                mPanda->run();
            }
        }
    }
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
	Size winSize = Director::getInstance()->getWinSize();

	// Create a world
	b2Vec2 gravity = b2Vec2(0.0f, -10.0f);
	mWorld  = new b2World(gravity);
    mWorld->SetAllowSleeping(true);
    //碰撞
    mContactListener = new MyContactListener();
    mWorld->SetContactListener(mContactListener);

	mDebugDraw = new GLESDebugDraw( PTM_RATIO );  
	mWorld->SetDebugDraw(mDebugDraw); //◊¢≤·µΩBox2dµƒworld∂‘œÛ¿Ô√Ê  
	uint32 flags = 0;  
	flags += 1 * b2Draw::e_shapeBit;
	flags += 1 * b2Draw::e_jointBit;
	flags += 0 * b2Draw::e_aabbBit;
	flags += 0 * b2Draw::e_centerOfMassBit;
	mDebugDraw->SetFlags(flags);  

	//world box
	b2BodyDef groundBodyDef;
	groundBodyDef.position.SetZero();
	//create body
	b2Body *groundBody=mWorld->CreateBody(&groundBodyDef);
	//create Edges
	b2EdgeShape groundBox;;
	groundBox.Set(b2Vec2(0,100/PTM_RATIO),b2Vec2(winSize.width/PTM_RATIO,100/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);
	groundBox.Set(b2Vec2(0,100/PTM_RATIO),b2Vec2(0,winSize.height/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);
	groundBox.Set(b2Vec2(0,winSize.height/PTM_RATIO),b2Vec2(winSize.width/PTM_RATIO,winSize.height/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);
	groundBox.Set(b2Vec2(winSize.width/PTM_RATIO,winSize.height/PTM_RATIO),b2Vec2(winSize.width/PTM_RATIO,100/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);

	//sprite
	Size size = mPanda->getContentSize();
    
	b2BodyDef bodyDef;
	bodyDef.type=b2_dynamicBody;
	bodyDef.position.Set(mPanda->getPosition().x/PTM_RATIO,mPanda->getPosition().y/PTM_RATIO - size.height/2/PTM_RATIO);
	bodyDef.userData = mPanda;
	mPandaBody=mWorld->CreateBody(&bodyDef);
    
	b2PolygonShape shapeBox;
	shapeBox.SetAsBox(size.width/PTM_RATIO/2, size.height/PTM_RATIO/2);
    
	b2FixtureDef fixtureDef;
	fixtureDef.shape=&shapeBox;
	fixtureDef.density=1.5f;
	fixtureDef.friction=0.f;
    fixtureDef.isSensor = true;

	mPandaBody->CreateFixture(&fixtureDef);
}

void CGameLayer::draw( Renderer* renderer, const Mat4 &transform, uint32_t flags )
{
    enableVertexAttribs( VERTEX_ATTRIB_FLAG_POSITION );
    Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    mWorld->DrawDebugData();
    Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    CHECK_GL_ERROR_DEBUG();
}
