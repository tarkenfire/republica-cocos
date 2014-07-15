/*
 * GameScreenScene.cpp
 * Michael Mancuso
 * July 9, 2014
 * Modal dialog class for Cocos2d-x using only cocos core (implementation).
*/

#include "ModalDialog.h"
#include <sstream>

USING_NS_CC;


bool ModalDialog::init()
{
    //check for super init
    if (!LayerColor::init())
    {
        return false;
    }
    
    //get coordinate constraints
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //body sprite
    cocos2d::Sprite* modalBG = Sprite::create("bgHead.png");
    
    
    
    this->setColor(Color3B(0,0,0));
    this->setOpacity(150);
}

void ModalDialog::configDialog(DialogType dialogType, std::string title, std::string message)
{
    //get coordinate constraints
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //labels
    auto cocos2d::LabelTTF title = LabelTTF::create("Title", "Arial", 72);
    auto cocos2d::LabelTTF message = LabelTTF::create("Message", "Arial", 64);
    
    
}