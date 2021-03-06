/*
 * SplashScreenScene.cpp
 * Michael Mancuso
 * June 9, 2014
 * Splash Screen and Main Menu for the game.
*/

#include "SplashScreenScene.h"
#include "AchScreenScene.h"

#include <jni.h>
#include <JniHelper.h>

USING_NS_CC;

Scene* SplashScreen::createScene()
{
    auto scene = Scene::create();
    auto layer = SplashScreen::create();
    scene->addChild(layer);
    return scene;
}

bool SplashScreen::init()
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
    auto bg = Sprite::create("SplashScreenUHD.png");
    bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    
    //scale bg to match screen
    float rX = visibleSize.width / bg->getContentSize().width;
    float rY = visibleSize.height / bg->getContentSize().height;
    
    bg->setScaleX(rX);
    bg->setScaleY(rY);
    
    //menus and buttons
    
    Vector<MenuItem*> pMenuItems;
    
    //"New Game" button
    auto pNewGame = MenuItemImage::create(
                                                "btnNewGameUHD.png",
                                                "btnNewGamePressedUHD.png",
                                                CC_CALLBACK_1(SplashScreen::menuSelectCallback, this)
                                               );
    
 
    
    pNewGame->setTag(1);
    
    pMenuItems.pushBack(pNewGame);
    
    //"Continue" button
    auto pContinue = MenuItemImage::create(
                                            "btnContinueUHD.png",
                                            "btnContinuePressedUHD.png",
                                            CC_CALLBACK_1(SplashScreen::menuSelectCallback, this)
                                           );
    
    
    pContinue->setTag(2);
    
    pMenuItems.pushBack(pContinue);
    
    
    //"Options" button
    auto pOptions = MenuItemImage::create(
                                          "btnOptionsUHD.png",
                                          "btnOptionsPressedUHD.png",
                                          CC_CALLBACK_1(SplashScreen::menuSelectCallback, this)
                                          );
                                        
                                        
    
    pOptions->setTag(3);
    
    pMenuItems.pushBack(pOptions);
    
    auto pMenu = Menu::createWithArray(pMenuItems);
    pMenu->alignItemsVerticallyWithPadding(40);
    pMenu->setPosition(Vec2(visibleSize.width/2, visibleSize.height / 2));
    
    
    //secondary menu
    Vector<MenuItem*> bMenuItems;
    
    //"Options" button
    auto bAch = MenuItemImage::create(
                                          "btnAch.png",
                                          "btnAchPressed.png",
                                          CC_CALLBACK_1(SplashScreen::menuSelectCallback, this)
                                          );
    
    bAch->setPosition(Vec2( visibleSize.width / 2, bAch->getContentSize().height + 40));
    bAch->setTag(5);
    
    bMenuItems.pushBack(bAch);
    
    auto bMenu = Menu::createWithArray(bMenuItems);
    
    bMenu->setPosition(Vec2::ZERO);
    
    
    //add elements
    this->addChild(bg, -1);
    this->addChild(pMenu, 1);
    this->addChild(bMenu, 1);
}

void SplashScreen::menuSelectCallback(Ref* sender)
{
    MenuItem* button = (MenuItem*) sender;
    auto newScene = GameScreen::createScene();
    
    switch (button->getTag())
    {
        case 1: //new game button
            Director::getInstance()->replaceScene(newScene);
            break;
        case 2: //continue button
            MessageBox("Feature Not Implemented.", "Continue");
            break;
        case 3: // settings buttons
            MessageBox("Feature Not Implemeted.", "Settings");
            break;
        case 5: // ach
            showAchievements();
            break;
        default: //error
            break;
    }
}

extern "C"
{
    void showAchievements()
    {
        JniMethodInfo target;
        
        if (JniHelper::getStaticMethodInfo(target,
                                           "org/cocos2dx/cpp/AppActivity",
                                           "showAchievements",
                                           "()V"))
        {
            target.env->CallStaticVoidMethod(target.classID, target.methodID);
        }    
    }    
}


