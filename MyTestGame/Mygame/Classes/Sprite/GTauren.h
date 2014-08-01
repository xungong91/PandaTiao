#ifndef _G_TAUREN_H_
#define _G_TAUREN_H_

#include "Sprite/EnemySprite.h"

class GTauren:public EnemySprite
{
public:
	CREATE_FUNC(GTauren);
	bool init();
private:
};
#endif