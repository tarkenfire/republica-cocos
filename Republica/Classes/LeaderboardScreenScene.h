/*
 * LeaderboardScreenScene.h
 * Michael Mancuso
 * June 20, 2014
 * "Game Over" and leaderboard screen.
*/

#ifndef __LEADERBOARDSCREEN_SCENE_H__
#define __LEADERBOARDSCREEN_SCENE_H__

#include "cocos2d.h"

class LeaderboardScreen : public cocos2d::Layer
{
    public:
        static cocos2d::Scene* createScene();
        virtual bool init();
        CREATE_FUNC(LeaderboardScreen);
        
        //callback
        void menuSelectCallback(cocos2d::Ref* sender);
        
        int playerScore = 0;
        int playerTurn = 0;
        
    private:
        std::map<int, std::string> localTopList;
         
};





#endif