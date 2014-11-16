#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::CCScene* gameScene();

	CREATE_FUNC(GameOverScene);

};