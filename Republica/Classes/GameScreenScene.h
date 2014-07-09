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
        static const int BTN_GO_TO_HILL_OFFICE = 11;
        static const int BTN_GO_TO_HILL_MC = 12;
        static const int BTN_GO_TO_HILL_FLOOR = 13;
        static const int BTN_GO_TO_FLOOR = 14;
        static const int BTN_NEXT_TURN = 15;
        static const int BTN_NEW_BILL = 16;
        static const int BTN_VOTE = 17;
        static const int BTN_AMMEND = 18;
        static const int BTN_RIDER = 19;
        static const int BTN_CAMPAIGN = 20;
        static const int BTN_INTERVIEW = 21;
        static const int BTN_LOBBY = 22;
        static const int BTN_GO_TO_MC = 23;
        static const int BTN_FUNDRAISE = 24;
        static const int BTN_SOAPBOX = 25;
        
        //structs
        
        struct Bill
        {
            int appeal;
            int wording;
        };
        //enums
        enum class MenuType { MAIN, OFFICE, FLOOR, MEDIA};
        
        //member variables
        cocos2d::Sprite* bg;
                
        //menus
        cocos2d::Menu* mainMenu;
        cocos2d::Menu* floorMenu;
        cocos2d::Menu* officeMenu;
        cocos2d::Menu* MCMenu;
        
        //label ui
        cocos2d::LabelTTF* statusLabel;
        cocos2d::LabelTTF* billLabel;
        
        int turn = 1;
        int score = 0;
        int support = 100;
        int pc = 2;
        int pl = 0;
        int cf = 0;
        int billsPassed = 0;
        
        Bill* curBill = nullptr;
        
        bool flag_decay_frozen = false;
        int freezeCounter = 0;
        
        
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
        
        //utility
        int getRandomIntInRange(int min, int max);
        
        
        //callbacks
        void menuSelectCallback(cocos2d::Ref* sender);
        
};

#endif