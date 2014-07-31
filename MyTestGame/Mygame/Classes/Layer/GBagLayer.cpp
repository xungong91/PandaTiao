#include "GBagLayer.h"
#include "include/GFileHelper.h"

GBagLayer::GBagLayer()
{
	IsSelect=false;
	SelectModelNum=0;
	//model=new GSkillModel[5];
}

bool GBagLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	this->setTouchEnabled(true);
	strings = CCDictionary::createWithContentsOfFile("GameLanguage/SimplifiedChinese.xml"); 
	strings->retain();
	array_button=CCArray::create();
	array_button->retain();
	array_hudbutton=CCArray::create();
	array_hudbutton->retain();
	UILayer* UILayer = UILayer::create();
	Layout *UI_Dialog = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/bag/bagTest_1.ExportJson")); 
	UILayer->addWidget(UI_Dialog);
	Close_Button=static_cast<UIButton*>(UILayer->getWidgetByName("Close_Button"));
	TextArea=static_cast<UITextArea*>(UILayer->getWidgetByName("TextArea"));
	UIButton* Button1=static_cast<UIButton*>(UILayer->getWidgetByName("Button1"));
	UIButton* Button2=static_cast<UIButton*>(UILayer->getWidgetByName("Button2"));
	UIButton* Button3=static_cast<UIButton*>(UILayer->getWidgetByName("Button3"));
	UIButton* Button4=static_cast<UIButton*>(UILayer->getWidgetByName("Button4"));
	UIButton* Button5=static_cast<UIButton*>(UILayer->getWidgetByName("Button5"));
	array_button->addObject(Button1);
	array_button->addObject(Button2);
	array_button->addObject(Button3);
	array_button->addObject(Button4);
	array_button->addObject(Button5);
	UIButton* HudButton1=static_cast<UIButton*>(UILayer->getWidgetByName("HudButton1"));
	UIButton* HudButton2=static_cast<UIButton*>(UILayer->getWidgetByName("HudButton2"));
	UIButton* HudButton3=static_cast<UIButton*>(UILayer->getWidgetByName("HudButton3"));
	UIButton* HudButton4=static_cast<UIButton*>(UILayer->getWidgetByName("HudButton4"));
	array_hudbutton->addObject(HudButton1);
	array_hudbutton->addObject(HudButton2);
	array_hudbutton->addObject(HudButton3);
	array_hudbutton->addObject(HudButton4);
	m_selectImage=UIImageView::create();
	//m_selectImage->setTexture(Normalpng[0],UI_TEX_TYPE_PLIST);
	m_selectImage->setScale(0.6);
	m_selectImage->setPosition(ccp(100,100));
	m_selectImage->setVisible(false);
	UILayer->addWidget(m_selectImage);
	this->addChild(UILayer);
	return true;
}
GBagLayer::~GBagLayer()
{
	CC_SAFE_DELETE(strings);
	CC_SAFE_DELETE(array_button);
	CC_SAFE_DELETE(array_hudbutton);
	//CC_SAFE_DELETE(model);
	m_bag=NULL;
}
void GBagLayer::SetDialog( GBagDelegate *_degelate )
{
	this->m_delegate=_degelate;
	CCObject* obj;
	int i=0;
	CCARRAY_FOREACH(array_button,obj)
	{
		UIButton* button =static_cast<UIButton*>(obj);
		SkillModel* model=GFileHelper::Singleton()->GetSkillModel(i);
		if (model->IsBuy)
			button->setNormalTexture(model->Norma.c_str(),UI_TEX_TYPE_PLIST);
		else
			button->setNormalTexture(model->light_skill.c_str(),UI_TEX_TYPE_PLIST);
		i++;
	}
	i=0;
	CCARRAY_FOREACH(array_hudbutton,obj)
	{
		UIButton* button =static_cast<UIButton*>(obj);
		MYSkillModel *model=GFileHelper::Singleton()->GetMYSkillModel(i);
		if (model->SkillNum!=0)
		{
			button->setNormalTexture(model->Norma.c_str(),UI_TEX_TYPE_PLIST);
		}
		else
		{
			button->setNormalTexture(model->light_skill.c_str(),UI_TEX_TYPE_PLIST);
		}
		//SetButtonImage(button,i,ButtonType_My_Skill);
		i++;
	}
}
GBagLayer* GBagLayer::m_bag=NULL;
GBagLayer* GBagLayer::Singleton()
{
	if (m_bag==NULL)
	{
		m_bag=GBagLayer::create();
	}
	return m_bag;
}
void GBagLayer::SkillTouchEvent( CCObject *pSender, TouchEventType type )
{

}
void GBagLayer::CloseTouchEvent( CCObject *pSender, TouchEventType type )
{
	m_delegate->onBagCloseActivated(this);
}
void GBagLayer::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint location= pTouch->getLocation();
	IsSelect=false;
	m_selectImage->setVisible(false);
	CCObject* obj;
	int i=0;
	CCARRAY_FOREACH(array_hudbutton,obj)
	{
		UIButton* button=static_cast<UIButton*>(obj);
		CCPoint bpoint=button->getPosition();
		float distance=ccpDistance(location,bpoint);
		if (distance<20.0f)
		{
			MYSkillModel* mymodel =GFileHelper::Singleton()->GetMYSkillModel(i);
			mymodel->SkillNum=SelectModelNum+1;
			GFileHelper::Singleton()->SaveMYSkillModel(mymodel,i);
			SkillModel* model=GFileHelper::Singleton()->GetSkillModel(SelectModelNum);
			button->setNormalTexture(model->Norma.c_str(),UI_TEX_TYPE_PLIST);
			return;
		}
		i++;
	}
}
void GBagLayer::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	if (IsSelect)
	{
		CCPoint location= pTouch->getLocation();
		m_selectImage->setPosition(location);
	}
}
bool GBagLayer::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint location= pTouch->getLocation();
	if (ccpDistance(location,Close_Button->getPosition())<40.0f)
	{
		CCRect r=Close_Button->getRect();
		if (r.intersectsRect(CCRectMake(location.x,location.y,1,1)))
		{
			CloseTouchEvent(NULL,TOUCH_EVENT_BEGAN);
			return false;
		}
	}
	int i=0;
	CCObject* obj=NULL;
	CCARRAY_FOREACH(array_button,obj)
	{
		UIButton* button=static_cast<UIButton*>(obj);
		SkillModel* model= GFileHelper::Singleton()->GetSkillModel(i);
		if (model->IsBuy)
		{
			CCPoint bpoint=button->getPosition();
			float distance=ccpDistance(location,bpoint);
			if (distance<20.0f)
			{
				IsSelect=true;
				SelectModelNum=i;
				TextArea->setText(model->Introduction.c_str());
				m_selectImage->setVisible(true);
				m_selectImage->setPosition(location);
				m_selectImage->setTexture(model->Norma.c_str(),UI_TEX_TYPE_PLIST);
				return true;
			}
			i++;
		}
	}
	i=0;
	CCARRAY_FOREACH(array_hudbutton,obj)
	{
		UIButton* button=static_cast<UIButton*>(obj);
		CCPoint bpoint=button->getPosition();
		float distance=ccpDistance(location,bpoint);
		if (distance<20.0f)
		{
			MYSkillModel* mymodel =GFileHelper::Singleton()->GetMYSkillModel(i);
			mymodel->SkillNum=0;
			GFileHelper::Singleton()->SaveMYSkillModel(mymodel,i);
			button->setNormalTexture(mymodel->light_skill.c_str(),UI_TEX_TYPE_PLIST);
			return false;
		}
		i++;
	}
	return false;
}
void GBagLayer::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
}
