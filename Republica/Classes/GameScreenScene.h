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
    //TODO: Some of this stuff can (and should) be private
    public:
        //enums
        enum class MenuType { MAIN, OFFICE, BILL, CAMPAIGN };
        
        //member variables
        cocos2d::Sprite* bg;
        cocos2d::Menu* menu;
        cocos2d::Vector<cocos2d::MenuItem *> menuItems;
        
        cocos2d::Sprite* bgStatusBar;
        cocos2d::LabelTTF* turnLabel;
        cocos2d::LabelTTF* pcLabel;
        cocos2d::LabelTTF* plLabel;
        cocos2d::LabelTTF* cfLabel;
        cocos2d::LabelTTF* spLabel;
        cocos2d::LabelTTF* scoreLabel;
        
        int turn = 1;
        int score = 0;
        int support = 100;
        int pc = 2;
        int pl = 0;
        int cf = 0;
        
        
        //member methods
        static cocos2d::Scene* createScene();
        virtual bool init();
        CREATE_FUNC(GameScreen);
        void changeMenu(GameScreen::MenuType type);
        void changeBackgrounds(GameScreen::MenuType type);
        
        void onNextTurn();
        void updateUI();
        
        //callbacks
        void menuSelectCallback(cocos2d::Ref* sender);
};

#endif