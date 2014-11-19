#include "cocos2d.h"
#include "SweepMain.h"
#include "GameOverScene.h"
#include "HelloWorldScene.h"
#include "time.h"
#include "string.h"
#include "ctime"
#include "sstream"

USING_NS_CC;

Sweep sweep[9][9];
int clickNumber;
clock_t touchTime;
CCLabelTTF* timeText,*sweepText;
int timeNumber,leftSweepNumber;

bool SweepMain::init()
{
	  if ( !Layer::init() )
     {
			return false;
     }
	  //sweepSurplusTTF = CCLabelTTF::create();//剩余雷数显示

	  clickNumber = 0;
	  creatSweepMap(); //数字信息生成
	  creatSweepSprite(); //图像信息生成
	  this->setTouchEnabled(true);
	  sweepTouchCreate();//生成按钮
	  
	  timeText = CCLabelTTF::create("0","Felt",30);
	  timeText->setPosition(ccp(238-57,283-48));
	  this->addChild(timeText);
	  sweepText = CCLabelTTF::create("10","Felt",30);
	  sweepText->setPosition(ccp(57,283-48));
	  this->addChild(sweepText);
	  timeNumber = 0;leftSweepNumber = 10; 
	  schedule(schedule_selector(SweepMain::updateTimeNumber), 1); //读秒

}


void SweepMain::creatSweepMap()
{
	int numSweep = 0;
	for (int i=0;i<9;i++)
		for (int j=0;j<9;j++)
		{
			sweep[i][j].sweepNumber = 0;
			sweep[i][j].Xpoint = i;
			sweep[i][j].Ypoint = j;
			sweep[i][j].isClick = false;
			sweep[i][j].sweepClick = false;
			sweep[i][j].markClick = false;
		}

	std::srand(time(NULL));
	while (numSweep != 10)
	{
		int xPoint = rand()%9;
		int yPoint = rand()%9;
		if (sweep[xPoint][yPoint].sweepNumber == 0)
		{
			sweep[xPoint][yPoint].sweepNumber = 10;
			numSweep++;
		}
	}

	for (int i=0;i<9;i++)
		for (int j=0;j<9;j++)
			getSweepNumber(i,j);

	for (int i=0;i<9;i++)
	{
		for (int j=0;j<9;j++)
			CCLOG("%d",sweep[i][j].sweepNumber);
		CCLOG("\n");
	}

}

void SweepMain::creatSweepSprite()
{
	std::string clickNumber;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	CCSprite* backGroundPic = CCSprite::create("backgroundmain.png");
	backGroundPic->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(backGroundPic);

	for (int i=0;i<9;i++)
		for (int j=0;j<9;j++)
		{
			sweep[i][j].sweepButton = CCSprite::create("sweep.png");
			sweep[i][j].sweepButton->setPosition(ccp(39+i*20,184-(j*20)));
			this->addChild(sweep[i][j].sweepButton);
		}
}

void SweepMain::getSweepNumber(int x,int y)
{
	if (sweep[x][y].sweepNumber != 10)
	{
		if ((sweep[x-1][y-1].sweepNumber == 10)&&(x-1>=0)&&(y-1>=0)) sweep[x][y].sweepNumber++;
		if ((sweep[x-1][y+1].sweepNumber == 10)&&(x-1>=0)&&(y+1<=8)) sweep[x][y].sweepNumber++;
		if ((sweep[x+1][y-1].sweepNumber == 10)&&(x+1<=8)&&(y-1>=0)) sweep[x][y].sweepNumber++;
		if ((sweep[x+1][y+1].sweepNumber == 10)&&(x+1<=8)&&(y+1<=8)) sweep[x][y].sweepNumber++;
		if ((sweep[x][y-1].sweepNumber == 10)&&(y-1>=0)) sweep[x][y].sweepNumber++;
		if ((sweep[x-1][y].sweepNumber == 10)&&(x-1>=0)) sweep[x][y].sweepNumber++;
		if ((sweep[x][y+1].sweepNumber == 10)&&(y+1<=8)) sweep[x][y].sweepNumber++;
		if ((sweep[x+1][y].sweepNumber == 10)&&(x+1<=8)) sweep[x][y].sweepNumber++;
	}
}

void SweepMain::sweepTouchCreate()
{
	Listener = EventListenerTouchOneByOne::create();   
	Listener->setSwallowTouches(true);

	
	Listener->onTouchBegan = [](Touch* touch, Event* event)
	{
		 touchTime = clock();
		 CCPoint touchPoint = touch->getLocationInView();     
		 touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint );  
		 for (int i=0;i<9;i++)
			 for (int j=0;j<9;j++)
			 {
					CCRect rc1 = sweep[i][j].sweepButton->boundingBox(); 

					if((rc1.containsPoint(touchPoint))&&(!sweep[i][j].isClick))
					{
						sweep[i][j].sweepButton->setTexture("sweep0.png");
					}
			 }
         return true;
	};

	Listener->onTouchMoved = [](Touch* touch, Event* event)
	{

		 CCPoint touchPoint = touch->getLocationInView();     
		 touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint );  
		 for (int i=0;i<9;i++)
			 for (int j=0;j<9;j++)
			 {
					CCRect rc1 = sweep[i][j].sweepButton->boundingBox(); 

					if((rc1.containsPoint(touchPoint))&&(!sweep[i][j].isClick))
					{
						sweep[i][j].sweepButton->setTexture("sweep0.png");
					}
			 }


	};
    Listener->onTouchEnded = [=](Touch* touch, Event* event)
	{
		 touchTime = clock() - touchTime;
		 CCPoint touchPoint = touch->getLocationInView();     
		 touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint );  
		 for (int i=0;i<9;i++)
			 for (int j=0;j<9;j++)
			 {
					CCRect rc1 = sweep[i][j].sweepButton->boundingBox(); 

					if((rc1.containsPoint(touchPoint))&&(!sweep[i][j].isClick))
					{
						if (touchTime >= CLOCKS_PER_SEC/4)
							sweep[i][j].markSweepButton();
						else
						{
							sweep[i][j].sweepClick = true;
							sweep[i][j].clickSweepButton();
						}
					}
			 }
         
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Listener, sweep[0][0].sweepButton);
}

