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
    cocostudio::ArmatureDataManager::destroyInstance();
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto pDirector = Director::getInstance();
    auto glview = pDirector->getOpenGLView();

    if(!glview) {
        glview = GLViewImpl::create("Alchemy");
        pDirector->setOpenGLView(glview);
    }

    // 해상도 지원
	Size screenSize = glview->getFrameSize();
    Size designSize = Size(1080, 1920);
    
    auto fileUtils = FileUtils::getInstance();
    std::vector<std::string> searchPaths;
    
    /*
    if (screenSize.height > 320)
    {
        auto resourceSize = Size(960, 640);
        searchPaths.push_back("hd");
        searchPaths.push_back("ccs-res/hd");
        searchPaths.push_back("ccs-res");
        searchPaths.push_back("Manifests");
        pDirector->setContentScaleFactor(resourceSize.height/designSize.height);
        
        searchPaths.push_back("hd/ActionTimeline");
    }
    else
    {
        searchPaths.push_back("ccs-res");
        
        searchPaths.push_back("ActionTimeline");
    }
    */
    
    fileUtils->setSearchPaths(searchPaths);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
    // a bug in DirectX 11 level9-x on the device prevents ResolutionPolicy::NO_BORDER from working correctly
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::SHOW_ALL);
#else
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::NO_BORDER);
#endif
    
    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    Scene *pScene = PEIntroLayer::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
	char buf[5];

	sprintf(buf, "%d", POPUP_STOP);
	__String* popParam=__String::create(buf);
	__NotificationCenter::getInstance()->postNotification("scene_popup", popParam); 
	PEBackgroundMusic::sharedPEBackgroundMusic()->PE_pause();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
	PEBackgroundMusic::sharedPEBackgroundMusic()->PE_resume();
    
}
