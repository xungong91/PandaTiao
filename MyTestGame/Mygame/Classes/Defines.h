#ifndef _DEFINES_H_
#define _DEFINES_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>
USING_NS_CC;
USING_NS_CC_EXT;
///精灵状态
enum _ActionState {
	kActionStateNone = 0,
	kActionStateIdle,
	kActionStateAttack,
	kActionStateWalk,
	kActionStateHurt,
	kActionStateKnockedDown,
	kActionStateCombos,
	kActionStateDead,
	kActionStatecoma,
	kActionStateBuff
};
#pragma region 攻击动作相关
#define SMITTENCB "HeroSttackCallBack"
#define ENEMYSTTACKCB "EnemySttackCallBack"
#define ENEMYDEATH "EnemyDeathCallBack"
#define ATTACK_NORMAL_ATTACK "ATTACK_NORMAL_ATTACK"
#define ATTACK_KNOCKDOWN_ATTACK "ATTACK_KNOCKDOWN_ATTACK"
#define ATTACK_COMA_ATTACK "ATTACK_COMA_ATTACK"
#define ATTACK_PAIJI_ATTACK "ATTACK_PAIJI_ATTACK"
#define ATTACK_NAILUO_ATTACK "ATTACK_NAILUO_ATTACK"
#define ATTACK_LVUP_ATTACK "ATTACK_LVUP_ATTACK"
#pragma endregion

#pragma region UI相关
#define MAIN_SCENE_TAG 1000
#define MAP_SCENE_TAG 1001
#define GAME_SCENE_TAG 1002


enum _GameLayerType
{
	OneChapter=0,
	TwoChapter,
	ThreeChapter
};
enum _ChildrenType
{
	_uiAnimation=-4,
	_childSprite=-5,
	_other=-6,
};
#pragma endregion

struct BoundingBox {
	cocos2d::CCRect actual;
	cocos2d::CCRect original;
};
#define CURTIME GetCurTime()
inline float GetCurTime(){
	struct cc_timeval now;  
	CCTime::gettimeofdayCocos2d(&now, NULL);  
	unsigned long millisecs = (now.tv_sec * 1000) + (now.tv_usec / 1000); 
	return (float)millisecs; 
};
inline void SetVisibleAndTouchEnabled(UIWidget* widget,bool b) 
{
	widget->setVisible(b); 
	widget->setTouchEnabled(b); 
}

#endif