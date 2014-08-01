#ifndef _G_MENU_SCENE_H_
#define _G_MENU_SCENE_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Layer\GDialogLayer.h"
#include "Layer\GTalkLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GMenuScene:public CCLayer,public GDialogDelegate
{
public:
	GMenuScene();
	~GMenuScene();
	static CCScene* Scence();
	virtual bool init();
	CREATE_FUNC(GMenuScene);
	void CloseGame();
	virtual void onOkActivated(const char* sender,CCLayer* layer);
	virtual void onCancelActivated(const char* sender,CCLayer* layer);
private:
	void Login(CCObject* pSender);
	void NewGame(CCObject* pSender);

};
#endif