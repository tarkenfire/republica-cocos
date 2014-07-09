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
    
    
    //multi-menu system
    
    //button pool for creating menus
    
    auto mainOfficeButton = MenuItemImage::create(
                                            "btnGoToOffice.png",
                                            "btnGoToOfficePressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    mainOfficeButton->setTag(BTN_GO_TO_OFFICE);
    
    auto mainFloorButton = MenuItemImage::create(
                                            "btnGoToFloor.png",
                                            "btnGoToFloorPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    mainFloorButton->setTag(BTN_GO_TO_FLOOR);
    
    auto mainMCButton = MenuItemImage::create(
                                            "btnGoToMC.png",
                                            "btnGoToMCPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    mainMCButton->setTag(BTN_GO_TO_MC);
    
    auto floorHillButton = MenuItemImage::create(
                                            "btnGoToHill.png",
                                            "btnGoToHillPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    floorHillButton->setTag(BTN_GO_TO_HILL_FLOOR);
    
    auto hillNextTurnButton = MenuItemImage::create(
                                            "btnNextTurn.png",
                                            "btnNextTurnPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    hillNextTurnButton->setTag(BTN_NEXT_TURN);
    
    auto floorNewBillButton = MenuItemImage::create(
                                            "btnNewBill.png",
                                            "btnNewBillPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    floorNewBillButton->setTag(BTN_NEW_BILL);
    
    auto floorVoteButton = MenuItemImage::create(
                                            "btnVote.png",
                                            "btnVotePressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    floorVoteButton->setTag(BTN_VOTE);
    
    auto floorAmmendButton = MenuItemImage::create(
                                            "btnAmmend.png",
                                            "btnAmmendPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    floorAmmendButton->setTag(BTN_AMMEND);
    
    auto floorRiderButton = MenuItemImage::create(
                                            "btnRider.png",
                                            "btnRiderPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    floorRiderButton->setTag(BTN_RIDER);
    
    auto officeCampButton = MenuItemImage::create(
                                            "btnCampaign.png",
                                            "btnCampaignPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    officeCampButton->setTag(BTN_CAMPAIGN);
    
    auto officeInterviewButton = MenuItemImage::create(
                                            "btnInterview.png",
                                            "btnInterviewPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    officeInterviewButton->setTag(BTN_INTERVIEW);
    
    auto officeLobbyButton = MenuItemImage::create(
                                            "btnLobby.png",
                                            "btnLobbyPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    officeLobbyButton->setTag(BTN_LOBBY);
    
    auto officeHillButton = MenuItemImage::create(
                                            "btnGoToHill.png",
                                            "btnGoToHillPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    officeHillButton->setTag(BTN_GO_TO_HILL_OFFICE);
    
    auto MCHillButton = MenuItemImage::create(
                                            "btnGoToHill.png",
                                            "btnGoToHillPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    MCHillButton->setTag(BTN_GO_TO_HILL_MC);
    
    auto MCFundButton = MenuItemImage::create(
                                            "btnFundraise.png",
                                            "btnFundraisePressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    MCFundButton->setTag(BTN_FUNDRAISE);
    
    auto MCSoapButton = MenuItemImage::create(
                                            "btnSoap.png",
                                            "btnSoapPressed.png",
                                            CC_CALLBACK_1(GameScreen::menuSelectCallback, this));
    MCSoapButton->setTag(BTN_SOAPBOX);
    
    //create menus - hill menu
    Vector<MenuItem* > tItems;
    tItems.pushBack(mainMCButton);
    tItems.pushBack(mainOfficeButton);
    tItems.pushBack(mainFloorButton);
    tItems.pushBack(hillNextTurnButton);
    
    mainMenu = Menu::createWithArray(tItems);
    mainMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    mainMenu->alignItemsVerticallyWithPadding(40);
    
    //office menu
    tItems.clear();
    tItems.pushBack(officeCampButton);
    tItems.pushBack(officeInterviewButton);
    tItems.pushBack(officeLobbyButton);
    tItems.pushBack(officeHillButton);
    
    officeMenu = Menu::createWithArray(tItems);
    officeMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    officeMenu->alignItemsVerticallyWithPadding(40);
    
    //floor menu
    tItems.clear();
    tItems.pushBack(floorNewBillButton);
    tItems.pushBack(floorAmmendButton);
    tItems.pushBack(floorRiderButton);
    tItems.pushBack(floorVoteButton);
    tItems.pushBack(floorHillButton);
    
    floorMenu = Menu::createWithArray(tItems);
    floorMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100));
    floorMenu->alignItemsVerticallyWithPadding(40);
    
    //media center menu
    tItems.clear();
    tItems.pushBack(MCFundButton);
    tItems.pushBack(MCSoapButton);
    tItems.pushBack(MCHillButton);
    
    MCMenu = Menu::createWithArray(tItems);
    MCMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    MCMenu->alignItemsVerticallyWithPadding(40);
    
    //manually retain to avoid nasty cpp error.
    mainMenu->retain();
    officeMenu->retain();
    floorMenu->retain();
    MCMenu->retain();
    
    
    //status labels
    cocos2d::Sprite* topBar = Sprite::create("bgHead.png");
    
    topBar->setScaleX(visibleSize.width);
    topBar->setScaleY(visibleSize.height / 64);
    topBar->setPosition(Vec2(0, visibleSize.height - topBar->getContentSize().height));
    
    statusLabel = LabelTTF::create("Turn: 1  PC: 0  PL: 0  CF: 0  SP: 100", "Arial", 64);
    //statusLabel->setAlignment(TextHAlignment::CENTER);
    statusLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - statusLabel->getContentSize().height));
    
    cocos2d::Sprite* bottomBar = Sprite::create("bgHead.png");
    bottomBar->setScaleX(visibleSize.width);
    bottomBar->setScaleY(visibleSize.height / 72);
    bottomBar->setPosition(Vec2(0, topBar->getContentSize().height));
    
    billLabel = LabelTTF::create("No Bill", "Arial", 72);
    billLabel->setPosition(Vec2(visibleSize.width / 2, billLabel->getContentSize().height));
    
    
        
    
    //add layout to screen
    this->addChild(bg, -1);
    this->addChild(mainMenu, 1);
    this->addChild(topBar, 1);
    this->addChild(statusLabel, 2);
    this->addChild(bottomBar, 1);
    this->addChild(billLabel, 2);
    
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
        case GameScreen::MenuType::FLOOR:
            bg->setTexture(TextureCache::sharedTextureCache()->addImage("bgFloorUHD.png"));
            break;
        case GameScreen::MenuType::MEDIA:
            bg->setTexture(TextureCache::sharedTextureCache()->addImage("bgMediaUHD.png"));
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
            this->removeChild(floorMenu, false);
            this->removeChild(MCMenu, false);
            this->addChild(mainMenu, 1);
            break;
        case GameScreen::MenuType::OFFICE:
            this->removeChild(mainMenu, false);
            this->addChild(officeMenu, 1);
            break;
        case GameScreen::MenuType::FLOOR:
            this->removeChild(mainMenu, false);
            this->addChild(floorMenu, 1);
            break;
        case GameScreen::MenuType::MEDIA:
            this->removeChild(mainMenu, false);
            this->addChild(MCMenu, 1);
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
        case BTN_GO_TO_HILL_OFFICE:
            this->changeMenu(GameScreen::MenuType::MAIN);
            break;
        case BTN_GO_TO_HILL_MC:
            this->changeMenu(GameScreen::MenuType::MAIN);
            break;
        case BTN_GO_TO_HILL_FLOOR:
            this->changeMenu(GameScreen::MenuType::MAIN);
            break;
        case BTN_GO_TO_FLOOR:
            this->changeMenu(GameScreen::MenuType::FLOOR);
            break;
        case BTN_GO_TO_MC:
            this->changeMenu(GameScreen::MenuType::MEDIA);
            break;
        
        case BTN_NEW_BILL:
            if (!doesBillExist())
            {
                createBill();
            }
            else
            {
                MessageBox("IMPLEMENT ME", "IMPLEMENT");
            }
            
            break;
        case BTN_AMMEND:
            if (doesBillExist())
            {
                if (pl > 0)
                {
                    curBill->appeal++;
                    pl--;
                    MessageBox("IMPLEMENT ME", "IMPLEMENT");
                }
                else
                {
                    MessageBox("IMPLEMENT ME", "IMPLEMENT");
                }
            }
            else
            {
                MessageBox("IMPLEMENT ME", "IMPLEMENT");
            }
            
            break;
        
        case BTN_RIDER:
             if (doesBillExist())
            {
                if (pl > 0)
                {
                    pl--;
                    int ridResult = getRandomIntInRange(0,5);
                    curBill->appeal+= ridResult;
                    
                    MessageBox("IMPLEMENT ME", "IMPLEMENT");
                }
                else
                {
                    MessageBox("IMPLEMENT ME", "IMPLEMENT");
                }
            }
            else
            {
                MessageBox("IMPLEMENT ME", "IMPLEMENT");
            }
            
            break;
        
        case BTN_VOTE:
            passBill();
            break;
        
        case BTN_CAMPAIGN:
            if (cf > 0)
            {
                cf--;
                support++;
                MessageBox("IMPLEMENT ME", "IMPLEMENT");
            }
            else
            {
                MessageBox("IMPLEMENT ME", "IMPLEMENT");
            }
            break;
        
        case BTN_INTERVIEW:
            if (cf > 0)
            {
                cf--;
                int interResult = getRandomIntInRange(0, 5);
                support+= interResult;
                
                MessageBox("IMPLEMENT ME", "IMPLEMENT");
            }
            else
            {
                MessageBox("IMPLEMENT ME", "IMPLEMENT");
            }
            break;
        
        case BTN_LOBBY:
            if (cf > 1)
            {
                cf-=2;
                
                flag_decay_frozen = true;
                freezeCounter = getRandomIntInRange(3, 5);
                
                MessageBox("IMPLEMENT ME", "IMPLEMENT");
            }
            else
            {
                MessageBox("IMPLEMENT ME", "IMPLEMENT");   
            }
            
            break;
    
        case BTN_NEXT_TURN:
            onNextTurn();
            break;
        
        case BTN_FUNDRAISE:
            if (pc > 0)
            {
                pc--;
                cf++;
                MessageBox("IMPLEMENT ME", "IMPLEMENT");
            }
            else
            {
                MessageBox("IMPLEMENT ME", "IMPLEMENT");
            }
            break;
        
        case BTN_SOAPBOX:
            if (pc > 0)
            {
                pc--;
                pl++;
                MessageBox("IMPLEMENT ME", "IMPLEMENT");
            }
            else
            {
                MessageBox("IMPLEMENT ME", "IMPLEMENT");
            }
            break;
        
        
        
    }
    
    updateUI();
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
}



void GameScreen::passBill()
{    
    //if base + appeal >= 70, bill passes, gain score += wording
    int base = getRandomIntInRange(0,100);
    
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
    
    //update top status bar
    parser << "Turn: " << turn << "  PC: " << pc << "  PL: " <<
        pl << "  CF: " << cf << "  SP: " << support;
        
    statusLabel->setString(parser.str());
    
    parser.str(std::string());
    parser.clear();
    
    //update bottom status bar
    if (doesBillExist())
    {
        parser << "Current Bill - Appeal: " << curBill->appeal;
        billLabel->setString(parser.str());
    }
    else
    {
        billLabel->setString("No Bill");
    }
    
    
}

int GameScreen::getRandomIntInRange(int min, int max)
{
    std::random_device rd; //rand generator
    std::mt19937 eng(rd()); //seed the generator
    std::uniform_int_distribution<> pRange(min, max); //range
    
    return pRange(eng);
}

bool GameScreen::doesBillExist()
{
    return !(curBill == nullptr);
}
