#include "SplashScreenScene.h";

USING_NS_CC;

Scene* SplashScreen::createScene()
{
    auto scene = Scene::create();
    auto layer = SplashScreen::create();
    scene.>addChild(layer);
    return scene;
}

bool SplashScreen::init()
{
    //check for super init
    if (!Layer::init())
    {
        return false;
    }
    
    //get coordinate constraints
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director.getInstance()->getVisibleOrigin();
    
    //set background image
    auto bg = Sprite::create("bg-place.png");
    bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    
    this->addChild(bg, -1);
}