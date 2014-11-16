#include "cocos2d.h"
#include "GameOverScene.h"

USING_NS_CC;

bool GameOverScene::init()
{
	  if ( !Layer::init() )
     {
			return false;
	  }

	  Size visibleSize = Director::getInstance()->getVisibleSize();
	  CCSprite* winSprite = CCSprite::create("win.png");
	  winSprite->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	  this->addChild(winSprite);

}

CCScene* GameOverScene::gameScene()
{
	CCLOG("333");

	CCScene* playScene = CCScene::create();
	GameOverScene* layer = GameOverScene::create();

	playScene->addChild(layer);
	return playScene;
}

