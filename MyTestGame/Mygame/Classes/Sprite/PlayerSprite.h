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
	virtual void onFrameEvent(CCBone *bone, const char *evt, int originFrameIndex, int currentFrameIndex);  //自定义
	virtual CCRect GetAttackBox();
	virtual void onCombos();
	virtual bool onBuff(float &cd,float mana=33.0f); 
	virtual bool onPaiji(float &cd);
	virtual bool onnailuo(float &cd);
	virtual bool onDuyao(float &cd){return false;}
	virtual int OnChangeWeapon(); //设置武器
	//设置等级 什么的
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
	void DeleteEmitter(float dt); //删除lvup
	virtual void StartCombos(); //开始连续技
	bool _IsCombos; //是否进行下个连击动作
	int _combosMaxNum; //最大动作
	int _currentNum;  //当前的动作
	string* CombosNames; //动作名称
	void SetPower();
	float _attackInternal; //攻击速度参数
	void SetAttackSpeed(float _internal);  //设置攻击速度
	float buffSpeed;
};


#endif