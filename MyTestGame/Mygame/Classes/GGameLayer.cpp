#include "GGameLayer.h"
#include "GMapScene.h"

bool GGameLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	} 
	initTileMap();
	hero=GHero::create();
	hero->setPosition(ccp(80, 80));
	hero->setDesiredPosition(hero->getPosition());
	hero->idle();
	this->addChild(hero);
	this->setTouchEnabled(true);
	this->scheduleUpdate();

	enemy=CCArray::create();
	enemy->retain();
	for (int i=0;i<20;i++)
	{
	CCSprite* sprite=CCSprite::create("CloseNormal.png");
	sprite->setAnchorPoint(ccp(0,0));
	sprite->setPosition(ccp(CCRANDOM_0_1()*_tileMap->getMapSize().width * _tileMap->getTileSize().width,CCRANDOM_0_1()*_tileMap->getMapSize().height * _tileMap->getTileSize().height*2/5));  
	this->addChild(sprite);
	enemy->addObject(sprite);
	}

	return true;
}

void GGameLayer::initTileMap()
{
	_tileMap=CCTMXTiledMap::create("Map1.tmx");
	CCObject *pObject = NULL;
	CCARRAY_FOREACH(_tileMap->getChildren(), pObject)
	{
		CCTMXLayer *child = (CCTMXLayer*)pObject;
		child->getTexture()->setAliasTexParameters();
	}
	this->addChild(_tileMap, -6);
}

void GGameLayer::ccTouchesBegan( CCSet *pTouches, CCEvent *pEvent )
{
	CCTouch* touch=(CCTouch*)pTouches->anyObject();
	CCPoint location= touch->getLocation();
}
void GGameLayer::SetHeroAttack()
{
	hero->attack();
}
void GGameLayer::SetWeaponint(int weaponint)
{
	CCBone* bone=hero->getBone("Layer17");
	bone->changeDisplayByIndex(weaponint,true);
}
void GGameLayer::update( float delta )
{
	hero->SpriteUpdate(delta);
	this->updatePositions();
	this->setViewpointCenter(hero->getPosition());
}

void GGameLayer::updatePositions()
{
	float posX=MIN(_tileMap->getMapSize().width * _tileMap->getTileSize().width,MAX(0,hero->getDesiredPosition().x));
	float posY=MIN(_tileMap->getMapSize().height * _tileMap->getTileSize().height*2/5,MAX(0,hero->getDesiredPosition().y));

	hero->setPosition(ccp(posX,posY));
}

void GGameLayer::setViewpointCenter(CCPoint position)
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * _tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	CCPoint actualPosition = ccp(x, y);

	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
	this->setPosition(viewPoint);
}
void GGameLayer::draw()
{
	CCLayer::draw();
	/* 三角形面积
	CCPoint vertices2[] = {  ccp(100,0),ccp(0,0), ccp(50,50) };  
	ccDrawPoly( vertices2, 3, true);  
	CCPoint pointac=ccpSub(vertices2[2],vertices2[0]);
	CCPoint pointab=ccpSub(vertices2[1],vertices2[0]);
	CCPoint pointProject=ccpProject(pointac,pointab);
	float DistanceH =ccpDistance(pointac,pointProject);
	float DistanceB=ccpDistance(vertices2[0],vertices2[1]);
	float area=DistanceH*DistanceB/2;*/

	CCAffineTransform affinetransform=hero->nodeToParentTransform();
	rect = CCRectApplyAffineTransform(hero->boundingBox(), affinetransform);
	ccDrawColor4B(100, 100, 100, 255);
	//ccDrawRect(rect.origin, ccp(rect.getMaxX(), rect.getMaxY()));

	/*ccDrawColor4B(255, 0, 0, 255);
	ccDrawRect(hero->getHitbox().actual.origin, ccp(hero->getHitbox().actual.getMaxX(),hero->getHitbox().actual.getMaxY()));

	ccDrawColor4B(0, 255, 0, 255);
	ccDrawRect(hero->getAttackBox().actual.origin, ccp(hero->getAttackBox().actual.getMaxX(),hero->getAttackBox().actual.getMaxY()));
	*/
	CCObject *obj;
	CCARRAY_FOREACH(enemy,obj)
	{
		CCSprite *sprite=(CCSprite*)obj;
		CCSize size= sprite->getContentSize();
		CCSize point=sprite->getPosition();
		CCRect rect1=CCRectMake(point.width,point.height,size.width,size.height);
		ccDrawRect(rect1.origin, ccp(rect1.getMaxX(),rect1.getMaxY()));
	}

	//ccDrawSolidRect( rect.origin, ccp(rect.getMaxX(), rect.getMaxY()),ccc4f(255,132,255,255));
	/*
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	kmGLPushMatrix();
	world->DrawDebugData();
	kmGLPopMatrix();
	*/
}

void GGameLayer::initWorld()
{
	b2Vec2 noGravity(0, 0);

	world = new b2World(noGravity);
	world->SetAllowSleeping(false);

	listener = new ContactListener();
	world->SetContactListener(listener);

	debugDraw = new GLESDebugDraw( PT_RATIO );
	world->SetDebugDraw(debugDraw);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	//        flags += b2Draw::e_jointBit;
	//        flags += b2Draw::e_aabbBit;
	//        flags += b2Draw::e_pairBit;
	//        flags += b2Draw::e_centerOfMassBit;
	debugDraw->SetFlags(flags);


	// Define the dynamic body.
	//Set up a 1m squared box in the physics world
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	b2Body *body = world->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.5f, 1.5f);//These are mid points for our 1m box

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.isSensor = true;
	body->CreateFixture(&fixtureDef);

	CCSpriteFrame *frame= CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("girl_head.png");
	bullet= CCPhysicsSprite::createWithSpriteFrame(frame);
	this->addChild(bullet);
	bullet->setB2Body(body);
	bullet->setPTMRatio(PT_RATIO);
	bullet->setPosition( ccp( 300, 100) );

	body = world->CreateBody(&bodyDef);
	armature = cocos2d::extension::CCArmature::create("Cowboy");
	armature->getAnimation()->play("Walk");
	armature->setScaleX(-0.2f);
	armature->setScaleY(0.2f);
	armature->setPosition(ccp(200,200));
	addChild(armature);
	armature->setBody(body);

	body = world->CreateBody(&bodyDef);
	hero->setBody(body);
}

void GGameLayer::onEnter()
{
	CCLayer::onEnter();
	CCNotificationCenter::sharedNotificationCenter()->addObserver(
		this,                         
		callfuncO_selector(GGameLayer::heroSmitten),  // 处理的消息的回调函数
		SMITTENCB,
		NULL);      
}
void GGameLayer::onExit()
{
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(
		this,
		SMITTENCB);
	CCLayer::onExit();
}
void GGameLayer::heroSmitten(CCObject* object)
{
}

