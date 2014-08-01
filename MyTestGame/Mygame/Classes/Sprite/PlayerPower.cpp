#include "Sprite/PlayerPower.h"
#include "include/GFileHelper.h"
PlayerPower::PlayerPower()
{
	pExp=CCUserDefault::sharedUserDefault()->getIntegerForKey("My_Exp");
	pLV=CCUserDefault::sharedUserDefault()->getIntegerForKey("My_Lv");
	pWeaponType=CCUserDefault::sharedUserDefault()->getIntegerForKey("My_Weapon");
	p_weaponModel=new WeaponModel[2];
	SetLv(pLV);
	SetPower();
	SetWeapon();
}
WeaponModel PlayerPower::GetWeapon()
{
	return p_weaponModel[pWeaponType-1];
}
PlayerPower::~PlayerPower()
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("My_Exp",pExp);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("My_Lv",pLV);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("My_Weapon",pWeaponType);
	CC_SAFE_DELETE_ARRAY(p_weaponModel);
}
void PlayerPower::SetLv(int lv)
{
	pLV=lv;
	int cont=7;
	string s;
	stringstream ss;
	float* arrayfloat=new float[cont];
	ss<<"select Experience,Damage,AttackSpeed,HitPoints,ManaPoints,WalkSpeed,SkillPoints from T_Power where Lv="<<lv;
	s=ss.str();
	char** data1=GFileHelper::Singleton()->GetStringArray(s.c_str(),cont);
	ss.str("");
	for (int i=0;i<cont;i++)
	{
		ss<<data1[i];
		ss>>arrayfloat[i];
		ss.clear();
	}
	for (int i=0;i<cont;i++)
	{
		CC_SAFE_DELETE_ARRAY(data1[i]);
	}
	CC_SAFE_DELETE_ARRAY(data1);
	pExperience=(int)arrayfloat[0];
	pDamage=arrayfloat[1];
	pAttackSpeed=arrayfloat[2];
	pHitPoints=arrayfloat[3];
	pManaPoints=arrayfloat[4];
	pWalkSpeed=arrayfloat[5];
	pSkillPoints=arrayfloat[6];
	CC_SAFE_DELETE_ARRAY(arrayfloat);
}
void PlayerPower::SetWeapon()
{
	for (int i=1;i<=2;i++)
	{
		int lv=GFileHelper::Singleton()->GetWeaponLv(i);
		const char* select=CCString::createWithFormat("select Speed,RadiusX,RadiusY,Damage,WIndex from T_Weapon where Type=%d and Lv=%d",i,lv)->getCString();
		int cont=5;
		char** data=GFileHelper::Singleton()->GetStringArray(select,cont);
		int index=i-1;
		p_weaponModel[index].Speed=CCString::createWithFormat(data[0])->floatValue();
		p_weaponModel[index].RadiusX=CCString::createWithFormat(data[1])->floatValue();
		p_weaponModel[index].RadiusY=CCString::createWithFormat(data[2])->floatValue();
		p_weaponModel[index].Damage=CCString::createWithFormat(data[3])->floatValue();
		p_weaponModel[index].Index=CCString::createWithFormat(data[4])->intValue();
		for (int i=0;i<cont;i++)
		{
			CC_SAFE_DELETE_ARRAY(data[i]);
		}
		CC_SAFE_DELETE_ARRAY(data);
	}
}
void PlayerPower::SetPower()
{
	pSkill_4_h=100;
	pSkill_4_w=200;
	GFileHelper *hepler= GFileHelper::Singleton();
	string s;
	stringstream ss;
	float float1;
	float float2;
	float float3;
	float float4;
	float float5;
	int cont;
	SkillModel *model1=hepler->GetSkillModel(0);
	if (model1->SkillLv>0)
	{
		ss<<"select pSkill_1_damageX1,pSkill_1_damageX2 from T_Skill where LV="<<model1->SkillLv;
		s=ss.str();
		cont=2;
		char** data1=hepler->GetStringArray(s.c_str(),cont);
		ss.str("");
		ss<<data1[1];
		ss>>float2;
		ss.clear();
		ss<<data1[0];
		ss>>float1;
		ss.str("");
		ss.clear();
		pSkill_1_damageX1=float1;
		pSkill_1_damageX2=float2;
		for (int i=0;i<cont;i++)
		{
			CC_SAFE_DELETE_ARRAY(data1[i]);
		}
		CC_SAFE_DELETE_ARRAY(data1);
	}
	SkillModel *model2=hepler->GetSkillModel(1);
	if (model2->SkillLv>0)
	{
		ss<<"select pSkill_2_danageX,pSkill_2_Walk,pSkill_2_time,pSkill_2_CD from T_Skill where LV="<<model2->SkillLv;
		s=ss.str();
		cont=4;
		char** data2=hepler->GetStringArray(s.c_str(),cont);
		ss.str("");
		ss<<data2[0];
		ss>>float1;
		ss.clear();
		ss<<data2[1];
		ss>>float2;
		ss.clear();
		ss<<data2[2];
		ss>>float3;
		ss.clear();
		ss<<data2[3];
		ss>>float4;
		ss.str("");
		ss.clear();
		pSkill_2_danageX=float1;
		pSkill_2_Walk=float2;
		pSkill_2_time=float3;
		pSkill_2_CD=float4;
		for (int i=0;i<cont;i++)
		{
			CC_SAFE_DELETE_ARRAY(data2[i]);
		}
		CC_SAFE_DELETE_ARRAY(data2);
	}
	SkillModel *model3=hepler->GetSkillModel(2);
	if (model3->SkillLv>0)
	{
		ss<<"select pSkill_3_damageX,pSkill_3_ConvertedHp,pSkill_3_CD from T_Skill where LV="<<model3->SkillLv;
		s=ss.str();
		cont=3;
		char** data3=hepler->GetStringArray(s.c_str(),cont);
		ss.str("");
		ss<<data3[0];
		ss>>float1;
		ss.clear();
		ss<<data3[1];
		ss>>float2;
		ss.clear();
		ss<<data3[2];
		ss>>float3;
		ss.str("");
		ss.clear();
		pSkill_3_damageX=float1;
		pSkill_3_ConvertedHp=float2;
		pSkill_3_CD=float3;
		for (int i=0;i<cont;i++)
		{
			CC_SAFE_DELETE_ARRAY(data3[i]);
		}
		CC_SAFE_DELETE_ARRAY(data3);
	}
	SkillModel *model4=hepler->GetSkillModel(3);
	if (model4->SkillLv>0)
	{
		ss<<"select pSkill_4_h,pSkill_4_w,pSkill_4_damage,pSkill_4_CD from T_Skill where LV="<<model4->SkillLv;
		s=ss.str();
		cont=4;
		char** data4=hepler->GetStringArray(s.c_str(),cont);
		ss.str("");
		ss<<data4[0];
		ss>>float1;
		ss.clear();
		ss<<data4[1];
		ss>>float2;
		ss.clear();
		ss<<data4[2];
		ss>>float3;
		ss.clear();
		ss<<data4[3];
		ss>>float4;
		ss.str("");
		ss.clear();
		pSkill_4_h=float1;
		pSkill_4_w=float2;
		pSkill_4_damage=float3;
		pSkill_4_CD=float4;
		for (int i=0;i<cont;i++)
		{
			CC_SAFE_DELETE_ARRAY(data4[i]);
		}
		CC_SAFE_DELETE_ARRAY(data4);
	}
}

