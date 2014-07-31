#ifndef _HUD_LAYER_H_
#define _HUD_LAYER_H_

#include "cocos2d.h"
#include "Sprite/PlayerSprite.h"
#include "./include/CCJoyStick.h"
#include "GDialogLayer.h"

USING_NS_CC;
enum HudPauseType
{
	_PlayerWin=0,
	_EnemyWin,
	_gamePause
};
class GHudLayer:public CCLayer,public GDialogDelegate,public PlayerDelegate
{
public:
	GHudLayer();
	~GHudLayer();
	bool init();
	CREATE_FUNC(GHudLayer);
	void bindArmature(PlayerSprite* armature);
	int arms;

	UILayer* m_pUILayer;
	void ArmsTouchEvent(CCObject* sender,TouchEventType type);
	void ButtonTouchEvent(CCObject* sender,TouchEventType type);
	void SetDamageLable(CCPoint point,float damage);           //显示伤害
	void SetGoldLable(CCPoint point,int gold);
	cocos2d::CCLabelTTF *label;          //测试
	void SetPause(HudPauseType type);
	void SetButton();
	virtual void onOkActivated(const char* sender,CCLayer* layer);
	virtual void onCancelActivated(const char* sender,CCLayer* layer);
	virtual void OnSetHitPoints(float hp);
	virtual void OnSetManeaPoints(float mp);
	virtual void OnSetExp(float Exp);
	virtual void OnLVUP(float lv,float hp,float mp,float exp);
protected:
	SkillDelegate* m_SkillDelegate;
	CCJoystick* createJoystick();
	CCJoystick* joyStick;
	CCArray* array_button;
	float RedBarMax;
	float BlueBarMax;
	int YellowBarMax;
	void SetCDprogress(float dt,CCPoint point,float size);
	void CallFuncLable(CCNode* node);
	UILoadingBar* RedBar;			//血量hp
	UILoadingBar* BlueBar;			//蓝量mp
	UILoadingBar* YellowBar;		//经验值exp
	UILabelAtlas* LabelAtlas;		//等级lv
	UIImageView* arms1;				//武器
};
class MyJoyStickDelegate : public CCJoyStickDelegate
{
public:
    void onCCJoyStickUpdate(cocos2d::CCNode* sender,float angle,cocos2d::CCPoint direction,float power);
    /**
     *  to active joystick
     */
    void onCCJoyStickActivated(cocos2d::CCNode* sender);
    /**
     *  to deactive joystick
     */
    void onCCJoyStickDeactivated(cocos2d::CCNode* sender);

	CC_SYNTHESIZE(ActionSprite*,_armature,Armature);
protected:
};

#endif