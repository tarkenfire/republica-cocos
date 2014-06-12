/*
 * GameScreenScene.cpp
 * Michael Mancuso
 * June 12, 2014
 * Main game screen for the game.
*/

#ifndef __GAMESCREEN_SCENE_H__
#define __GAMESCREEN_SCENE_H__

#include "cocos2d.h"

class GameScreen : public cocos2d::Layer
{
    public:
        //enums
        enum class MenuType { MAIN, OFFICE, BILL, CAMPAIGN };
        
        //member variables
        cocos2d::Sprite* bg;
        cocos2d::Menu* menu;
        cocos2d::Vector<cocos2d::MenuItem *> menuItems;
        
        cocos2d::LabelTTF* turnLabel;
        cocos2d::LabelTTF* pcLabel;
        
        
        //member methods
        static cocos2d::Scene* createScene();
        virtual bool init();
        CREATE_FUNC(GameScreen);
        void changeMenu(GameScreen::MenuType type);
        void changeBackgrounds(GameScreen::MenuType type);
        
        //callbacks
        void menuSelectCallback(cocos2d::Ref* sender);
};

#endif