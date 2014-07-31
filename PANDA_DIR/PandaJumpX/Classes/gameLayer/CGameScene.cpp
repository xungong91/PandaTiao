#include "CGameScene.h"
#include "CGameLayer.h"

USING_NS_CC;

CGameScene::CGameScene()
{

}

CGameScene::~CGameScene()
{

}

bool CGameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	glClearColor(255.0f, 255.0f, 255.0f, 1.0f);


	this->addChild(CGameLayer::create());

	return true;
}

