#ifndef _ENEMY_SPRITE_H_
#define _ENEMY_SPRITE_H_

#include "Sprite/ActionSprite.h"

class EnemySprite:public ActionSprite
{
public:
	EnemySprite();
	~EnemySprite();
	CC_SYNTHESIZE(int,_experience,Experience);
	CC_SYNTHESIZE(float, _nextDecisionTime, NextDecisionTime);          //决定时间
	virtual int UpdataEnemy(CCPoint centerpoint);   
	virtual void onFrameEvent(CCBone *bone, const char *evt, int originFrameIndex, int currentFrameIndex);  //自定义
	virtual void hurtWithDamage(float damage,CCString* attackaction);  //受到的伤害 
	virtual void knockout();    //死了
	virtual void animationEvent(CCArmature *armature, MovementEventType movementType, const char *movementID);  //完成 开始
	void coma();
	void comaCB(float dt);
	void KnockedDown();
	void SetBeakBack();
	void setDesiredPosition(cocos2d::CCPoint var,float Vector );

	bool GetGold(int &gold);		//随机金币
protected:
	int m_gold;
	float m_goldPercentage;
};

#endif