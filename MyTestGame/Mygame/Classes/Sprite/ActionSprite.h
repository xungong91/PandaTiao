#ifndef _ACTION_SPRITE_H_
#define _ACTION_SPRITE_H_

#include "cocos2d.h"
#include "Sprite/SpriteBox.h"
#include "Defines.h"
#include "cocos-ext.h"
#include "SpriteHurt.h"

USING_NS_CC;
USING_NS_CC_EXT;

class ActionSprite:public CCArmature,public SpriteBox
{
public:
	ActionSprite();
	~ActionSprite();

	//action
	void idle();  //闲置
	virtual void attack();    //攻击
	virtual void hurtWithDamage(float damage,CCString* attackaction);  //受到的伤害 
	virtual void knockout();    //死了
	void walkWithDirection(cocos2d::CCPoint direction);  //走的方向
	void trick1();   //特殊技能
	//states
	CC_SYNTHESIZE(_ActionState, _actionState, ActionState);
	//movement
	CC_SYNTHESIZE(cocos2d::CCPoint, _velocity, Velocity); //方向
	CC_SYNTHESIZE(cocos2d::CCPoint, _desiredPosition, DesiredPosition);  //位置
	void updatePositions(float w,float h);
	//attributes  包含精灵行走速度值，受伤时减少生命点值，攻击伤害值。
	CC_SYNTHESIZE(float, _hitPoints, HitPoints);
	CC_SYNTHESIZE(float, _damage, Damage);
	CC_SYNTHESIZE(float, _walkSpeed, WalkSpeed);
	//measurements  保存对精灵的实际图像有用的测量值。需要这些值，是因为你将要使用的这些精灵画布大小是远远大于内部包含的图像。
	CC_SYNTHESIZE(float, _centerToSides, CenterToSides);
	CC_SYNTHESIZE(float, _centerToBottom, CenterToBottom);
	float scale;
	virtual void setScale(float scale);

	//SpriteBox *_spriteBox;
	BoundingBox createBoundingBoxWithOrigin(cocos2d::CCPoint origin, cocos2d::CCSize size);
	void setPosition(CCPoint position);
	void SpriteUpdate(float dt); 

	virtual void animationEvent(CCArmature *armature, MovementEventType movementType, const char *movementID);  //完成 开始
	virtual void onFrameEvent(CCBone *bone, const char *evt, int originFrameIndex, int currentFrameIndex);  //自定义
	virtual SpriteHurt* GetHurt();
	virtual void clean();
};
#endif