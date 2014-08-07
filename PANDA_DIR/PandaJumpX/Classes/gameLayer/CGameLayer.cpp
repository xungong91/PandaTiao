#include "CGameLayer.h"
#include "Defines.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define PTM_RATIO 32

CGameLayer::CGameLayer()
{

}

CGameLayer::~CGameLayer()
{
	delete mWorld;
	delete mDebugDraw;
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
	mPandaBody->SetLinearVelocity(b2Vec2(0, 10));
	//mPanda->jump();
}

void CGameLayer::update( float dt )
{
	Layer::update(dt);
	//updatePositions();
	int32 velocityIterations = 8;
	int32 positionIteratoins = 1;
	mWorld->Step( dt, velocityIterations, positionIteratoins);
	for( b2Body *b = mWorld->GetBodyList();b;b = b->GetNext() )
	{
		if(b->GetUserData() != NULL)
		{
			Sprite *myActor = (Sprite*)b->GetUserData();
			//,
			myActor->setPosition(Vec2((b->GetPosition().x )* PTM_RATIO,b->GetPosition().y * PTM_RATIO));//设置精灵位置
			myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );//设置精灵旋转方向
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

	mDebugDraw = new GLESDebugDraw( PTM_RATIO );  
	mWorld->SetDebugDraw(mDebugDraw); //注册到Box2d的world对象里面  
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
	b2BodyDef bodyDef;
	bodyDef.type=b2_dynamicBody;
	bodyDef.position.Set(mPanda->getPosition().x/PTM_RATIO,mPanda->getPosition().y/PTM_RATIO);
	bodyDef.userData = mPanda;
	mPandaBody=mWorld->CreateBody(&bodyDef);

	Size size = mPanda->getContentSize();
	b2PolygonShape shapeBox;
	shapeBox.SetAsBox(0.6, 0.6);

	b2FixtureDef fixtureDef;
	fixtureDef.shape=&shapeBox;
	fixtureDef.density=1.0f;
	fixtureDef.friction=0.3f;

	mPandaBody->CreateFixture(&fixtureDef);
}

void CGameLayer::draw( Renderer* renderer, const Mat4 &transform, uint32_t flags )
{
	glDisable(GL_TEXTURE_2D);  
	glDisableClientState(GL_COLOR_ARRAY);  
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);  

	mWorld->DrawDebugData();  

	glEnable(GL_TEXTURE_2D);  
	glEnableClientState(GL_COLOR_ARRAY);  
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);  
}
