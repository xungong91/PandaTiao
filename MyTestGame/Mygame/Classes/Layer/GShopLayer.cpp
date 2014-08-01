#include "GShopLayer.h"
#include "include/GFileHelper.h"

const char* Shop_Lock="Shop_Lock";
const char* Shop_Gold_Not="Shop_Gold_Not";
const char* Shop_Buy_true="Shop_Buy_true";
const char* Shop_Buy_false="Shop_Buy_false";
const char* Shop_Skill_MaxLv_true="Shop_Skill_MaxLv_true";
const char* Shop_Skill_Upgrade_true="Shop_Skill_Upgrade_true";
const char* Shop_WeaponGold_Not="Shop_WeaponGold_Not";
const char* Shop_Weapon_Buy_false="Shop_Weapon_Buy_false";
const char* Shop_Weapon_MaxLv_true="Shop_Weapon_MaxLv_true";

bool GShopLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	strings = CCDictionary::createWithContentsOfFile("GameLanguage/SimplifiedChinese.xml"); 
	strings->retain();
	array_uibutton=CCArray::create();
	array_uibutton->retain();
	array_weapon=CCArray::create();
	array_weapon->retain();
	SelectButtonNum=0;
	SelectWeaponNum=0;
	m_uILayer = UILayer::create();
	Layout *UI_Dialog = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/Shop/ShopTest_1.ExportJson")); 
	m_uILayer->addWidget(UI_Dialog);

	UIButton* Close_Button=static_cast<UIButton*>(m_uILayer->getWidgetByName("Close_Button"));
	Close_Button->addPushDownEvent(this,coco_pushselector(GShopLayer::ButtonClick));

	//skill_LabelPiece=static_cast<UILabel*>(UILayer->getWidgetByName("skill_LabelPiece"));
	//Gold_Label=static_cast<UILabel*>(UILayer->getWidgetByName("Gold_Label"));
	points=static_cast<UILabel*>(m_uILayer->getWidgetByName("points"));
	skill_TextArea=static_cast<UITextArea*>(m_uILayer->getWidgetByName("skill_TextArea"));
	Lv_Label=static_cast<UITextArea*>(m_uILayer->getWidgetByName("Lv_Label"));
	UIButton* skill_Button1=static_cast<UIButton*>(m_uILayer->getWidgetByName("skill_Button1"));
	skill_Button1->addTouchEventListener(this,toucheventselector(GShopLayer::ButtonTouchEvent));
	UIButton* skill_Button2=static_cast<UIButton*>(m_uILayer->getWidgetByName("skill_Button2"));
	skill_Button2->addTouchEventListener(this,toucheventselector(GShopLayer::ButtonTouchEvent));
	UIButton* skill_Button3=static_cast<UIButton*>(m_uILayer->getWidgetByName("skill_Button3"));
	skill_Button3->addTouchEventListener(this,toucheventselector(GShopLayer::ButtonTouchEvent));
	UIButton* skill_Button4=static_cast<UIButton*>(m_uILayer->getWidgetByName("skill_Button4"));
	skill_Button4->addTouchEventListener(this,toucheventselector(GShopLayer::ButtonTouchEvent));
	UIButton* skill_Button5=static_cast<UIButton*>(m_uILayer->getWidgetByName("skill_Button5"));
	skill_Button5->addTouchEventListener(this,toucheventselector(GShopLayer::ButtonTouchEvent));
	skill_Buy=static_cast<UITextButton*>(m_uILayer->getWidgetByName("skill_Buy"));
	skill_Buy->addTouchEventListener(this,toucheventselector(GShopLayer::BuyTouchEvent));
	UIWidget* TextButton1=static_cast<UIWidget*>(m_uILayer->getWidgetByName("TextButton1"));
	TextButton1->addPushDownEvent(this,coco_pushselector(GShopLayer::SkillbuttonEvent));
	UIWidget* TextButton2=static_cast<UIWidget*>(m_uILayer->getWidgetByName("TextButton2"));
	TextButton2->addPushDownEvent(this,coco_pushselector(GShopLayer::WeaponbuttonEvent));
	UIImageView* Weapon1=static_cast<UIImageView*>(m_uILayer->getWidgetByName("Weapon1"));
	Weapon1->addTouchEventListener(this,toucheventselector(GShopLayer::WeaponTouchEvent));
	UIImageView* Weapon2=static_cast<UIImageView*>(m_uILayer->getWidgetByName("Weapon2"));
	Weapon2->addTouchEventListener(this,toucheventselector(GShopLayer::WeaponTouchEvent));
	UITextButton* Weapon_buy=static_cast<UITextButton*>(m_uILayer->getWidgetByName("Weapon_buy"));
	Weapon_buy->addTouchEventListener(this,toucheventselector(GShopLayer::WeaponBuyTouchEvent));

	array_uibutton->addObject(skill_Button1);
	array_uibutton->addObject(skill_Button2);
	array_uibutton->addObject(skill_Button3);
	array_uibutton->addObject(skill_Button4);
	array_uibutton->addObject(skill_Button5);

	array_weapon->addObject(Weapon1);
	array_weapon->addObject(Weapon2);
	//model=new GSkillModel[5];
	this->addChild(m_uILayer,0);
	this->retain();
	return true;
}

