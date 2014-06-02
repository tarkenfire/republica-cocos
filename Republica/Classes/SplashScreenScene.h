#ifndef __SPLASHSCREEN_SCENE_H__
#define __SPLASHSCREEN_SCENE_H__

#include "cocos2d.h"

class SplashScreen : public cocos2d::Layer
{
    public:
        static cocos2d::Scene createScene();
        virtual bool init();
        CREATE_FUNC(SplashScreen);
};

#endif