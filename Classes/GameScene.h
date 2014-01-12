#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::CCLayer
{
    private :
        void makeBackground();
    
    public :
        virtual bool init();
        static cocos2d::CCScene* scene();
        void scene2();
        CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__