/*
 * LeaderboardScreenScene.cpp
 * Michael Mancuso
 * June 20, 2014
 * "Game Over" and leaderboard screen.
*/

#include "LeaderboardScreenScene.h"

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
    
    //other ui
    int l_score = UserDefault::getInstance()->getIntegerForKey("endScore");
    
    
    
    
    
    this->addChild(bg, -1);
}

void LeaderboardScreen::setPlayerStats(int const& score, int const& turns)
{
   
}