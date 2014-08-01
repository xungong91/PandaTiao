#ifndef _G_HERO_H_
#define _G_HERO_H_

#include "Sprite/PlayerSprite.h"
#include <string>
using namespace std;

class GHero:public PlayerSprite
{
public:
	GHero();
	~GHero();
	CREATE_FUNC(GHero);
	bool init();
	virtual SpriteHurt* GetHurt();
};

#endif