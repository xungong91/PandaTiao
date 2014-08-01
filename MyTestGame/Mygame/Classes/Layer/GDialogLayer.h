#ifndef _G_DIALOG_LAYER_H_
#define _G_DIALOG_LAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;


class GDialogDelegate {
public:
	virtual void onOkActivated(const char* sender,CCLayer* layer){};
	virtual void onCancelActivated(const char* sender,CCLayer* layer){};
};

class GDialogLayer:public CCLayer
{
public:
	static GDialogLayer* Singleton();
	~GDialogLayer();
	GDialogDelegate *_delegate;
	void ButtonClick(CCObject* sender);
	void SetDialog(const char* data,GDialogDelegate* _delegate);
	static GDialogLayer* _m_Dialog;
private:
	CREATE_FUNC(GDialogLayer);
	bool init();
	GDialogLayer();
	CCDictionary *strings;
	UITextArea* TextArea;
	const char* data;
};

#endif