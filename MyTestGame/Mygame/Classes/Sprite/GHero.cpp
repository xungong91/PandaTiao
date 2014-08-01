#include "Sprite/GHero.h"

GHero::GHero()
{
	CombosNames=new string[3];
	CombosNames[0]="combos1";
	CombosNames[1]="combos2";
	CombosNames[2]="combos3";

	_combosMaxNum=2;
}
GHero::~GHero()
{

}
bool GHero::init()
{
	if (!CCArmature::init("Hero"))
	{
		return false;
	}
	CCParticleSystem *p1 = CCParticleSystemQuad::create("armature/SmallSun.plist");
	CCBone* bone=CCBone::create("p1");
	CCPoint point=bone->getPosition();
	bone->setPosition(ccp(60,0));
	bone->addDisplay(p1, 0);
	bone->changeDisplayByIndex(0, true);
	bone->setIgnoreMovementBoneData(true);
	bone->setZOrder(100);
	bone->setScale(1.2f);
	this->addBone(bone,"Layer17");

	SetPower();
	this->_hitPoints=pHitPoints;
	this->_manaPoints=pManaPoints;   //¸Ä±äÑªÁ¿
	this->setScale(0.5);
	SetSpriteBox(ccp(-6,-6),CCSizeMake(60,90),ccp(30,15),CCSizeMake(110,40));
	//_spriteBox=new SpriteBox(ccp(-6,-6),CCSizeMake(60,90),ccp(30,15),CCSizeMake(110,40));
	BoxItem *itme1=new BoxItem(ccp(-6,-6),CCSizeMake(60,90),ccp(40,15),CCSizeMake(100,30),kActionStateCombos,1);
	BoxItem *itme2=new BoxItem(ccp(-6,-6),CCSizeMake(60,90),ccp(30,15),CCSizeMake(70,40),kActionStateCombos,2);
	this->_boxItems->addObject(itme1);
	this->_boxItems->addObject(itme2);

	this->getAnimation()->setFrameEventCallFunc(this, frameEvent_selector(GHero::onFrameEvent));
	this->getAnimation()->setMovementEventCallFunc(this, movementEvent_selector(GHero::animationEvent));
	return true;
}
SpriteHurt* GHero::GetHurt()
{
	SpriteHurt* hurt=new SpriteHurt();
	if (_currentNum==0)
	{
		hurt->damage=this->_damage*pSkill_1_damageX2;
		hurt->hurttype=CCString::create(ATTACK_KNOCKDOWN_ATTACK);
	}
	else
	{
		hurt->damage=this->_damage*pSkill_1_damageX1;
		hurt->hurttype=CCString::create(ATTACK_NORMAL_ATTACK);
	}
	return hurt;
}
