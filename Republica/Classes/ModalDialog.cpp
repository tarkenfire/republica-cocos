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
    modalBG = Sprite::create("bgHead.png");
    
    modalBG->setScaleX(visibleSize.width - (visibleSize.width / 16));
    modalBG->setScaleY(visibleSize.height / 32);
    modalBG->setPosition(Vec2(0, visibleSize.height / 2));
    
    
    
    this->setColor(Color3B(0,0,0));
    this->setOpacity(150);
    this->addChild(modalBG, 1);
}

void ModalDialog::configDialog(DialogType dialogType, std::string title, std::string message)
{
    //get coordinate constraints
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //labels
    //auto cocos2d::LabelTTF title = LabelTTF::create("Title", "Arial", 72);
    //auto cocos2d::LabelTTF message = LabelTTF::create("Message", "Arial", 64);
    
    cocos2d::LabelTTF* titleLabel = LabelTTF::create("Title", "Arial", 64);
    cocos2d::LabelTTF* messageLabel = LabelTTF::create("Message", "Arial", 64);
    
    titleLabel->setPosition(Vec2(visibleSize.width / 2, modalBG->getPosition().y));
    
    this->addChild(titleLabel, 4);
}