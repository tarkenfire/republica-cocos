/*
 * GameScreenScene.cpp
 * Michael Mancuso
 * June 12, 2014
 * Main game screen for the game.
*/

#ifndef __GAMESCREEN_SCENE_H__
#define __GAMESCREEN_SCENE_H__

#include "cocos2d.h"
#include "LeaderboardScreenScene.h"

class GameScreen : public cocos2d::Layer
{
    
    
    //TODO: Some of this stuff can (and should) be private
    
    //TODO: THIS IS PAPER-BOAT LEVEL LEAKY. Fix memory leaks.
    public:
        //button constants
        static const int BTN_GO_TO_OFFICE = 10;
        static const int BTN_GO_TO_HILL = 11;
        
        //structs
        
        struct Bill
        {
            int appeal;
            int wording;
        };
        //enums
        enum class MenuType { MAIN, OFFICE, HILL};
        
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
        cocos2d::LabelTTF* billLabel;
        
        //menus
        cocos2d::Menu* mainMenu;
        cocos2d::Menu* floorMenu;
        cocos2d::Menu* officeMenu;
        
        int turn = 1;
        int score = 0;
        int support = 100;
        int pc = 2;
        int pl = 0;
        int cf = 0;
        int billsPassed = 0;
        
        Bill* curBill = nullptr;
        
        
        //member methods
        static cocos2d::Scene* createScene();
        virtual bool init();
        CREATE_FUNC(GameScreen);
        void changeMenu(GameScreen::MenuType type);
        void changeBackgrounds(GameScreen::MenuType type);
        
        void onNextTurn();
        
        void createBill();
        bool doesBillExist();
        void passBill();
        void onGameEnd();
        
        void updateUI();
        
        
        //callbacks
        void menuSelectCallback(cocos2d::Ref* sender);
        
};

#endif