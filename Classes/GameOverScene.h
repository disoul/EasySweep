#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
public:
	virtual bool init();
	static cocos2d::CCScene* gameScene();
	void endGame(Ref* _ref);
	void restartGame(Ref* _ref);

	CREATE_FUNC(GameOverScene);

};