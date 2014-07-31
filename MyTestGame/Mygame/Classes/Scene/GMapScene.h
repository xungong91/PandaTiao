#ifndef _G_MAP_SCENE_
#define _G_MAP_SCENE_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Layer\GShopLayer.h"
#include "Layer\GTalkLayer.h"
#include "Layer\GBagLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GMapScene:public CCScene,public GShopDelegate,public GTalkDelegate,public GBagDelegate
{
public:
	CREATE_FUNC(GMapScene);
	virtual bool init();
	GMapScene();
	~GMapScene();
	virtual void onEnter();
	virtual void onExit();
	virtual void onEnterTransitionDidFinish();
	void MapInit();
	void SetTextArea();
	void AreaTestTouchEvent(CCObject *pSender, TouchEventType type);
	void ButtonBlueStartTouchEvent( CCObject *pSender, TouchEventType type );
	void ShopButtonTouchEvent( CCObject *pSender, TouchEventType type );
	void BagButtonTouchEvent( CCObject *pSender, TouchEventType type );
	virtual void onShopCloseActivated(CCLayer* layer);
	virtual void onTalkCancelActivated(const char* num,CCLayer* layer);
	virtual void onBagCloseActivated(CCLayer* layer);
private:
	UILayer* m_pUILayer;
	CCLayer* m_layer;
	CCArray* array_button;
};


#endif