/*
 * GameScreenScene.cpp
 * Michael Mancuso
 * June 12, 2014
 * Main game screen for the game.
*/

#include "GameScreenScene.h"
#include <sstream>

USING_NS_CC;

Scene* GameScreen::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScreen::create();
    scene->addChild(layer);
    return scene;
}

bool GameScreen::init()
{
    //check for super init
    if (!Layer::init())
    {
        return false;
    }
    
    //get coordinate constraints
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //set background image
    bg = Sprite::create("SplashScreenUHD.png");
    bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    
    //scale bg to match screen
    float rX = visibleSize.width / bg->getContentSize().width;
    float rY = visibleSize.height / bg->getContentSize().height;
    
    bg->setScaleX(rX);
    bg->setScaleY(rY);
    
    //create "main" menu
    this->changeMenu(GameScreen::MenuType::MAIN);
    
    int offset = 500;
    
    //TODO: This will need to be dynamic in the future
    auto tempAddPL = MenuItemImage::create(
                                            "btnAddPL.png",
                                            "btnAddPLPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    
    tempAddPL->setPosition(Vec2(visibleSize.width / 2 + origin.x, (visibleSize.height - offset) + origin.y));
    
    tempAddPL->setTag(10);
    menuItems.pushBack(tempAddPL);
    
    //this lis hacky, lazy position for termp buttons
    int btnHeight = tempAddPL->getContentSize().height;
    int bPadding = 50;
    
    auto tempAddCF = MenuItemImage::create(
                                            "btnAddCF.png",
                                            "btnAddCFPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    
    tempAddCF->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height - offset) - (btnHeight + bPadding)));
    
    tempAddCF->setTag(20);
    menuItems.pushBack(tempAddCF);
    
    auto tempCreateBill = MenuItemImage::create(
                                            "btnPassBill.png",
                                            "btnPassBillPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    
    tempCreateBill->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height - offset) - (btnHeight*2 + bPadding)));
    
    tempCreateBill->setTag(30);
    menuItems.pushBack(tempCreateBill);
    
    auto tempCampaign = MenuItemImage::create(
                                            "btnCamp.png",
                                            "btnCampPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    
    tempCampaign->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height - offset) - (btnHeight*3 + bPadding)));
    
    tempCampaign->setTag(40);
    menuItems.pushBack(tempCampaign);
    
    auto tempNextTurn = MenuItemImage::create(
                                            "btnEndTurn.png",
                                            "btnEndTurnPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    
    tempNextTurn->setPosition(Vec2(visibleSize.width / 2, (visibleSize.height - offset) - (btnHeight*4 + bPadding)));
    
    tempNextTurn->setTag(50);
    menuItems.pushBack(tempNextTurn);
    
    menu = Menu::createWithArray(menuItems);
    menu->setPosition(Vec2::ZERO);
    
    
    
    //other ui
    turnLabel = LabelTTF::create("Turn 1", "Arial", 72);
    pcLabel = LabelTTF::create("PC: 2", "Arial", 72);
    plLabel = LabelTTF::create("PL: 0", "Arial", 72);
    cfLabel = LabelTTF::create("CF: 0", "Arial", 72);
    spLabel = LabelTTF::create("SP: 100", "Arial", 72);
    
    scoreLabel = LabelTTF::create("Score: 0", "Arial", 128);
    
    turnLabel->setColor(ccc3(0,0,0));
    pcLabel->setColor(ccc3(0,0,0));
    plLabel->setColor(ccc3(0,0,0));
    cfLabel->setColor(ccc3(0,0,0));
    spLabel->setColor(ccc3(0,0,0));
    scoreLabel->setColor(ccc3(0,0,0));
    
    
    int padding = 20;
    
    turnLabel->setPosition(Vec2(turnLabel->getContentSize().width, visibleSize.height - turnLabel->getContentSize().height));
    pcLabel->setPosition(Vec2(turnLabel->getPosition().x + turnLabel->getContentSize().width + padding, visibleSize.height - turnLabel->getContentSize().height));
    plLabel->setPosition(Vec2(pcLabel->getPosition().x + pcLabel->getContentSize().width + padding, visibleSize.height - turnLabel->getContentSize().height));
    cfLabel->setPosition(Vec2(plLabel->getPosition().x + plLabel->getContentSize().width + padding, visibleSize.height - turnLabel->getContentSize().height));
    
    spLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - turnLabel->getContentSize().height * 2));
    
    scoreLabel->setPosition(Vec2(visibleSize.width / 2, scoreLabel->getContentSize().height + padding));
    
    //add layout to screen
    this->addChild(bg, -1);
    this->addChild(menu, 1);
    this->addChild(turnLabel, 2);
    this->addChild(pcLabel, 2);
    this->addChild(plLabel, 2);
    this->addChild(cfLabel, 2);
    this->addChild(spLabel, 2);
    this->addChild(scoreLabel, 2);
}

void GameScreen::changeBackgrounds(GameScreen::MenuType type)
{
    switch (type)
    {
        case GameScreen::MenuType::MAIN:
            bg->setTexture(TextureCache::sharedTextureCache()->addImage("bgMainUHD.png"));
            break;
        default:
            break;
    }
}

void GameScreen::changeMenu(GameScreen::MenuType type)
{
    
    
    changeBackgrounds(type);
}

void GameScreen::menuSelectCallback(cocos2d::Ref* sender)
{
    MenuItem* button = (MenuItem*) sender;
    
    switch (button->getTag())
    {
        case 10: //add pl
            if (pc > 0)
            {
                pc--;
                pl++;
            }
            break;
        case 20: //add cf
            if (pc > 0)
            {
                pc--;
                cf++;
            }
            break;
        case 30: //pass bill
            if (pl > 0)
            {
                pl--;
                score++;
            }
            break;
        case 40: //campaign
            if (cf > 0)
            {
                cf--;
                if (support < 100) support++;
            }
            break;
        case 50: //end turn
            turn++;
            support--;
            pc+=2;
            break;
    }
    
    updateUI();
}

void GameScreen::onNextTurn()
{
    //todo: implement
}

void GameScreen::updateUI()
{
    //nothing is easy in c++.
    std::ostringstream parser;
    
    parser << "Turn " << turn;
    turnLabel->setString(parser.str());
    
    parser.str(std::string());
    parser.clear();
    
    parser << "PC: " << pc;
    pcLabel->setString(parser.str());
    
    parser.str(std::string());
    parser.clear();
    
    parser << "PL: " << pl;
    plLabel->setString(parser.str());
    
    parser.str(std::string());
    parser.clear();
    
    parser << "CF: " << cf;
    cfLabel->setString(parser.str());
    
    parser.str(std::string());
    parser.clear();
    
    parser << "SP: " << support;
    spLabel->setString(parser.str());

    //special case for SP, change font color if below 20.
    if (support <= 20)
    {
        spLabel->setColor(ccc3(200,0,0));
    }
    else
    {
        spLabel->setColor(ccc3(0,0,0));
    }
    
    parser.str(std::string());
    parser.clear();
    
    parser << "Score: " << score;
    scoreLabel->setString(parser.str());
}