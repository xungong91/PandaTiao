#include "AppDelegate.h"
#include "Scene\GMenuScene.h"
#include "include/MyKeypadDelegate.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "vld.h"
#endif

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);

	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(480, 320,kResolutionExactFit);  
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

	//KeypadDlegate
	MyKeypadDelegate *m_pKeypadDlegate = new MyKeypadDelegate();
	m_pKeypadDlegate->autorelease();
	pDirector->getKeypadDispatcher()->addDelegate(m_pKeypadDlegate);

    // create a scene. it's an autorelease object
	CCScene *pScene=GMenuScene::Scence();
	//CCScene *pScene=HelloWorld::scene();
	//CocosGUIExamplesMapScene *pScene = new CocosGUIExamplesMapScene();
	//pScene->autorelease();
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
