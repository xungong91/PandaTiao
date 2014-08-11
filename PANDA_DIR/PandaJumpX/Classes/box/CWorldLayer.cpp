#include "CWorldLayer.h"
#include "cocos2d.h"
#include "Defines.h"

USING_NS_CC;
using namespace GL;

CWorldLayer::CWorldLayer()
{

}

CWorldLayer::~CWorldLayer()
{
	delete mWorld;
	delete mDebugDraw;
}

bool CWorldLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}

void CWorldLayer::onEnter()
{
	Layer::onEnter();
	this->scheduleUpdate();
}

void CWorldLayer::onExit()
{
	Layer::onExit();
}

void CWorldLayer::update( float dt )
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
			float offY = myActor->getAnchorPoint().y == 0 ? myActor->getContentSize().height/2 : 0;
			myActor->setPosition(
				Vec2((b->GetPosition().x )* PTM_RATIO,
				(b->GetPosition().y * PTM_RATIO - offY)));
			myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
		}
	}
}

void CWorldLayer::draw( cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, uint32_t flags )
{
	enableVertexAttribs( VERTEX_ATTRIB_FLAG_POSITION );
	Director::getInstance()->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	mWorld->DrawDebugData();
	Director::getInstance()->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	CHECK_GL_ERROR_DEBUG();
}

void CWorldLayer::initWorld()
{
	Size winSize = Director::getInstance()->getWinSize();

	// Create a world
	b2Vec2 gravity = b2Vec2(0.0f, -10.0f);
	mWorld  = new b2World(gravity);
	mWorld->SetAllowSleeping(true);

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
	b2EdgeShape groundBox;
	groundBox.Set(b2Vec2(0,100/PTM_RATIO),b2Vec2(winSize.width/PTM_RATIO,100/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);
	groundBox.Set(b2Vec2(0,100/PTM_RATIO),b2Vec2(0,winSize.height/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);
	groundBox.Set(b2Vec2(0,winSize.height/PTM_RATIO),b2Vec2(winSize.width/PTM_RATIO,winSize.height/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);
	groundBox.Set(b2Vec2(winSize.width/PTM_RATIO,winSize.height/PTM_RATIO),b2Vec2(winSize.width/PTM_RATIO,100/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);
}
