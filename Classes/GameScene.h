#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::CCLayer
{
    private :
        int nextNumber;
        float gametime;
    
        void makeBackground();
        void makeCards();
        void measureGametime(float fDelta);
        void showGametimeLabel();
        void makeRetryButton();
        void tapRetryButton(CCNode *node);
        void showHighScoreLabel();
    
    public :
        virtual bool init();
        static cocos2d::CCScene* scene();
        virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvents);
        virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvents);
        CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__