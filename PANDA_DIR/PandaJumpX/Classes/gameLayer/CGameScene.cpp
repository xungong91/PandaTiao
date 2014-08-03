#include "CGameScene.h"
#include "gameLayer/CGameLayer.h"
#include "gameLayer/CHudLayer.h"

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
	this->addChild(LayerColor::create(Color4B(255,255,255,255)));

	//¿ØÖÆ²ã
	auto hudLayer = CHudLayer::create();
	this->addChild(hudLayer);

	//ÓÎÏ·²ã
	auto gameLayer = CGameLayer::create();
	this->addChild(gameLayer);

	hudLayer->setHudDelegate(gameLayer);
	return true;
}

