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
    auto bg = Sprite::create("bgMainUHD.png");
    bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    
    //scale bg to match screen
    float rX = visibleSize.width / bg->getContentSize().width;
    float rY = visibleSize.height / bg->getContentSize().height;
    
    bg->setScaleX(rX);
    bg->setScaleY(rY);
    
    //button
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
    
    
    //Size* inputSize = new Size(400, 150);
    //CCEditBox* offlineIn = CCEditBox::create(inputSize, CCScale9Sprite::create("bgMainUHD.png"));
    
    //offlineIn->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    
    
    
    
    
    this->addChild(bg, -1);
    this->addChild(soloMenu, 1);
    //this->addChild(offlineIn, 2);
}

void LeaderboardScreen::menuSelectCallback(cocos2d::Ref* sender)
{
       //only one button, no checks needed
    auto newScene = SplashScreen::createScene();
    Director::getInstance()->replaceScene(newScene);
}