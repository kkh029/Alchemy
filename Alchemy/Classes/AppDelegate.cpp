#include "AppDelegate.h"
#include "Intro/PEIntroLayer.h"
#include "Sound/PEBackgroundMusic.h"
#include "PopUp/PEPopUpManager.h"
#include "Common.h"

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

    // �ػ� ����
	Size winSize = CCDirector::sharedDirector()->getWinSize();
	CCEGLView::sharedOpenGLView()->setFrameSize(winSize.width, winSize.height);
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(DESIGN_WIDTH, DESIGN_HEIGHT, kResolutionShowAll);
	
    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = PEIntroLayer::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();
	char buf[5];

	sprintf(buf, "%d", POPUP_STOP);
	CCString* popParam=CCString::create(buf);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("scene_popup", popParam); 
	PEBackgroundMusic::sharedPEBackgroundMusic()->PE_pause();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
	PEBackgroundMusic::sharedPEBackgroundMusic()->PE_resume();
    
}
