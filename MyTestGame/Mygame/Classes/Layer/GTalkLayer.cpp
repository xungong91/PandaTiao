#include "GTalkLayer.h"

bool GTalkLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	strings = CCDictionary::createWithContentsOfFile("GameLanguage/SimplifiedChinese.xml"); 
	strings->retain();
	UILayer *UILayer = UILayer::create();
	Layout *UI_Dialog = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("ui/Talk/Talk.ExportJson")); 
	UILayer->addWidget(UI_Dialog);
	TalkTextArea=static_cast<UITextArea*>(UILayer->getWidgetByName("TalkTextArea"));   
	TalkTextArea->addTouchEventListener(this,toucheventselector(GTalkLayer::AreaTestTouchEvent));
	this->addChild(UILayer);

	return true;
}

GTalkLayer::GTalkLayer()
{
	_textCurrent=0;
}

GTalkLayer::~GTalkLayer()
{
	CC_SAFE_RELEASE(strings);
	_m_talk=NULL;
}

void GTalkLayer::AreaTestTouchEvent( CCObject *pSender, TouchEventType type )
{
	if (type==TOUCH_EVENT_BEGAN)
	{
		_textCurrent++;
		if (_textCurrent>_textAreaCount)
		{
			ButtonClick(this);
			return;
		}
		char data[20];
		sprintf(data,"%s%d",_textAreastring,_textCurrent);
		TalkTextArea->setText(((CCString*)strings->objectForKey(data))->m_sString.c_str());
	}
}

void GTalkLayer::ButtonClick( CCObject* sender )
{
	_delegate->onTalkCancelActivated("",this);
}

void GTalkLayer::SetDialog(int data,GTalkDelegate* _delegate )
{
	SetTextArea(data);
	this->_delegate=_delegate;
}
GTalkLayer* GTalkLayer::_m_talk=NULL;
GTalkLayer* GTalkLayer::Singleton()
{
	if (_m_talk==NULL)
	{
		_m_talk= GTalkLayer::create();
		return _m_talk;
	}
	else
	{
		return NULL;
	}
}
void GTalkLayer::SetTextArea(int num)
{
	switch (num)
	{
	case 1:
		_textAreaCount=3;
		_textAreastring="NPC_BOSS_Talk_";
		break;
	case 2:
		_textAreaCount=4;
		_textAreastring="NPC_BOSS_Talk_2_";
		break;
	default:
		break;
	}
	AreaTestTouchEvent(NULL,TOUCH_EVENT_BEGAN);
}
