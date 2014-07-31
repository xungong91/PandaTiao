#ifndef _G_TAUREN_BOSS_H_
#define _G_TAUREN_BOSS_H_

#include "Sprite/EnemySprite.h"

class GTaurenBoss:public EnemySprite
{
public:
	CREATE_FUNC(GTaurenBoss);
	bool init();
	virtual int UpdataEnemy(CCPoint centerpoint);   
	virtual void hurtWithDamage(float damage,CCString* attackaction);  // ‹µΩµƒ…À∫¶ 
private:
};
#endif