GShopLayer::GShopLayer()
{

}

GShopLayer::~GShopLayer()
{
	CC_SAFE_RELEASE(strings);
	CC_SAFE_DELETE(array_uibutton);
	CC_SAFE_DELETE(array_weapon);
	//CC_SAFE_DELETE_ARRAY(model);
	CC_SAFE_DELETE(GDialogLayer::_m_Dialog);
	_m_Shop=NULL;
}

void GShopLayer::ButtonClick( CCObject* sender )
{
	_delegate->onShopCloseActivated(this);
}

void GShopLayer::SetDialog(GShopDelegate* _delegate )
{
	this->_delegate=_delegate;
	CCObject* obj;
	int i=0;
	CCARRAY_FOREACH(array_uibutton,obj)
	{
		SkillModel* model=GFileHelper::Singleton()->GetSkillModel(i);
		UIButton* button=static_cast<UIButton*>(obj);
		button->setNormalTexture(model->Norma.c_str(),UI_TEX_TYPE_PLIST);
		button->setPressedTexture(model->Pressed.c_str(),UI_TEX_TYPE_PLIST);
		i++;
	}
	CCARRAY_FOREACH(array_weapon,obj)
	{
		updataWeaponButton(obj);
	}
	Setskillpoints_Label();
	SetSkillButton(0);
	updataWeapon(array_weapon->objectAtIndex(0));
	updataGold_Label();
}

GShopLayer::CGarbo GShopLayer::garbo;
GShopLayer* GShopLayer::_m_Shop=NULL;
GShopLayer* GShopLayer::Singleton()
{
	if (_m_Shop==NULL)
	{
		_m_Shop= GShopLayer::create();
	}
	return _m_Shop;
}

void GShopLayer::ButtonTouchEvent( CCObject *pSender, TouchEventType type )
{
	if (type==TOUCH_EVENT_ENDED)
	{
		int num= array_uibutton->indexOfObject(pSender);
		SetSkillButton(num);
	}
}
void GShopLayer::SetSkillButton( int num )
{
	SkillModel* model=GFileHelper::Singleton()->GetSkillModel(num);
	if (model->Unlock)
	{
		SetGDialog(Shop_Lock);
		return;
	}
	string s;
	ostringstream oss;
	skill_TextArea->setText(model->Introduction.c_str());
	if (model->IsBuy)
		skill_Buy->setText(strings->valueForKey("Shop_Skill_Upgrade")->getCString());
	else
		skill_Buy->setText(strings->valueForKey("Shop_Skill_Buy")->getCString());
	oss<<model->SkillLv;
	s=oss.str();
	Lv_Label->setText(s.c_str());
	SelectButtonNum=num;
}

