#ifndef _G_ENEMY_Z_H_
#define _G_ENEMY_Z_H_

#include "Sprite/EnemySprite.h"
#include <string>
using namespace std;

class EnemyZ:public EnemySprite
{
public:
	CREATE_FUNC(EnemyZ);
	bool init();
};

#endif