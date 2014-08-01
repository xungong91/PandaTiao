#ifndef _ENEMY_SPRITE_H_
#define _ENEMY_SPRITE_H_

#include "Sprite/ActionSprite.h"

class EnemySprite:public ActionSprite
{
public:
	EnemySprite();
	~EnemySprite();
	CC_SYNTHESIZE(int,_experience,Experience);
	CC_SYNTHESIZE(float, _nextDecisionTime, NextDecisionTime);          //����ʱ��
	virtual int UpdataEnemy(CCPoint centerpoint);   
	virtual void onFrameEvent(CCBone *bone, const char *evt, int originFrameIndex, int currentFrameIndex);  //�Զ���
	virtual void hurtWithDamage(float damage,CCString* attackaction);  //�ܵ����˺� 
	virtual void knockout();    //����
	virtual void animationEvent(CCArmature *armature, MovementEventType movementType, const char *movementID);  //��� ��ʼ
	void coma();
	void comaCB(float dt);
	void KnockedDown();
	void SetBeakBack();
	void setDesiredPosition(cocos2d::CCPoint var,float Vector );

	bool GetGold(int &gold);		//������
protected:
	int m_gold;
	float m_goldPercentage;
};

#endif