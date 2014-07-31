#include "GameLoadingScence.h"
#include "cocos-ext.h"
#include "GGameScene.h"

bool GameLoadingScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	return true;
}

void GameLoadingScene::onEnter()
{
	CCLayer::onEnter();
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	CCLayer* layer =CCLayerColor::create(ccc4(200.0f,0.0f,200.0f,255.0f));
	this->addChild(layer,0);
	label = CCLabelTTF::create("Loading.. ", "Arial", 28);
	addChild(label, 1);
	label->setPosition( ccp(s.width/2, s.height-50) );;
	schedule(schedule_selector(GameLoadingScene::Customupdate),0.5);
	layer->runAction( CCRepeatForever::create(
		CCSequence::create(
		CCFadeIn::create(1),
		CCFadeOut::create(1),
		NULL)
		)); 

	labelnum=CCLabelTTF::create("", "Arial", 28);
	labelnum->setPosition( ccp(s.width/2, s.height-80) );
	this->addChild(labelnum, 1);

	CCLOG("armature version : %s", armatureVersion());
	//¼ÓÔØ×ÊÔ´
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(
	"armature/UiAnimation0.png",
		"armature/UiAnimation0.plist",
		"armature/UiAnimation.ExportJson",this,schedule_selector(GameLoadingScene::dataLoaded));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(
		"armature/HeroAnimation0.png",
		"armature/HeroAnimation0.plist",
		"armature/Hero.ExportJson",this,schedule_selector(GameLoadingScene::dataLoaded));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(
		"armature/EnemyAnimation0.png", 
		"armature/EnemyAnimation0.plist",
		"armature/tauren.ExportJson", this, schedule_selector(GameLoadingScene::dataLoaded));
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfoAsync(
		"armature/EnemyZAnimation0.png", 
		"armature/EnemyZAnimation0.plist",
		"armature/EnemyZAnimation.ExportJson", this, schedule_selector(GameLoadingScene::dataLoaded));

}

void GameLoadingScene::dataLoaded( float percent )
{
	if (percent>=1)
	{
		dataComplete();
		return;
	}
	else
		labelnum->setString(CCString::createWithFormat("%f%%", percent*100)->getCString());
}

void GameLoadingScene::dataComplete()
{
	GGameScene *scene=GGameScene::Singleton();
	CCTransitionTurnOffTiles * ss=CCTransitionTurnOffTiles::create(0.5,scene);
	CCDirector::sharedDirector()->replaceScene(ss);
}

void GameLoadingScene::Customupdate( float delta )
{
	float a= CCRANDOM_0_1()*3;
	if (a>2)
		label->setString("Loading...");
	else if (a>1)
		label->setString("Loading.. ");
	else
		label->setString("Loading.  ");
}
