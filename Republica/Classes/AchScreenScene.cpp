/*
 * AchScreenScene.cpp
 * Michael Mancuso
 * June 25, 2014
 * Main game screen for the game.
*/

#include "AchScreenScene.h"
#include "SplashScreenScene.h"

USING_NS_CC;

Scene* AchScreen::createScene()
{
    auto scene = Scene::create();
    auto layer = AchScreen::create();
    scene->addChild(layer);
    return scene;
}

bool AchScreen::init()
{
    //constants
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //bg
    bg = Sprite::create("bgMainUHD.png");
    bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    
    //scale bg to match screen
    float rX = visibleSize.width / bg->getContentSize().width;
    float rY = visibleSize.height / bg->getContentSize().height;
    
    bg->setScaleX(rX);
    bg->setScaleY(rY);
    
    
    //set initial ui
    achP5 = Sprite::create("achPassFive.png");
    achP10 = Sprite::create("achPassTen.png");
    achP15 = Sprite::create("achPassFivteen.png");
    
    //position ach sprites
    achP5->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.3));
    achP10->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.3 - 160));
    achP15->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.3 - 320));
    
    
    
    //button
    Vector<MenuItem*> item;
    
    auto bAch = MenuItemImage::create(
                                          "btnBack.png",
                                          "btnBackPressed.png",
                                          CC_CALLBACK_1(AchScreen::menuSelectCallback, this)
                                          );
    
    bAch->setPosition(Vec2( visibleSize.width / 2, bAch->getContentSize().height + 40));
    bAch->setTag(1);
    
    item.pushBack(bAch);
    
    auto soloMenu = Menu::createWithArray(item);
    soloMenu->setPosition(Vec2::ZERO);
    
    //check achs, change ui if ach is obtained
    if (UserDefault::getInstance()->getBoolForKey("p5"))
    {
        achP5->setTexture(TextureCache::sharedTextureCache()->addImage("achPassFiveActive.png"));
    }
    
    //add children
    this->addChild(bg, -1);
    this->addChild(soloMenu, 1);
    this->addChild(achP5, 1);
    this->addChild(achP10, 1);
    this->addChild(achP15, 1);
}

void AchScreen::menuSelectCallback(cocos2d::Ref* sender)
{
    //only one button, no checks needed
    auto newScene = SplashScreen::createScene();
    Director::getInstance()->replaceScene(newScene);
    
}