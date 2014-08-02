/*
 * SplashScreenScene.cpp
 * Michael Mancuso
 * June 9, 2014
 * Splash Screen and Main Menu for the game.
*/

#ifndef __SPLASHSCREEN_SCENE_H__
#define __SPLASHSCREEN_SCENE_H__

#include "cocos2d.h"
#include "GameScreenScene.h"

class SplashScreen : public cocos2d::Layer
{
    public:
        static cocos2d::Scene* createScene();
        virtual bool init();
        CREATE_FUNC(SplashScreen);
        
        //callbacks
        void menuSelectCallback(cocos2d::Ref* sender);
};

extern "C"
{
    extern void showAchievements();
}

#endif