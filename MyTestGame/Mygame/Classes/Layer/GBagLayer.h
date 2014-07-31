#ifndef _G_BAG_LAYER_H_
#define _G_BAG_LAYER_H_

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC_EXT;
USING_NS_CC;

class GBagDelegate {
public:
	virtual void onBagCloseActivated(CCLayer* layer){};
};
enum SkillButtonType
{
	ButtonType_List_Skill,
	ButtonType_My_Skill
};
class GBagLayer:public CCLayer
{
public:
	~GBagLayer();
	static GBagLayer* Singleton();
	void SetDialog(GBagDelegate *_degelate);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void onEnterTransitionDidFinish();
private:
	CREATE_FUNC(GBagLayer);
	//GSkillModel* model;
	UIButton* Close_Button;
	UITextArea* TextArea;
	CCDictionary *strings;
	GBagDelegate* m_delegate;
	CCArray* array_button;
	CCArray* array_hudbutton;
	UIImageView* m_selectImage;
	bool IsSelect;
	int SelectModelNum;
	bool init();
	static GBagLayer* m_bag;
	GBagLayer();
	void SkillTouchEvent( CCObject *pSender, TouchEventType type );
	void CloseTouchEvent( CCObject *pSender, TouchEventType type );
};

#endif