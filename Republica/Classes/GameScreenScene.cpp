/*
 * GameScreenScene.cpp
 * Michael Mancuso
 * June 12, 2014
 * Main game screen for the game.
*/

#include "GameScreenScene.h"

#include <sstream>
#include <random>

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
    bg = Sprite::create("bgMainUHD.png");
    bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    
    //scale bg to match screen
    float rX = visibleSize.width / bg->getContentSize().width;
    float rY = visibleSize.height / bg->getContentSize().height;
    
    bg->setScaleX(rX);
    bg->setScaleY(rY);
    
    int offset = 500;
    
    //TODO: This will need to be dynamic in the future
    auto tempAddPL = MenuItemImage::create(
                                            "btnAddPL.png",
                                            "btnAddPLPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    
    tempAddPL->setPosition(Vec2(visibleSize.width / 4 + origin.x, (visibleSize.height - offset) + origin.y));
    
    tempAddPL->setTag(10);
    menuItems.pushBack(tempAddPL);
    
    //left temp menu
    int btnHeight = tempAddPL->getContentSize().height;
    int bPadding = 50;
    
    auto tempAddCF = MenuItemImage::create(
                                            "btnAddCF.png",
                                            "btnAddCFPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    
    tempAddCF->setPosition(Vec2(visibleSize.width / 4, (visibleSize.height - offset) - (btnHeight + bPadding)));
    
    tempAddCF->setTag(20);
    menuItems.pushBack(tempAddCF);
    
    auto tempCampaign = MenuItemImage::create(
                                            "btnCamp.png",
                                            "btnCampPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    
    tempCampaign->setPosition(Vec2(visibleSize.width / 4, (visibleSize.height - offset) - (btnHeight*2 + bPadding)));
    
    tempCampaign->setTag(30);
    menuItems.pushBack(tempCampaign);
    
    auto tempNextTurn = MenuItemImage::create(
                                            "btnEndTurn.png",
                                            "btnEndTurnPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    
    tempNextTurn->setPosition(Vec2(visibleSize.width / 4, (visibleSize.height - offset) - (btnHeight*3 + bPadding)));
    
    tempNextTurn->setTag(40);
    menuItems.pushBack(tempNextTurn);
    
    menu = Menu::createWithArray(menuItems);
    menu->setPosition(Vec2::ZERO);
    
    //right menu
    Vector<MenuItem*> rightMenuItems;
    
    auto tempNewBill = MenuItemImage::create(
                                            "btnNewBill.png",
                                            "btnNewBillPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    
    tempNewBill->setPosition(Vec2(visibleSize.width / 1.35, visibleSize.height - offset));
    tempNewBill->setTag(50);
    rightMenuItems.pushBack(tempNewBill);
    
    auto tempBillAppeal = MenuItemImage::create(
                                            "btnAppeal.png",
                                            "btnAppealPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    
    tempBillAppeal->setPosition(Vec2(visibleSize.width / 1.35, (visibleSize.height - offset) - (btnHeight + bPadding)));
    tempBillAppeal->setTag(60);
    rightMenuItems.pushBack(tempBillAppeal);
    
    auto tempBillWording = MenuItemImage::create(
                                            "btnWording.png",
                                            "btnWordingPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    
    tempBillWording->setPosition(Vec2(visibleSize.width / 1.35, (visibleSize.height - offset) - (btnHeight * 2 + bPadding)));
    tempBillWording->setTag(70);
    rightMenuItems.pushBack(tempBillWording);
    
    
    auto tempPassBill = MenuItemImage::create(
                                            "btnPassBill.png",
                                            "btnPassBillPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    
    tempPassBill->setPosition(Vec2(visibleSize.width / 1.35 , (visibleSize.height - offset) - (btnHeight * 3 + bPadding)));
    tempPassBill->setTag(80);
    rightMenuItems.pushBack(tempPassBill);
    
    auto rightMenu = Menu::createWithArray(rightMenuItems);
    rightMenu->setPosition(Vec2::ZERO);
      
    //other ui
    turnLabel = LabelTTF::create("Turn 1", "Arial", 72);
    pcLabel = LabelTTF::create("PC: 2", "Arial", 72);
    plLabel = LabelTTF::create("PL: 0", "Arial", 72);
    cfLabel = LabelTTF::create("CF: 0", "Arial", 72);
    spLabel = LabelTTF::create("SP: 100", "Arial", 72);
    
    scoreLabel = LabelTTF::create("Score: 0", "Arial", 128);
    billLabel = LabelTTF::create("No Bill", "Arial", 72);
    
    turnLabel->setColor(ccc3(0,0,0));
    pcLabel->setColor(ccc3(0,0,0));
    plLabel->setColor(ccc3(0,0,0));
    cfLabel->setColor(ccc3(0,0,0));
    spLabel->setColor(ccc3(0,0,0));
    scoreLabel->setColor(ccc3(0,0,0));
    billLabel->setColor(ccc3(0,0,0));
    
    int padding = 20;
    
    turnLabel->setPosition(Vec2(turnLabel->getContentSize().width, visibleSize.height - turnLabel->getContentSize().height));
    pcLabel->setPosition(Vec2(turnLabel->getPosition().x + turnLabel->getContentSize().width + padding, visibleSize.height - turnLabel->getContentSize().height));
    plLabel->setPosition(Vec2(pcLabel->getPosition().x + pcLabel->getContentSize().width + padding, visibleSize.height - turnLabel->getContentSize().height));
    cfLabel->setPosition(Vec2(plLabel->getPosition().x + plLabel->getContentSize().width + padding, visibleSize.height - turnLabel->getContentSize().height));
    
    spLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - turnLabel->getContentSize().height * 2));
    
    scoreLabel->setPosition(Vec2(visibleSize.width / 2, scoreLabel->getContentSize().height + padding));
    billLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 4));
    
    //multi-menu system
    
    //create all buttons
    
    auto mainOfficeButton = MenuItemImage::create(
                                            "btnGoToOffice.png",
                                            "btnGoToOfficePressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    mainOfficeButton->setTag(BTN_GO_TO_OFFICE);
    
    auto allHillButton = MenuItemImage::create(
                                            "btnGoToHill.png",
                                            "btnGoToHillPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    allHillButton->setTag(BTN_GO_TO_HILL);
    
    //create menus
    Vector<MenuItem* > tItems; 
    tItems.pushBack(mainOfficeButton);
    
    mainMenu = Menu::createWithArray(tItems);
    mainMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    
    tItems.clear();
    tItems.pushBack(allHillButton);
    
    officeMenu = Menu::createWithArray(tItems);
    officeMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    
    tItems.clear();
    
    
    //manually retain to avoid nasty cpp error.
    mainMenu->retain();
    officeMenu->retain();
    
    
    
    //add layout to screen
    this->addChild(bg, -1);
    this->addChild(mainMenu, 1);
    
    //this->addChild(menu, 1);
    //this->addChild(rightMenu, 1);
    //this->addChild(turnLabel, 2);
    //this->addChild(pcLabel, 2);
    //this->addChild(plLabel, 2);
    //this->addChild(cfLabel, 2);
    //this->addChild(spLabel, 2);
    //this->addChild(scoreLabel, 2);
    //this->addChild(billLabel, 2);
    
    
}

void GameScreen::changeBackgrounds(GameScreen::MenuType type)
{
    switch (type)
    {
        case GameScreen::MenuType::MAIN:
            bg->setTexture(TextureCache::sharedTextureCache()->addImage("bgMainUHD.png"));
            break;
        case GameScreen::MenuType::OFFICE:
            bg->setTexture(TextureCache::sharedTextureCache()->addImage("bgOfficeUHD.png"));
            break;
        default:
            break;
    }
}

void GameScreen::changeMenu(GameScreen::MenuType type)
{
    switch (type)
    {
        case GameScreen::MenuType::MAIN:
            this->removeChild(officeMenu, false);
            this->addChild(mainMenu, 1);
            break;
        case GameScreen::MenuType::OFFICE:
            this->removeChild(mainMenu, false);
            this->addChild(officeMenu, 1);
            break;
    }
    
    changeBackgrounds(type);
}

void GameScreen::menuSelectCallback(cocos2d::Ref* sender)
{
    MenuItem* button = (MenuItem*) sender;
    
    switch(button->getTag())
    {
        case BTN_GO_TO_OFFICE:
            this->changeMenu(GameScreen::MenuType::OFFICE);
            break;
        
        case BTN_GO_TO_HILL:
            this->changeMenu(GameScreen::MenuType::MAIN);
            break;
    }
    
    //updateUI();
}

void GameScreen::onGameEnd()
{
    UserDefault::getInstance()->setIntegerForKey("endScore", score);
    UserDefault::getInstance()->setIntegerForKey("endTurn", turn);
    
    auto newScene = LeaderboardScreen::createScene();
    
    
    //check ach'ments
    if (billsPassed == 0)
    {
        UserDefault::getInstance()->setBoolForKey("duck", true);
    }
    
    if (support > 0)
    {
        UserDefault::getInstance()->setBoolForKey("com", true);
    }
    
    Director::getInstance()->replaceScene(newScene);
    
}

void GameScreen::onNextTurn()
{
    
    support--;
    pc+=2;
    turn++;
    
    if (doesBillExist())
    {
        curBill->appeal--;
    }
    
    //check for game end conditions.
    
    if (support <= 0 || turn == 20)
    {
        onGameEnd();
    }
}

void GameScreen::createBill()
{
    curBill = new Bill();
    curBill->appeal = 20;
    curBill->wording = 1;
}



void GameScreen::passBill()
{
    //roll a d100 - in the annoying C++ way.
    std::random_device rd; //rand generator
    std::mt19937 eng(rd()); //seed the generator
    std::uniform_int_distribution<> pRange(0, 100); //range
    
    //if base + appeal >= 70, bill passes, gain score += wording
    int base = pRange(eng);
    
    std::ostringstream parser;
    parser << "Base Role " << base << " Appeal: " << curBill->appeal
    << " Total Role: " << base + curBill->appeal;
    
    if(base + curBill->appeal >= 70)
    {
        parser << " Bill Passes. Score of " << curBill->wording << " is awarded.";
        score += curBill->wording;
        billsPassed++;
        
        //acheviment checks
        //cascade flags just in case
        if (billsPassed >= 15)
        {
            UserDefault::getInstance()->setBoolForKey("p15", true);
            UserDefault::getInstance()->setBoolForKey("p10", true);
            UserDefault::getInstance()->setBoolForKey("p5", true);
        }
        else if (billsPassed >= 10)
        {
            UserDefault::getInstance()->setBoolForKey("p10", true);
            UserDefault::getInstance()->setBoolForKey("p5", true);
        }
        else if (billsPassed >= 5)
        {
            UserDefault::getInstance()->setBoolForKey("p5", true);
        }
    }
    else
    {
        parser << " Bill fails. No score awarded.";
    }
    
    
    std::string holder = parser.str();
    const char* p = holder.c_str();
    
    MessageBox(p ,"Vote Result");
    
    curBill = nullptr;
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
    
    parser.str(std::string());
    parser.clear();
    
    if (doesBillExist())
    {
        parser << "Bill - Appeal: " << curBill->appeal << " Wording: " << curBill->wording;
        billLabel->setString(parser.str());
    }
    else
    {
        billLabel->setString("No Bill");
    }
}

bool GameScreen::doesBillExist()
{
    return !(curBill == nullptr);
}
