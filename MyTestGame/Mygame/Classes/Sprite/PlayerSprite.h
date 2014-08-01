#ifndef _PLAYER_SPPRITE_H_
#define _PLAYER_SPPRITE_H_

#include "Sprite/ActionSprite.h"
#include "Sprite/PlayerPower.h"
#include <string>
using namespace std;

class SkillDelegate
{
public:
	virtual void onCombos(){};
	virtual bool onBuff(float &cd,float mana=33.0f){return false;} 
	virtual bool onPaiji(float &cd){return false;} 
	virtual bool onnailuo(float &cd){return false;} 
	virtual bool onDuyao(float &cd){return false;}
	virtual int OnChangeWeapon(){return 0;}
};

class PlayerDelegate
{
public:
	virtual void OnSetHitPoints(float hp){};
	virtual void OnSetManeaPoints(float mp){};
	virtual void OnSetExp(float Exp){};
	virtual void OnLVUP(float lv,float hp,float mp,float exp){};
};

class PlayerSprite:public ActionSprite,public PlayerPower ,public SkillDelegate
{
public:
	PlayerSprite();
	~PlayerSprite();
	virtual void animationEvent(CCArmature *armature, MovementEventType movementType, const char *movementID);
	virtual void onFrameEvent(CCBone *bone, const char *evt, int originFrameIndex, int currentFrameIndex);  //�Զ���
	virtual CCRect GetAttackBox();
	virtual void onCombos();
	virtual bool onBuff(float &cd,float mana=33.0f); 
	virtual bool onPaiji(float &cd);
	virtual bool onnailuo(float &cd);
	virtual bool onDuyao(float &cd){return false;}
	virtual int OnChangeWeapon(); //��������
	//���õȼ� ʲô��
	virtual void setHitPoints(float var);
	virtual float getManaPoints();
	virtual void setManaPoints(float var);
	void SetExperience(int ex);
	CC_SYNTHESIZE(float,_radiusX,RadiusX);
	CC_SYNTHESIZE(float,_radiusY,RadiusY);
	CCRect nailuorect();
	CCPoint nailuopoint();
	bool _isBuff;
	bool _isPaiji;
	bool _isNailuo;
	void SetPlayerDelegate(PlayerDelegate* _delegate);
protected:
	float _manaPoints;
	PlayerDelegate* m_PlayerDelegate;
	void BuffCancel(float dt);
	void BuffTimeOff(float dt);
	void PaijiTimeOff(float dt);
	void NailuoTimeOff(float dt);
	CCNode *ParticleNode;  //buff
	CCNode *ParticleNode2;	//lvup
	void DeleteEmitter(float dt); //ɾ��lvup
	virtual void StartCombos(); //��ʼ������
	bool _IsCombos; //�Ƿ�����¸���������
	int _combosMaxNum; //�����
	int _currentNum;  //��ǰ�Ķ���
	string* CombosNames; //��������
	void SetPower();
	float _attackInternal; //�����ٶȲ���
	void SetAttackSpeed(float _internal);  //���ù����ٶ�
	float buffSpeed;
};


#endif