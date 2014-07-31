#include "GHudLayer.h"
#include "Scene/GGameScene.h"
#include "Defines.h"
#include <string>
#include "include/GFileHelper.h"
using namespace std;

string buttonstring="Skill_Button";

GHudLayer::GHudLayer(void)
{
	arms=0;
}

GHudLayer::~GHudLayer(void)
{
	CC_SAFE_RELEASE(array_button);
}


bool GHudLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	m_pUILayer = UILayer::create();
	m_pUILayer->scheduleUpdate();
	this->addChild(m_pUILayer,0);
	joyStick = createJoystick();
	this->addChild(joyStick,0);
	array_button=CCArray::create();
	array_button->retain();
	Layout* map_root = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/Head/HeadTest_1.ExportJson"));
	m_pUILayer->addWidget(map_root);
	RedBar=static_cast<UILoadingBar*>(m_pUILayer->getWidgetByName("RedBar"));
	BlueBar=static_cast<UILoadingBar*>(m_pUILayer->getWidgetByName("BlueBar"));
	YellowBar=static_cast<UILoadingBar*>(m_pUILayer->getWidgetByName("YellowBar"));
	LabelAtlas=static_cast<UILabelAtlas*>(m_pUILayer->getWidgetByName("LabelAtlas"));
	UIImageView *HeadImageView=static_cast<UIImageView*>(m_pUILayer->getWidgetByName("HeadImageView"));
	HeadImageView->addTouchEventListener(this,toucheventselector(GHudLayer::ArmsTouchEvent));
	arms1=static_cast<UIImageView*>(m_pUILayer->getWidgetByName("arms1"));                  
	UIButton* Button1=static_cast<UIButton*>(m_pUILayer->getWidgetByName("Button1"));         
	Button1->addTouchEventListener(this,toucheventselector(GHudLayer::ButtonTouchEvent));
	UIButton* Button2=static_cast<UIButton*>(m_pUILayer->getWidgetByName("Button2"));              
	Button2->addTouchEventListener(this,toucheventselector(GHudLayer::ButtonTouchEvent)); 
	UIButton* Button3=static_cast<UIButton*>(m_pUILayer->getWidgetByName("Button3"));              
	Button3->addTouchEventListener(this,toucheventselector(GHudLayer::ButtonTouchEvent)); 
	UIButton* Button4=static_cast<UIButton*>(m_pUILayer->getWidgetByName("Button4"));              
	Button4->addTouchEventListener(this,toucheventselector(GHudLayer::ButtonTouchEvent)); 
	array_button->addObject(Button1);
	array_button->addObject(Button2);
	array_button->addObject(Button3);
	array_button->addObject(Button4);

	SetButton();
	return true;
}
void GHudLayer::SetButton()
{
	CCObject* obj=NULL;
	int i=1;
	CCARRAY_FOREACH(array_button,obj)
	{
		MYSkillModel *model =GFileHelper::Singleton()->GetMYSkillModel(i-1);
		UIButton* button=static_cast<UIButton*>(obj);
		int num = model->SkillNum;
		button->setTag(num);
		if (num==0)
			button->setEnabled(false);
		else
		{
			button->setNormalTexture(model->Norma.c_str(),UI_TEX_TYPE_PLIST);
			button->setPressedTexture(model->Pressed.c_str(),UI_TEX_TYPE_PLIST);
		}
		i++;
	}
}

CCJoystick* GHudLayer::createJoystick()
{
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	CCJoystick* joyStick = CCJoystick::create(20, 50, false, true, false, false);
	joyStick->setPosition(ccp(0.15 * size.width,0.2 * size.height));
	joyStick->setBallTexture("ui/buttonpress.png");
	joyStick->setStickTexture("ui/stick.png");
	joyStick->setDockTexture("ui/joystickbg.png");
	return joyStick;
}


