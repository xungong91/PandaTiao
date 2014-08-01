#ifndef _G_GOLD_SPRITE_H_
#define _G_GOLD_SPRITE_H_
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class GGoldSprite:public CCArmature 
{
public:
	CREATE_FUNC(GGoldSprite);
	virtual bool init();
	void SetShow(int gold);
	void SetShow(int gold,CCPoint point);
	void removeforparent();
	int PickUp();
	GGoldSprite();
	~GGoldSprite();
private:
	int gold;
};

#endif