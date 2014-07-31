#ifndef _GAME_LOADING_SCENCE_H_
#define _GAME_LOADING_SCENCE_H_

#include "cocos2d.h"
USING_NS_CC;

class GameLoadingScene:public CCLayer
{
public:
	CREATE_FUNC(GameLoadingScene);
	bool init();
	virtual void onEnter();
	void dataLoaded(float percent);
	void dataComplete();
	void Customupdate(float delta);

	CCLabelTTF* label;
	CCLabelTTF* labelnum;
};

#endif