void GHudLayer::ArmsTouchEvent( CCObject* sender,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN	)
	{
		int armsnum= m_SkillDelegate->OnChangeWeapon();
		arms1->loadTexture(GFileHelper::armsarray[armsnum],UI_TEX_TYPE_PLIST);
	}
}
void GHudLayer::ButtonTouchEvent( CCObject* sender,TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN	)
	{
		float cd;
		float size;
		CCPoint point;
		UIWidget* widget=static_cast<UIWidget*>(sender);
		int num= widget->getTag();
		int index=array_button->indexOfObject(sender);
		size=index==0?0.55:0.35;
		switch (num)
		{
		case 1:
			m_SkillDelegate->onCombos();
			break;
		case 2:
			if(m_SkillDelegate->onBuff(cd))
			{
				SetCDprogress(cd,widget->getPosition(),size);
			}
			break;
		case 3:
			if(m_SkillDelegate->onPaiji(cd))
			{
				SetCDprogress(cd,widget->getPosition(),size);
			}
			break;
		case 4:
			if(m_SkillDelegate->onnailuo(cd))
			{
				SetCDprogress(cd,widget->getPosition(),size);
			}
			break;;
		case 5:
			if(m_SkillDelegate->onDuyao(cd))
			{
				SetCDprogress(cd,widget->getPosition(),size);
			}
			break;;
		default:
			break;
		}
	}
}
void GHudLayer::SetCDprogress(float dt, CCPoint point,float size )
{
	CCSprite* sprite=CCSprite::create("ui/cd.png");
	CCProgressTimer* progress=CCProgressTimer::create(sprite);
	progress->setScale(size);
	progress->setType(kCCProgressTimerTypeRadial);
	progress->setPosition(point);
	progress->setReverseProgress(true);
	this->addChild(progress,1);
	CCProgressFromTo* pro=CCProgressFromTo::create(dt,100,0);
	CCCallFuncN* callfunc=CCCallFuncN::create(this,callfuncN_selector(GHudLayer::CallFuncLable));
	progress->runAction(CCSequence::create(pro,callfunc,NULL));
}
void GHudLayer::SetDamageLable( CCPoint point,float damage)
{
	string s;
	ostringstream oss;
	oss<<"-"<<(int)damage;
	s=oss.str();
	CCLabelAtlas *label=CCLabelAtlas::create(s.c_str(),"ui/Blood_number.png",22,30,'+');
	label->setAnchorPoint(ccp(0.5,0));
	label->setPosition(ccpAdd(point,ccp(0,5)));
	this->addChild(label,1);
	CCActionInterval* actionMoveBy = CCMoveBy::create(0.4,ccp(0,20));
	CCActionInterval* actionFadeOut =CCFadeOut::create(0.3);
	CCCallFuncN* calfuncn=CCCallFuncN::create(this,callfuncN_selector(GHudLayer::CallFuncLable));
	label->runAction( CCSequence::create(actionMoveBy,actionFadeOut,calfuncn,NULL));
}
void GHudLayer::SetGoldLable( CCPoint point,int gold )
{
	string s;
	ostringstream oss;
	oss<<"gold "<<gold;
	s=oss.str();
	CCLabelBMFont *label = CCLabelBMFont::create(s.c_str(), "ui/gold.fnt");  
	label->setScale(0.5f);
	label->setAnchorPoint(ccp(0.5,0));
	label->setPosition(ccpAdd(point,ccp(0,5)));
	this->addChild(label,1);
	CCActionInterval* actionMoveBy = CCMoveBy::create(0.4,ccp(0,20));
	CCActionInterval* actionFadeOut =CCFadeOut::create(0.3);
	CCCallFuncN* calfuncn=CCCallFuncN::create(this,callfuncN_selector(GHudLayer::CallFuncLable));
	label->runAction( CCSequence::create(actionMoveBy,actionFadeOut,calfuncn,NULL));
}
void GHudLayer::CallFuncLable( CCNode* node )
{
	this->removeChild(node);
}

void GHudLayer::SetPause(HudPauseType type)
{
	GDialogLayer* dialog=GDialogLayer::Singleton();
	if (dialog)
	{
		this->addChild(dialog,2);
		switch(type)
		{
		case _gamePause:
			dialog->SetDialog("Hud_pause",this);
			break;
		case _PlayerWin:
			dialog->SetDialog("Hud_Player_Win",this);
			break;
		case _EnemyWin:
			dialog->SetDialog("Hud_Enemy_Win",this);
			break;
		default:
			break;
		}
	}
}

void GHudLayer::onOkActivated( const char* sender,CCLayer* layer )
{
	if (strcmp(sender,"Hud_pause")==0)
	{
		GGameScene::Singleton()->gamelayer->GameResume();
		GMapScene *map=GMapScene::create();
		CCDirector::sharedDirector()->replaceScene(map);
	}
	else if(strcmp(sender,"Hud_Player_Win")==0)
	{
		GMapScene *map=GMapScene::create();
		CCDirector::sharedDirector()->replaceScene(map);
	}
	else if(strcmp(sender,"Hud_Enemy_Win")==0)
	{
		GMapScene *map=GMapScene::create();
		CCDirector::sharedDirector()->replaceScene(map);
	}
}

void GHudLayer::onCancelActivated( const char* sender,CCLayer* layer )
{
	if (strcmp(sender,"Hud_pause")==0)
	{
		GGameScene::Singleton()->gamelayer->GameResume();
		this->removeChild(layer);
	}
	else
	{
		onOkActivated(sender,layer);
	}
}
void GHudLayer::bindArmature( PlayerSprite* armature )
{
	RedBarMax=armature->getHitPoints();
	BlueBarMax=armature->getManaPoints();
	YellowBarMax=armature->pExperience;
	ostringstream oss;
	oss<<armature->pLV;
	LabelAtlas->setStringValue(oss.str().c_str());
	OnSetExp(armature->pExp);
	arms1->loadTexture(GFileHelper::armsarray[armature->GetWeapon().Index],UI_TEX_TYPE_PLIST);

	m_SkillDelegate=armature;
	armature->SetPlayerDelegate(this);

	MyJoyStickDelegate* joystickDelegate = new MyJoyStickDelegate();
	joystickDelegate->setArmature(armature);
	joyStick->setDelegate(joystickDelegate);
}
void GHudLayer::OnLVUP(float lv,float hp,float mp,float exp)
{
	ostringstream oss;
	oss<<lv;
	LabelAtlas->setStringValue(oss.str().c_str());
	RedBarMax=hp;
	BlueBarMax=mp;
	YellowBarMax=exp;
}
void GHudLayer::OnSetHitPoints( float damage )
{
	RedBar->setPercent(damage/RedBarMax*100);
}

void GHudLayer::OnSetManeaPoints( float mp )
{
	BlueBar->setPercent(mp/BlueBarMax*100);
}

void GHudLayer::OnSetExp( float Exp )
{
	YellowBar->setPercent(Exp/YellowBarMax*100);
}

void MyJoyStickDelegate::onCCJoyStickUpdate( cocos2d::CCNode* sender,float angle,cocos2d::CCPoint direction,float power )
{
	_armature->walkWithDirection(direction);
}

void MyJoyStickDelegate::onCCJoyStickActivated( cocos2d::CCNode* sender )
{

}

void MyJoyStickDelegate::onCCJoyStickDeactivated( cocos2d::CCNode* sender )
{
	if (_armature->getActionState() == kActionStateWalk)
	{
		_armature->idle();
	}
}

