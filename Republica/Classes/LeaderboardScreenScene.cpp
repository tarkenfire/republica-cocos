/*
 * LeaderboardScreenScene.cpp
 * Michael Mancuso
 * June 20, 2014
 * "Game Over" and leaderboard screen.
*/

#include "LeaderboardScreenScene.h"
#include "extensions/cocos-ext.h"
#include "SplashScreenScene.h"

USING_NS_CC;

Scene* LeaderboardScreen::createScene()
{
    auto scene = Scene::create();
    auto layer = LeaderboardScreen::create();
    scene->addChild(layer);
    return scene;
}


bool LeaderboardScreen::init()
{
    //check for super init
    if (!Layer::init())
    {
        return false;
    }
    
    //get coordinate constraints
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //set background image
    auto bg = Sprite::create("bgBlank.png");
    bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    
    //scale bg to match screen
    float rX = visibleSize.width / bg->getContentSize().width;
    float rY = visibleSize.height / bg->getContentSize().height;
    
    bg->setScaleX(rX);
    bg->setScaleY(rY);
    
    //button
    Vector<MenuItem*> item;
    
    auto bAch = MenuItemImage::create(
                                          "btnBack.png",
                                          "btnBackPressed.png",
                                          CC_CALLBACK_1(LeaderboardScreen::menuSelectCallback, this)
                                          );
    
    bAch->setPosition(Vec2( visibleSize.width / 2, bAch->getContentSize().height + 40));
    bAch->setTag(1);
    
    item.pushBack(bAch);
    
    auto soloMenu = Menu::createWithArray(item);
    soloMenu->setPosition(Vec2::ZERO);
    
    //other ui
    int l_score = UserDefault::getInstance()->getIntegerForKey("endScore");
    
    textIn = TextFieldTTF::textFieldWithPlaceHolder("High Scores", "Arial", 72);
    textIn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.3));
    
    placeOne = LabelTTF::create("First Place", "Arial", 64);
    placeOne->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.5));
    placeOne->setColor(ccc3(0,0,0));
    
    placeTwo = LabelTTF::create("Second Place", "Arial", 64);
    placeTwo->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.5 - 70));
    placeTwo->setColor(ccc3(0,0,0));
    
    placeThree = LabelTTF::create("Third Place", "Arial", 64);
    placeThree->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.5 - 140));
    placeThree->setColor(ccc3(0,0,0));
    
    placeFour= LabelTTF::create("Fourth Place", "Arial", 64);
    placeFour->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.5 - 210));
    placeFour->setColor(ccc3(0,0,0));
    
    placeFive = LabelTTF::create("Fifth Place", "Arial", 64);
    placeFive->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.5 - 280));
    placeFive->setColor(ccc3(0,0,0));
    
    this->addChild(bg, -1);
    this->addChild(soloMenu, 1);
    this->addChild(textIn, 1);
    this->addChild(placeOne, 2);
    this->addChild(placeTwo, 2);
    this->addChild(placeThree, 2);
    this->addChild(placeFour, 2);
    this->addChild(placeFive, 2);
    
    
    //check if player has highscore
    checkVal = checkForHighScore(l_score);
}

void LeaderboardScreen::menuSelectCallback(cocos2d::Ref* sender)
{
    //only one button, no checks needed
    auto newScene = SplashScreen::createScene();
    Director::getInstance()->replaceScene(newScene);
}

void LeaderboardScreen::keyboardWillShow(cocos2d::IMEKeyboardNotificationInfo &info){}
void LeaderboardScreen::keyboardWillHide(cocos2d::IMEKeyboardNotificationInfo &info){}
//void LeaderboardScreen::ccTouchesBegan(cocos2d::Set *pTouches, cocos2d::Event *pEvent){}

int LeaderboardScreen::checkForHighScore(int newScore)
{
    //cascade through all five scores, starting at one
    int check = UserDefault::getInstance()->getIntegerForKey("top1", 0);
    
    //1
    if(newScore > check)
    {
        return 1;
    }
    
    int check = UserDefault::getInstance()->getIntegerForKey("top2", 0);
    
    //2
    if (newScore > check)
    {
        return 2;
    }
    
    int check = UserDefault::getInstance()->getIntegerForKey("top3", 0);
    if (newScore > check)
    {
        return 3;
    }
    
    int check = UserDefault::getInstance()->getIntegerForKey("top4", 0)
    if (newScore > check)
    {
        return 4;
    }
    
    int check = UserDefault::getInstance()->getIntegerForKey("top5", 0);
    if (newScore > check)
    {
        return 5;
    }
    
    return -1;
}

void addNewHighScore(int newScore, int pos, std::string name)
{
    switch (pos)
    {
        case -1:
            //no high score
            break;
            
    }
}