void GShopLayer::BuyTouchEvent( CCObject *pSender, TouchEventType type )
{
	if (type==TOUCH_EVENT_ENDED)
	{
		int i=SelectButtonNum;
		SkillModel* model=GFileHelper::Singleton()->GetSkillModel(i);
		if(model->Unlock)
		{
			SetGDialog(Shop_Lock);
		}
		else if (model->SkillLv==5)
		{
			SetGDialog(Shop_Skill_MaxLv_true);
		}
		else if (model->SkillLv>0)
		{
			if (skillpoints>0)
			{
				SetGDialog(Shop_Skill_Upgrade_true);
			}
			else
			{
				SetGDialog(Shop_Gold_Not);
			}
		}
		else
		{
			if (skillpoints>0)
			{
				SetGDialog(Shop_Buy_false);
			}
			else
			{
				SetGDialog(Shop_Gold_Not);
			}
		}
	}
}

void GShopLayer::Setskillpoints_Label()
{
	skillpoints=CCUserDefault::sharedUserDefault()->getIntegerForKey("My_SkillPoints");
	ostringstream oss;
	oss<<skillpoints;
	points->setText(oss.str().c_str());
}

void GShopLayer::onOkActivated( const char* sender,CCLayer* layer )
{
	if (strcmp(sender,Shop_Buy_false)==0)
	{
		int i=SelectButtonNum;
		SkillModel* model=GFileHelper::Singleton()->GetSkillModel(i);
		GFileHelper::Singleton()->SetAddSkillPoints(-1);
		model->IsBuy=true;
		model->SkillLv=model->SkillLv+1;
		GFileHelper::Singleton()->SaveSkillModel(model,i);
		static_cast<UIButton*>(array_uibutton->objectAtIndex(i))->setNormalTexture(model->Norma.c_str(),UI_TEX_TYPE_PLIST);
		SetSkillButton(SelectButtonNum);
		Setskillpoints_Label();
	}
	else if(strcmp(sender,Shop_Skill_Upgrade_true)==0)
	{
		int i=SelectButtonNum;
		SkillModel* model=GFileHelper::Singleton()->GetSkillModel(i);
		GFileHelper::Singleton()->SetAddSkillPoints(-1);
		model->SkillLv=model->SkillLv+1;
		GFileHelper::Singleton()->SaveSkillModel(model,i);
		SetSkillButton(SelectButtonNum);
		Setskillpoints_Label();
	}
	else if (strcmp(sender,Shop_Weapon_Buy_false)==0)
	{
		UILabel* skill_LabelPiece=static_cast<UILabel*>(m_uILayer->getWidgetByName("skill_LabelPiece"));
		int weaponprice;
		stringstream ss;
		ss.str(skill_LabelPiece->getStringValue());
		ss>>weaponprice;
		int gold=CCUserDefault::sharedUserDefault()->getIntegerForKey("MY_Gold");
		CCUserDefault::sharedUserDefault()->setIntegerForKey("MY_Gold",gold-weaponprice);
		GFileHelper::Singleton()->SetWeaponLvUp(SelectWeaponNum);

		CCObject* obj= array_weapon->objectAtIndex(SelectWeaponNum);
		updataWeapon(obj);
		updataWeaponButton(obj);
		updataGold_Label();
	}
	this->removeChild(layer);
}

void GShopLayer::onCancelActivated( const char* sender,CCLayer* layer )
{
	this->removeChild(layer);
}

void GShopLayer::SetGDialog( const char* data)
{
	GDialogLayer* diao=GDialogLayer::Singleton();
	if (diao)
	{
		diao->SetDialog(data,this);
		this->addChild(diao,1);
	}
}

void GShopLayer::SkillbuttonEvent( CCObject *pSender )
{
	UIPanel* Panel_Weapon=static_cast<UIPanel*>(m_uILayer->getWidgetByName("Panel_Weapon"));
	UIPanel* Panel_Skill=static_cast<UIPanel*>(m_uILayer->getWidgetByName("Panel_Skill"));
	Panel_Skill->setVisible(true);
	Panel_Skill->setZOrder(2);
	Panel_Weapon->setVisible(false);
	Panel_Weapon->setZOrder(1);
}

void GShopLayer::WeaponbuttonEvent( CCObject *pSender )
{
	UIPanel* Panel_Weapon=static_cast<UIPanel*>(m_uILayer->getWidgetByName("Panel_Weapon"));
	UIPanel* Panel_Skill=static_cast<UIPanel*>(m_uILayer->getWidgetByName("Panel_Skill"));
	Panel_Weapon->setVisible(true);
	Panel_Weapon->setZOrder(2);
	Panel_Skill->setVisible(false);
	Panel_Skill->setZOrder(1);
}

