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
    
    CREATE_FUNC(SweepMain);
};

class Sweep : public SweepMain
{
public:
	int sweepNumber,Xpoint,Ypoint;
	cocos2d::CCSprite* sweepButton;
	void clickSweepButton();
	void markSweepButton();
	bool isClick;//��ֹ�ظ����
	bool sweepClick;//��ֹ�ݹ�ʱ��������
	bool markClick;//��ֹ�������
};