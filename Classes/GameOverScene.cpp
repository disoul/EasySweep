#include "cocos2d.h"
#include "GameOverScene.h"
#include "HelloWorldScene.h"
#include "sstream"
#include "fstream"
#include "string.h"

USING_NS_CC;

bool GameOverScene::init()
{
	  if ( !Layer::init() )
     {
			return false;
	  }

	  Size visibleSize = Director::getInstance()->getVisibleSize();

	  CCMenuItemImage* endGameButtum = CCMenuItemImage::create("exit2.png","exit2.png","exit2.png",this,menu_selector(GameOverScene::endGame));
	  endGameButtum->setPosition(ccp(visibleSize.width/2+50,visibleSize.height/2-60));

	  CCMenuItemImage* restartGameButtum = CCMenuItemImage::create("restart.png","restart.png","restart.png",this,menu_selector(GameOverScene::restartGame));
	  restartGameButtum->setPosition(ccp(visibleSize.width/2-50,visibleSize.height/2-60));

	  CCMenu *Menu = CCMenu::create(endGameButtum,restartGameButtum,NULL);
	  Menu->setPosition(ccp(0,0));
	  this->addChild(Menu);

	  CCSprite* winSprite = CCSprite::create("win.png");
	  winSprite->setPosition(ccp(visibleSize.width/2,visibleSize.height/2+70));
	  this->addChild(winSprite);

	  printSweepGrade();
	  return true;
}

void GameOverScene::endGame(Ref* _ref)
{
	Director::getInstance()->end();
}

void GameOverScene::restartGame(Ref* _ref)
{
	auto reScene = CCTransitionFade::create(1,HelloWorld::createScene());
	CCDirector::sharedDirector()->replaceScene(reScene);
}

void GameOverScene::printSweepGrade()
{

	  Size visibleSize = Director::getInstance()->getVisibleSize();
#if 0
	  std::ifstream getTime;
	  getTime.open("sweepdata.sweep");
	  getTime>>gameTime;
	  getTime.close();


	  std::stringstream ss;
	  std::string timeString;
	  ss<<gameTime;ss>>timeString;
	  timeString = "Time:" + timeString + "s";
#endif
	  CCLabelTTF* winTimeTTF = CCLabelTTF::create("test","fonts/Marker Felt.ttf",15);
	  winTimeTTF->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	  this->addChild(winTimeTTF);

}

CCScene* GameOverScene::gameScene()
{

	CCScene* playScene = CCScene::create();
	GameOverScene* layer = GameOverScene::create();

	playScene->addChild(layer);
	return playScene;
}