void GShopLayer::WeaponTouchEvent( CCObject *pSender, TouchEventType type )
{
	if (type==TOUCH_EVENT_ENDED)
	{
		SelectWeaponNum= updataWeapon(pSender);
	}
}

void GShopLayer::WeaponBuyTouchEvent( CCObject *pSender, TouchEventType type )
{
	if (type==TOUCH_EVENT_ENDED)
	{
		int Lv=GFileHelper::Singleton()->GetWeaponLv(SelectWeaponNum+1);
		int gold=CCUserDefault::sharedUserDefault()->getIntegerForKey("MY_Gold");
		UILabel* skill_LabelPiece=static_cast<UILabel*>(m_uILayer->getWidgetByName("skill_LabelPiece"));
		int weaponprice;
		stringstream ss;
		ss.str(skill_LabelPiece->getStringValue());
		ss>>weaponprice;
		if (weaponprice>gold)
		{
			SetGDialog(Shop_WeaponGold_Not);
		}
		else if (Lv>=5)
		{
			SetGDialog(Shop_Weapon_MaxLv_true);
		}
		else
		{
			SetGDialog(Shop_Weapon_Buy_false);
		}
	}
}

void GShopLayer::updataGold_Label()
{
	UILabel* Gold_Label=static_cast<UILabel*>(m_uILayer->getWidgetByName("Gold_Label"));
	int gold=CCUserDefault::sharedUserDefault()->getIntegerForKey("MY_Gold");
	Gold_Label->setText(CCString::createWithFormat("%d",gold)->getCString());
}

void GShopLayer::updataWeaponButton( CCObject* image )
{
	int Index=array_weapon->indexOfObject(image);
	int Lv=GFileHelper::Singleton()->GetWeaponLv(Index+1);
	CCString* ccstring=CCString::createWithFormat("select WIndex from T_Weapon where Type=%d and Lv=%d",Index+1,Lv);
	char** data1=GFileHelper::Singleton()->GetStringArray(ccstring->getCString(),1);
	int data;
	stringstream oss;
	oss.str(data1[0]);
	oss>>data;
	static_cast<UIImageView*>(image)->setTexture(GFileHelper::armsarray[data],UI_TEX_TYPE_PLIST);

	for (int i=0;i<1;i++)
	{
		CC_SAFE_DELETE_ARRAY(data1[i]);
	}
	CC_SAFE_DELETE_ARRAY(data1);
}

int GShopLayer::updataWeapon( CCObject* image )
{
	UILabel* skill_LabelPiece=static_cast<UILabel*>(m_uILayer->getWidgetByName("skill_LabelPiece"));
	UITextArea* TextArea_Weapon=static_cast<UITextArea*>(m_uILayer->getWidgetByName("TextArea_Weapon"));
	UILabel* Label_WeaponLv=static_cast<UILabel*>(m_uILayer->getWidgetByName("Label_WeaponLv"));

	int Index=array_weapon->indexOfObject(image);
	int Lv=GFileHelper::Singleton()->GetWeaponLv(Index+1);
	CCString* ccstring=CCString::createWithFormat("select Price from T_Weapon where Type=%d and Lv=%d",Index+1,Lv);
	char** data1=GFileHelper::Singleton()->GetStringArray(ccstring->getCString(),1);
	skill_LabelPiece->setText(data1[0]);
	TextArea_Weapon->setText(strings->valueForKey(CCString::createWithFormat("Weapon_Introduction%d",Index+1)->getCString())->getCString());
	Label_WeaponLv->setText(CCString::createWithFormat("%d",Lv)->getCString());
	for (int i=0;i<1;i++)
	{
		CC_SAFE_DELETE_ARRAY(data1[i]);
	}
	CC_SAFE_DELETE_ARRAY(data1);
	return Index;
}

GSkillModel::GSkillModel()
{

}

GSkillModel::~GSkillModel()
{

}
