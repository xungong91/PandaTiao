#include "GDialogLayer.h"

GDialogLayer::GDialogLayer()
{

}

GDialogLayer::~GDialogLayer()
{
	CC_SAFE_RELEASE(strings);
	_m_Dialog=NULL;
}

bool GDialogLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	strings = CCDictionary::createWithContentsOfFile("GameLanguage/SimplifiedChinese.xml"); 
	strings->retain();
	UILayer *UILayer = UILayer::create();
	Layout *UI_Dialog = static_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("dialog/UI_Dialog.ExportJson")); 
	UILayer->addWidget(UI_Dialog);
	UIWidget* TextButtonOk=UILayer->getWidgetByName("TextButtonOk");   
	UIWidget* ButtonClose=UILayer->getWidgetByName("ButtonClose"); 
	TextArea=static_cast<UITextArea*>(UILayer->getWidgetByName("TextArea"));
	UILayer->getWidgetByName("Panel")->setTouchEnabled(true);
	ButtonClose->addPushDownEvent(this,coco_pushselector(GDialogLayer::ButtonClick));
	TextButtonOk->addPushDownEvent(this,coco_pushselector(GDialogLayer::ButtonClick));
	this->addChild(UILayer);
	return true;
}
void GDialogLayer::SetDialog( const char* data,GDialogDelegate* _delegate )
{
	TextArea->setText(((CCString*)strings->objectForKey(data))->m_sString.c_str());
	this->_delegate=_delegate;
	this->data=data;
}

void GDialogLayer::ButtonClick( CCObject* sender )
{
	UIWidget* widget=static_cast<UIWidget*>(sender);
	if (strcmp(widget->getName(),"TextButtonOk")==0)
	{
		_delegate->onOkActivated(data,this);
	}
	else if (strcmp(widget->getName(),"ButtonClose")==0)
	{
		_delegate->onCancelActivated(data,this);
	}
}
GDialogLayer* GDialogLayer::_m_Dialog=NULL;
///²»ÊÇµ¥Àý
GDialogLayer* GDialogLayer::Singleton()
{
	if (_m_Dialog==NULL)
	{
		_m_Dialog= GDialogLayer::create();
		return _m_Dialog;
	}
	else
	{
		return NULL;
	}
}
