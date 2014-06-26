/*
 * AchScreenScene.h
 * Michael Mancuso
 * June 25, 2014
 * Ach screen
*/

#ifndef __ACHSCREEN_SCENE_H__
#define __ACHSCREEN_SCENE_H__

#include "cocos2d.h"

class AchScreen : public cocos2d::Layer
{
    
    public:
        static cocos2d::Scene* createScene();
        virtual bool init();
        CREATE_FUNC(AchScreen);
        
        cocos2d::Sprite* bg;
        
        cocos2d::Sprite* achP5;
        cocos2d::Sprite* achP10;
        cocos2d::Sprite* achP15;
        
        cocos2d::Sprite* achPTot;
        
        cocos2d::Sprite* achCom;
        
        cocos2d::Sprite* achNeg;
        
        
        //callbacks
        void menuSelectCallback(cocos2d::Ref* sender);
};

#endif