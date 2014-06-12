/*
 * GameScreenScene.cpp
 * Michael Mancuso
 * June 12, 2014
 * Main game screen for the game.
*/

#include "GameScreenScene.h"

USING_NS_CC;

Scene* GameScreen::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScreen::create();
    scene->addChild(layer);
    return scene;
}

bool GameScreen::init()
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
    bg = Sprite::create("SplashScreenUHD.png");
    bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    
    //scale bg to match screen
    float rX = visibleSize.width / bg->getContentSize().width;
    float rY = visibleSize.height / bg->getContentSize().height;
    
    bg->setScaleX(rX);
    bg->setScaleY(rY);
    
    //create "main" menu
    this->changeMenu(GameScreen::MenuType::MAIN);
    menu = Menu::createWithArray(menuItems);
    
    
    
    
    //other ui
    
    
    this->addChild(bg, -1);
}

void GameScreen::changeBackgrounds(GameScreen::MenuType type)
{
    switch (type)
    {
        case GameScreen::MenuType::MAIN:
            bg->setTexture(TextureCache::sharedTextureCache()->addImage("bgMainUHD.png"));
            break;
        default:
            break;
    }
}

void GameScreen::changeMenu(GameScreen::MenuType type)
{
    
    
    changeBackgrounds(type);
}

void GameScreen::menuSelectCallback(cocos2d::Ref* sender)
{
    
}