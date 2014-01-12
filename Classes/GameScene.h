#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::CCLayer
{
    private :
        int nextNumber;
        void makeBackground();
        void makeCards();
    
    public :
        virtual bool init();
        static cocos2d::CCScene* scene();
        virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvents);
        virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvents);
        CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__