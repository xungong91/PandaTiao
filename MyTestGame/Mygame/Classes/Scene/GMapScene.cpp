#include "GMapScene.h"
#include "GGameScene.h"
#include "Defines.h"
#include "GameLoadingScence.h"


bool GMapScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}
	CCScene::init();
	this->setTag(MAP_SCENE_TAG);
	array_button=CCArray::create();
	array_button->retain();
	return true;
}
GMapScene::GMapScene()
{
}

GMapScene::~GMapScene()
{
	m_layer->removeAllChildren();
	CC_SAFE_RELEASE(array_button);
}

void GMapScene::onEnter()
{
	CCScene::onEnter();
	m_layer=CCLayer::create();
	m_pUILayer = UILayer::create();
	m_pUILayer->scheduleUpdate();
	m_layer->addChild(m_pUILayer,0);
	this->addChild(m_layer);

	UILayer *UILayer = UILayer::create();
	Layout *UI_Dialog = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/Talk/UiTest_2.ExportJson")); 
	UILayer->addWidget(UI_Dialog);
	this->addChild(UILayer,1);
	MapInit();
	SetTextArea();
}
void GMapScene::onEnterTransitionDidFinish()
{
	CCScene::onEnterTransitionDidFinish();
}
void GMapScene::onExit()
{
	m_pUILayer->removeFromParent();
	SceneReader::sharedSceneReader()->purgeSceneReader();
	GUIReader::shareReader()->purgeGUIReader();
	cocos2d::extension::ActionManager::shareManager()->purgeActionManager();
	CCScene::onExit();
}

void GMapScene::MapInit()
{
	Layout* map_root=static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/Map/UiTest_1.ExportJson"));
	//Layout* map_root = static_cast<Layout*>(UIHelper::instance()->createWidgetFromJsonFile("ui/Map/UiTest_1.ExportJson"));
	m_pUILayer->addWidget(map_root);
}
void GMapScene::ButtonBlueStartTouchEvent( CCObject *pSender, TouchEventType type )
{
	if (type == TOUCH_EVENT_ENDED)
	{
		int num=array_button->indexOfObject(pSender);
		switch (num)
		{
		case 0:
			GGameScene::GameLayerType=OneChapter;
			break;
		case  1:
			GGameScene::GameLayerType=TwoChapter;
			break;
		case  2:
			GGameScene::GameLayerType=ThreeChapter;
			break;
		}
		CCScene* scene =CCScene::create();
		scene->addChild(GameLoadingScene::create());
		CCDirector::sharedDirector()->replaceScene(scene);
	}
}
void GMapScene::ShopButtonTouchEvent( CCObject *pSender, TouchEventType type )
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		GShopLayer* shop=GShopLayer::Singleton();
		if (shop)
		{
			m_layer->addChild(shop,1);
			shop->SetDialog(this);
		}
	}
}
void GMapScene::BagButtonTouchEvent( CCObject *pSender, TouchEventType type )
{
	if (type == TOUCH_EVENT_BEGAN)
	{
		GBagLayer* bag=GBagLayer::Singleton();
		if (bag)
		{
			m_layer->addChild(bag,1);
			bag->SetDialog(this);
		}
	}
}
void GMapScene::SetTextArea()
{
	int MyChapter= CCUserDefault::sharedUserDefault()->getIntegerForKey("My_Chapter");
	//Chapter Button
	UIButton* Button1=static_cast<UIButton*>(m_pUILayer->getWidgetByName("Button1"));
	UIButton* Button2=static_cast<UIButton*>(m_pUILayer->getWidgetByName("Button2"));
	UIButton* Button3=static_cast<UIButton*>(m_pUILayer->getWidgetByName("Button3"));
	array_button->addObject(Button1);
	array_button->addObject(Button2);
	array_button->addObject(Button3);
	int i=1;
	CCObject* obj=NULL;
	CCARRAY_FOREACH(array_button,obj)
	{
		UIButton* button=static_cast<UIButton*>(obj);
		button->addTouchEventListener(this,toucheventselector(GMapScene::ButtonBlueStartTouchEvent));
		if (i<MyChapter)
		{
			SetVisibleAndTouchEnabled(button,true);
			button->setNormalTexture("blue1.png",UI_TEX_TYPE_PLIST);
			button->setPressedTexture("blue2.png",UI_TEX_TYPE_PLIST);
		}
		else if (i==MyChapter)
		{
			SetVisibleAndTouchEnabled(button,true);
			button->setNormalTexture("blue_ball1.png",UI_TEX_TYPE_PLIST);
			button->setPressedTexture("blue_ball2.png",UI_TEX_TYPE_PLIST);
		}
		else
		{
			SetVisibleAndTouchEnabled(button,false);
		}
		i++;
	}
	//Shop Button
	UIButton* Shop_Button=static_cast<UIButton*>(m_pUILayer->getWidgetByName("Shop_Button"));
	UIButton* Bag_Button=static_cast<UIButton*>(m_pUILayer->getWidgetByName("Bag_Button"));
	Shop_Button->addTouchEventListener(this,toucheventselector(GMapScene::ShopButtonTouchEvent));
	Bag_Button->addTouchEventListener(this,toucheventselector(GMapScene::BagButtonTouchEvent));

	if (MyChapter>2)
	{
		return;
	}
	GTalkLayer* talk=GTalkLayer::Singleton();
	if (talk)
	{
		m_layer->addChild(talk,1);
		talk->SetDialog(MyChapter,this);
	}
}

void GMapScene::onShopCloseActivated( CCLayer* layer )
{
	m_layer->removeChild(layer);
}

void GMapScene::onTalkCancelActivated(const char* num,CCLayer* layer )
{
	m_layer->removeChild(layer);
}

void GMapScene::onBagCloseActivated( CCLayer* layer )
{
	m_layer->removeChild(layer);
}