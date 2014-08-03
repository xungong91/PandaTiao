#ifndef _C_HUD_LAYER_H_
#define _C_HUD_LAYER_H_

#include "cocos2d.h"

class CHudDelegate
{
public:
	virtual void onTouchBegan(){}
};

class CHudLayer : public cocos2d::Layer
{
public:
	CHudLayer();
	~CHudLayer();
	CREATE_FUNC(CHudLayer);
	bool init();
	void setHudDelegate(CHudDelegate *hudDelegate);

	virtual bool onTouchBegan( cocos2d::Touch *touch, cocos2d::Event *unused_event );
	virtual void onEnter();
	virtual void onExit();
private:
	CHudDelegate *mHudDelegate;
};

#endif