void Sweep::clickSweepButton()
{
	if (!this->isClick)
	{
		if (sweep[this->Xpoint][this->Ypoint].sweepNumber == 0)	sweep[this->Xpoint][this->Ypoint].sweepButton->setTexture("sweep0.png");
		if (sweep[this->Xpoint][this->Ypoint].sweepNumber == 1)	sweep[this->Xpoint][this->Ypoint].sweepButton->setTexture("sweep1.png");
		if (sweep[this->Xpoint][this->Ypoint].sweepNumber == 2)	sweep[this->Xpoint][this->Ypoint].sweepButton->setTexture("sweep2.png");
		if (sweep[this->Xpoint][this->Ypoint].sweepNumber == 3)	sweep[this->Xpoint][this->Ypoint].sweepButton->setTexture("sweep3.png");
		if (sweep[this->Xpoint][this->Ypoint].sweepNumber == 4)	sweep[this->Xpoint][this->Ypoint].sweepButton->setTexture("sweep4.png");
		if (sweep[this->Xpoint][this->Ypoint].sweepNumber == 5)	sweep[this->Xpoint][this->Ypoint].sweepButton->setTexture("sweep5.png");
		if (sweep[this->Xpoint][this->Ypoint].sweepNumber == 6)	sweep[this->Xpoint][this->Ypoint].sweepButton->setTexture("sweep6.png");
		if (sweep[this->Xpoint][this->Ypoint].sweepNumber == 7)	sweep[this->Xpoint][this->Ypoint].sweepButton->setTexture("sweep7.png");
		if (sweep[this->Xpoint][this->Ypoint].sweepNumber == 8)	sweep[this->Xpoint][this->Ypoint].sweepButton->setTexture("sweep8.png");

		if (sweep[this->Xpoint][this->Ypoint].sweepButton->getTag() == 1015) updateSweepNumber(true);
		
		if ((this->sweepNumber == 10)&&(this->sweepClick)) {
			sweep[this->Xpoint][this->Ypoint].sweepButton->setTexture("sweep10.png");
			toGameOver(false);
			return;
		}

		if (this->sweepNumber == 0)
		{
			this->isClick = true;
			if ((this->Xpoint != 8)&&(this->Ypoint != 8)) sweep[this->Xpoint + 1][this->Ypoint + 1].clickSweepButton();
			if ((this->Xpoint != 0)&&(this->Ypoint != 8)) sweep[this->Xpoint - 1][this->Ypoint + 1].clickSweepButton();
			if ((this->Xpoint != 8)&&(this->Ypoint != 0)) sweep[this->Xpoint + 1][this->Ypoint - 1].clickSweepButton();
			if ((this->Xpoint != 0)&&(this->Ypoint != 0)) sweep[this->Xpoint - 1][this->Ypoint - 1].clickSweepButton();
			if (this->Xpoint != 8) sweep[this->Xpoint + 1][this->Ypoint].clickSweepButton();
			if (this->Xpoint != 0) sweep[this->Xpoint - 1][this->Ypoint].clickSweepButton();
			if (this->Ypoint != 8) sweep[this->Xpoint][this->Ypoint + 1].clickSweepButton();
			if (this->Ypoint != 0) sweep[this->Xpoint][this->Ypoint - 1].clickSweepButton();   //递归
		}
		this->isClick = true;
		clickNumber++;
		CCLOG("%d",clickNumber);
		if (clickNumber == 71)	toGameOver(true);
	}
}

void Sweep::markSweepButton()
{

	sweep[this->Xpoint][this->Ypoint].sweepButton->setTexture("sweep_mark.png");
	sweep[this->Xpoint][this->Ypoint].sweepButton->setTag(1015);
	this->markClick = true;
	updateSweepNumber(false);

}

void SweepMain::toGameOver(bool winLose)
{
	if (winLose)
	{
		auto reScene = CCTransitionCrossFade::create(1,GameOverScene::gameScene());
		CCDirector::sharedDirector()->replaceScene(reScene);
       
		CCLOG("win");
	}
	else
	{
		auto reScene = CCTransitionFade::create(1,HelloWorld::createScene());
		CCDirector::sharedDirector()->replaceScene(reScene);
	}
}

void SweepMain::updateTimeNumber(float t)
{
	timeNumber++;
	std::stringstream ss;
	std::string timeString;
	ss<<timeNumber;ss>>timeString;
	timeText->setString(timeString);

}

void SweepMain::updateSweepNumber(bool addOrDec)
{
	if (addOrDec) leftSweepNumber++; else leftSweepNumber--;

	std::stringstream ss;
	std::string sweepString;
	ss<<leftSweepNumber;ss>>sweepString;
	sweepText->setString(sweepString);

}

CCScene* SweepMain::gameScene()
{
	CCLOG("333");

	CCScene* playScene = CCScene::create();
	SweepMain* layer = SweepMain::create();

	playScene->addChild(layer);
	return playScene;
}
