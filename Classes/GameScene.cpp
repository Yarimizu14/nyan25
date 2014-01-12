#include "GameScene.h"

using namespace cocos2d;
using namespace std;

CCScene* GameScene::scene()
{
    CCScene* scene = CCScene::create();
    GameScene* layer = GameScene::create();
    scene->addChild(layer);
    
    return scene;
}

bool GameScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    //set Background
    makeBackground();
    
    srand((unsigned)time(NULL));
    nextNumber = 1;
    
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    
    makeCards();
    
    return true;
}

void GameScene::makeBackground()
{
    //get scene width
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    //make background
    CCSprite* pBG = CCSprite::create("background.png");
    pBG->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.5));
    this->addChild(pBG);
}

void GameScene::makeCards()
{
   //initialize array
    CCArray* numbers = CCArray::create();
    for(int i=1; i <= 25; i++)
        numbers->addObject(CCInteger::create(i));
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    for(int x =0; x<5; x++)
    {
        for(int y=0; y< 5; y++)
        {
            int index = rand() % numbers->count();
            int number = ((CCInteger*)numbers->objectAtIndex(index))->getValue();
            
            CCSprite* pCard = CCSprite::create("card_frontside.png");
            CCSize cardSize = pCard->getContentSize();
            pCard->setPosition(ccp(winSize.width*0.5+(x-2)*cardSize.width, winSize.height*0.5+(y-2)*cardSize.height));
            pCard->setTag(number);
            this->addChild(pCard);
            
            CCString* fileName = CCString::createWithFormat("%d.png", number)
            ;
            CCSprite* pNumber =CCSprite::create(fileName->getCString());
            pNumber->setPosition(ccp(cardSize.width * 0.5, cardSize.height * 0.5));
            
            pCard->addChild(pNumber);
            numbers->removeObjectAtIndex(index);
        }
    }
}

bool GameScene::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    return true;
}

void GameScene::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCPoint touchPoint = pDirector->convertToGL(pTouch->getLocationInView());
  
    CCNode* pCard = this->getChildByTag(nextNumber);
    if (!pCard)
    {
        return;
    }
    
    CCRect cardRect = pCard->boundingBox();
    if (cardRect.containsPoint(touchPoint)) {
        CCSprite* pNewCard = CCSprite::create("card_backside.png");
        pNewCard->setPosition(pCard->getPosition());
        this->addChild(pNewCard);
        
        pCard->removeFromParentAndCleanup(true);
        
        if (nextNumber >= 25)
        {
            return;
        }
        nextNumber++;
    }
    
    CCLog("x: %f, y:%f", touchPoint.x, touchPoint.y);
}