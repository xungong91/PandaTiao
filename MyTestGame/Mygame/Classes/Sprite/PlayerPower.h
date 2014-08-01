#ifndef _PLAYER_POWER_H_
#define _PLAYER_POWER_H_

class WeaponModel
{
public:
	WeaponModel(){};
	~WeaponModel(){};
	float Speed;
	float RadiusX;
	float RadiusY;
	float Damage;
	int Index;
};

class PlayerPower
{
public:
	PlayerPower();
	~PlayerPower();
	void SetLv(int lv);
	int pLV;
	int pExp;
	int pExperience;
	int pSkillPoints;
	float pAttackSpeed;
	float pHitPoints;
	float pManaPoints;
	float pDamage;
	float pWalkSpeed;
	int pWeaponType;
	WeaponModel* p_weaponModel;
	WeaponModel GetWeapon();

	float pSkill_1_damageX1;
	float pSkill_1_damageX2;
	float pSkill_2_danageX;
	float pSkill_2_Walk;
	float pSkill_2_CD;
	float pSkill_2_time;
	float pSkill_3_damageX;
	float pSkill_3_ConvertedHp;
	float pSkill_3_CD;
	float pSkill_4_h;
	float pSkill_4_w;
	float pSkill_4_damage;
	float pSkill_4_CD;
	float pSkill_5;
protected:
	void SetPower();
	void SetWeapon();
};

#endif