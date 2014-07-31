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
	void idle();  //����
	virtual void attack();    //����
	virtual void hurtWithDamage(float damage,CCString* attackaction);  //�ܵ����˺� 
	virtual void knockout();    //����
	void walkWithDirection(cocos2d::CCPoint direction);  //�ߵķ���
	void trick1();   //���⼼��
	//states
	CC_SYNTHESIZE(_ActionState, _actionState, ActionState);
	//movement
	CC_SYNTHESIZE(cocos2d::CCPoint, _velocity, Velocity); //����
	CC_SYNTHESIZE(cocos2d::CCPoint, _desiredPosition, DesiredPosition);  //λ��
	void updatePositions(float w,float h);
	//attributes  �������������ٶ�ֵ������ʱ����������ֵ�������˺�ֵ��
	CC_SYNTHESIZE(float, _hitPoints, HitPoints);
	CC_SYNTHESIZE(float, _damage, Damage);
	CC_SYNTHESIZE(float, _walkSpeed, WalkSpeed);
	//measurements  ����Ծ����ʵ��ͼ�����õĲ���ֵ����Ҫ��Щֵ������Ϊ�㽫Ҫʹ�õ���Щ���黭����С��ԶԶ�����ڲ�������ͼ��
	CC_SYNTHESIZE(float, _centerToSides, CenterToSides);
	CC_SYNTHESIZE(float, _centerToBottom, CenterToBottom);
	float scale;
	virtual void setScale(float scale);

	//SpriteBox *_spriteBox;
	BoundingBox createBoundingBoxWithOrigin(cocos2d::CCPoint origin, cocos2d::CCSize size);
	void setPosition(CCPoint position);
	void SpriteUpdate(float dt); 

	virtual void animationEvent(CCArmature *armature, MovementEventType movementType, const char *movementID);  //��� ��ʼ
	virtual void onFrameEvent(CCBone *bone, const char *evt, int originFrameIndex, int currentFrameIndex);  //�Զ���
	virtual SpriteHurt* GetHurt();
	virtual void clean();
};
#endif