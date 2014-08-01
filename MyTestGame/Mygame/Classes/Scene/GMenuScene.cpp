#include "GMenuScene.h"
#include "GMapScene.h"
#include "./include/GFileHelper.h"
#include <string>
#include "Defines.h"
#include "include/AudioHelper.h"

using namespace std;


cocos2d::CCScene* GMenuScene::Scence()
{
	CCScene* scene=CCScene::create();
	CCLayer* layer=GMenuScene::create();
	scene->setTag(MAIN_SCENE_TAG);
	scene->addChild(layer);
	layer->setTag(MAIN_SCENE_TAG);
	return scene;
}

bool GMenuScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCNode *loginScene = SceneReader::sharedSceneReader()->createNodeWithSceneFile("TestSceneProject.json");
	CCNode *ui=loginScene->getChildByTag(10012);
	CCComponent *component =ui->getComponent("GUIComponent");
	UILayer* uilayer=static_cast<UILayer*>(component->getNode());
	//static_cast<UIImageView*>(uilayer->getWidgetByName("ImageView"))->setVisible(false);
	UIWidget* button=uilayer->getWidgetByName("Button");            //1
	button->addPushDownEvent(this,coco_pushselector(GMenuScene::Login));
	UIWidget* TextButton=uilayer->getWidgetByName("TextButton");        //2
	TextButton->addPushDownEvent(this,coco_pushselector(GMenuScene::NewGame));
	this->addChild(loginScene);

	GFileHelper::Singleton()->CreateOrOpen();
	AudioHelper::Singleton()->PlayLoginBackMusic(true);
	return true;
}
void GMenuScene::Login(CCObject* pSender)
{
	CCTransitionScene * reScene = NULL;
	CCScene * s = GMapScene::create();
	float t = 1.0f;
	reScene = CCTransitionFade::create(t, s);
	CCDirector::sharedDirector()->replaceScene(reScene);
}

void GMenuScene::NewGame( CCObject* pSender )
{
	GDialogLayer* dialog=GDialogLayer::Singleton();
	if (dialog)
	{
		this->addChild(dialog,2);
		dialog->SetDialog("Main_Menu_New_Game",this);
	}
}
void GMenuScene::CloseGame()
{
	GDialogLayer* dialog=GDialogLayer::Singleton();
	if (dialog)
	{
		this->addChild(dialog,2);
		dialog->SetDialog("Main_Menu_End_Game",this);
	}
}

void GMenuScene::onOkActivated( const char* sender ,CCLayer* layer)
{
	if (strcmp(sender,"Main_Menu_New_Game")==0)
	{
		GFileHelper::Singleton()->CreateNewFile();
		Login(NULL);
	}
	else if(strcmp(sender,"Main_Menu_End_Game")==0)
	{
		CCDirector::sharedDirector()->end();
	}
}

void GMenuScene::onCancelActivated( const char* sender,CCLayer* layer )
{
	this->removeChild(layer);
}

GMenuScene::GMenuScene()
{

}

GMenuScene::~GMenuScene()
{
	CCArmatureDataManager::purge();
	SceneReader::sharedSceneReader()->purgeSceneReader();
	GUIReader::shareReader()->purgeGUIReader();
	cocos2d::extension::ActionManager::shareManager()->purgeActionManager();
}


