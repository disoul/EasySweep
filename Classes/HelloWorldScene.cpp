 #include "HelloWorldScene.h"
 #include "SweepMain.h"
 #include "GameOverScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
    	CCLOG("ASAS");
        return false;
    }
    
    CCLOG("DSAD");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	CCSprite* BackGoundPicture = CCSprite::create("background.png");
	BackGoundPicture->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(BackGoundPicture);
    
	CCMenuItemImage* StartBottum = CCMenuItemImage::create("start1.png","start2.png","start1.png",this,menu_selector(HelloWorld::toGameStartScene));
	StartBottum->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));

	CCMenuItemImage* ExitBottum = CCMenuItemImage::create("exit.png","exit_2.png","exit.png",this,menu_selector(HelloWorld::toExitGame));
	ExitBottum->setPosition(ccp(visibleSize.width/2,visibleSize.height/2-60));

	CCMenu *menu = CCMenu::create(StartBottum, ExitBottum,NULL);
	menu->setPosition(0,0);
	this->addChild(menu); 

	return true;
}

void HelloWorld::toGameStartScene(Ref* _ref)
{
	CCLOG("111");
	CCScene* sceneChange = SweepMain::gameScene();
	auto reScene = CCTransitionCrossFade::create(1,SweepMain::gameScene());
	CCDirector::sharedDirector()->replaceScene(reScene);
	CCLOG("222");
}

void HelloWorld::toExitGame(Ref* _ref)
{
	Director::getInstance()->end();
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
