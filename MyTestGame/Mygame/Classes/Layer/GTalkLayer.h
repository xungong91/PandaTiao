#ifndef _G_TALK_LAYER_H_
#define _G_TALK_LAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;

class GTalkDelegate {
public:
	virtual void onTalkCancelActivated(const char* num,CCLayer* layer){};
};

class GTalkLayer:public CCLayer
{
public:
	static GTalkLayer* Singleton();
	~GTalkLayer();
	GTalkDelegate *_delegate;
	void ButtonClick(CCObject* sender);
	void SetDialog(int data,GTalkDelegate* _delegate);
private:
	static GTalkLayer* _m_talk;
	CREATE_FUNC(GTalkLayer);
	bool init();
	GTalkLayer();
	CCDictionary *strings;
	UITextArea* TalkTextArea;
	char* _textAreastring; //字符
	int _textAreaCount;    //总共
	int _textCurrent;      //当前
	void SetTextArea(int data);
	void AreaTestTouchEvent( CCObject *pSender, TouchEventType type );
};
#endif