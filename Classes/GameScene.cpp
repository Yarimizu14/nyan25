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
    gametime = 0;
    
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    
    makeCards();
    showGametimeLabel();
    
    this->schedule(schedule_selector(GameScene::measureGametime));
    makeRetryButton();
    showHighScoreLabel();
    
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


void GameScene::measureGametime(float fDelta)
{
    gametime += fDelta;
    //CCLog("gametime: %f", gametime);
    showGametimeLabel();
}

void GameScene::showGametimeLabel()
{
    const int tagGametimeLabel = 100;
    
    CCString* timeString = CCString::createWithFormat("%8.1fs", gametime);
    
    CCLabelTTF* timerLabel = (CCLabelTTF*)this->getChildByTag(tagGametimeLabel);
    if (timerLabel) {
        timerLabel->setString(timeString->getCString());
    }
    else
    {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        timerLabel = CCLabelTTF::create(timeString->getCString(), "Arial", 24.0);
        timerLabel->setPosition(ccp(winSize.width*0.9, winSize.height*0.9));
        timerLabel->setTag(tagGametimeLabel);
        this->addChild(timerLabel);
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
            this->unschedule(schedule_selector(GameScene::measureGametime));
            showHighScoreLabel();
            return;
        }
        nextNumber++;
    }
    
    //CCLog("x: %f, y:%f", touchPoint.x, touchPoint.y);
}

void GameScene::makeRetryButton() {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF* retryLabel = CCLabelTTF::create("Retry", "Arial", 24.0);
    CCMenuItemLabel* retryItem = CCMenuItemLabel::create(retryLabel, this, menu_selector(GameScene::tapRetryButton));
    retryLabel->setPosition(ccp(winSize.width*0.9, winSize.height*0.2));
    
    CCMenu* menu = CCMenu::create(retryItem, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
}


void GameScene::tapRetryButton(CCNode *node) {
    CCLog("test");
    CCScene* gameScene = (CCScene*)GameScene::create();
    CCDirector::sharedDirector()->replaceScene(gameScene);
}

void GameScene::showHighScoreLabel() {
    CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
    
    const char* highScorekey = "hightscore";
    
    float highScore = userDefault->getFloatForKey(highScorekey, 99.9);
    if (gametime != 0)
    {
        if (gametime > highScore)
        {
            return;
        }
        else
        {
            highScore = gametime;
            
            userDefault->setFloatForKey(highScorekey, highScore);
            userDefault->flush();
        }
    }
    
    const int tagHighScoreLabel = 200;
    
    CCString* highScoreString = CCString::createWithFormat("%8.1fs", highScore);
    
    CCLabelTTF* highScoreLabel = (CCLabelTTF*)this->getChildByTag(tagHighScoreLabel);
    
    if (highScoreLabel)
    {
        highScoreLabel->setString(highScoreString->getCString());
    }
    else
    {
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        highScoreLabel = CCLabelTTF::create(highScoreString->getCString(), "Arial", 24.0);
        highScoreLabel->setPosition(ccp(winSize.width*0.9, winSize.height*0.7));
        highScoreLabel->setTag(tagHighScoreLabel);
        this->addChild(highScoreLabel);
    }
    
}