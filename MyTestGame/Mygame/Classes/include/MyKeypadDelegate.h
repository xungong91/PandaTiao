#ifndef _MY_KEYPAD_DELEGATE_H_
#define _MY_KEYPAD_DELEGATE_H_

#include "cocos2d.h"
#include "Defines.h"
#include "Scene/GMenuScene.h"
#include "Scene/GGameScene.h"
USING_NS_CC;

class MyKeypadDelegate:public CCKeypadDelegate,public CCNode
{
public:
	virtual void keyBackClicked();
	virtual void keyMenuClicked();
};

void MyKeypadDelegate::keyBackClicked()
{
	int iManSceneTag = CCDirector::sharedDirector()->getRunningScene()->getTag();
	switch (iManSceneTag)
	{
	case MAIN_SCENE_TAG:
		static_cast<GMenuScene*>(CCDirector::sharedDirector()->getRunningScene()->getChildByTag(MAIN_SCENE_TAG))->CloseGame();
		break;
	case MAP_SCENE_TAG:
		CCDirector::sharedDirector()->replaceScene(GMenuScene::Scence());
		break;
	case GAME_SCENE_TAG:
		(static_cast<GGameScene*>(CCDirector::sharedDirector()->getRunningScene()))->gamelayer->GamePause();
		break;
	default:
		break;
	}
}

void MyKeypadDelegate::keyMenuClicked()
{
	CCKeypadDelegate::keyMenuClicked();
}

#endif