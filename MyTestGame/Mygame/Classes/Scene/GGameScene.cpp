#include "GGameScene.h"
#include "Layer\GChapterOneLayer.h"
#include "Layer\GChapterTwoLayer.h"
#include "Layer\GChapterThreeLayer.h"

bool GGameScene::init()
{
	if (!CCScene::init())
	{
		return false;
	}
	glClearColor(0,0,0,255);

	gamelayer=FactoryGameLaye(GGameScene::GameLayerType);
	hudlayer=GHudLayer::create();
	hudlayer->bindArmature(gamelayer->getPlayer());

	this->addChild(gamelayer,0);
	this->addChild(hudlayer,1);
	this->setTag(GAME_SCENE_TAG);
	return true;
}
GGameScene* GGameScene::_GGameScene=NULL;

GGameScene* GGameScene::Singleton()
{
	if (_GGameScene==NULL)
	{
		_GGameScene=GGameScene::create();
	}
	return _GGameScene;
}

GGameScene::GGameScene()
{

}

GGameScene::~GGameScene()
{
	GGameScene::_GGameScene=NULL;
}
_GameLayerType GGameScene::GameLayerType=OneChapter;
GGameLayerBase * GGameScene::FactoryGameLaye( _GameLayerType ChapterNum )
{
	GGameLayerBase* GameLayer=NULL;	
	switch (ChapterNum)
	{
	case OneChapter:
		GameLayer=GChapterOneLayer::create();
		break;
	case TwoChapter:
		GameLayer=GChapterTwoLayer::create();
		break;
	case ThreeChapter:
		GameLayer=GChapterThreeLayer::create();
		break;
	default:
		break;
	}
	return GameLayer;
}

