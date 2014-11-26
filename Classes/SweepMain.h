#include "cocos2d.h"

class SweepMain : public cocos2d::Layer
{
public:

	cocos2d::CCLabelTTF* sweepSurplusTTF;
	int sweepSurplus;
	int sweepNumber[9][9];
	cocos2d::EventListenerTouchOneByOne* Listener;
    static cocos2d::CCScene* gameScene();
	void creatSweepMap();
	void sweepTouchCreate();
	void creatSweepSprite();
	void sweepUpdate(float t);
	void getSpriteNumble(cocos2d::CCPoint touchPoint);
	void getSweepNumber(int x,int y);
	void toGameOver(bool winLose);
	void updateTimeNumber(float t);
	void updateSweepNumber(bool addOrDec);
    virtual bool init();
	Sweep sweep[9][9];
    
    CREATE_FUNC(SweepMain);
};

class Sweep : public SweepMain
{
public:
	Sweep()
	{
		sweepNumber = 0;
		Xpoint = 0;
		Ypoint = 0;
		isClick = false;
		sweepClick = false;
		markClick = false;
	};
	int sweepNumber,Xpoint,Ypoint;
	cocos2d::CCSprite* sweepButton;
	void clickSweepButton();
	void markSweepButton();
	bool isClick;//防止重复点击
	bool sweepClick;//防止递归时触发雷区
	bool markClick;//防止触发标记
};


