/*
 * GameScreenScene.cpp
 * Michael Mancuso
 * June 12, 2014
 * Main game screen for the game.
*/

#include "GameScreenScene.h"

#include <sstream>
#include <random>

#include <jni.h>
#include <JniHelper.h>

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
    
    statusLabel = LabelTTF::create("Turn: 1  PC: 2  PL: 0  CF: 0  SP: 100", "Arial", 64);
    //statusLabel->setAlignment(TextHAlignment::CENTER);
    statusLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - statusLabel->getContentSize().height));
    
    cocos2d::Sprite* bottomBar = Sprite::create("bgHead.png");
    bottomBar->setScaleX(visibleSize.width);
    bottomBar->setScaleY(visibleSize.height / 72);
    bottomBar->setPosition(Vec2(0, topBar->getContentSize().height));
    
    billLabel = LabelTTF::create("No Bill", "Arial", 72);
    billLabel->setPosition(Vec2(visibleSize.width / 2, billLabel->getContentSize().height));
    
    
    auto dialog = ModalDialog::create();
    dialog->configDialog(ModalDialog::DialogType::CONFIRM, "Hi", "Hi");
    
    
    //add layout to screen
    this->addChild(bg, -1);
    this->addChild(mainMenu, 1);
    this->addChild(topBar, 1);
    this->addChild(statusLabel, 2);
    this->addChild(bottomBar, 1);
    this->addChild(billLabel, 2);
    
    //this->addChild(dialog, 5);
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
                MessageBox("There is a bill already created. Only one bill can be created at a time.", "Exisiting Bill");
            }
            
            break;
        case BTN_AMMEND:
            if (doesBillExist())
            {
                if (pl > 0)
                {
                    curBill->appeal++;
                    pl--;
                    MessageBox("You add an ammendment to the bill, increasing it's appeal by 1", "Ammendment");
                }
                else
                {
                    MessageBox("You need more PL to do this. PL can be converted in the Media Center.", "Not Enough PL");
                }
            }
            else
            {
                MessageBox("There is no bill to ammend. Create a bill first.", "No Bill");
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
                    
                    std::ostringstream parser;
                    parser << "You introduce a controversial rider to the bill, hoping for a large increase in appeal. ";
                    
                    if (ridResult == 0)
                    {
                        parser << "The plan fails. Bill appeal remains the same.";
                    }
                    else // >0
                    {
                        parser << "The plan is a success, bill appeal increases by " << ridResult;
                    }
                    
                    std::string holder = parser.str();
                    const char* p = holder.c_str();
                    
                    MessageBox(p, "Rider");
                }
                else
                {
                    MessageBox("You need more PL to do this. PL can be converted in the Media Center.", "Not Enough PL");
                }
            }
            else
            {
                 MessageBox("There is no bill to add a rider to. Create a bill first.", "No Bill");
            }
            
            break;
        
        case BTN_VOTE:
            if (doesBillExist())
            {
                passBill();
            }
            else
            {
                MessageBox("There is no bill to vote on. Create a bill first.", "No Bill");
            }
            break;
        
        case BTN_CAMPAIGN:
            if (cf > 0)
            {
                cf--;
                support++;
                MessageBox("You make a few campaign speeches and gain a bit of support. SP increased by 1.", "Campaign");
            }
            else
            {
                MessageBox("You need more CF to do this. CF can be converted in the Media Center.", "Not Enough PL");
            }
            break;
        
        case BTN_INTERVIEW:
            if (cf > 0)
            {
                cf--;
                int interResult = getRandomIntInRange(0, 5);
                support+= interResult;
                
                std::ostringstream parser;
                parser << "You have an interview with a controversial pundit, hoping for a large increase in support. ";
                
                if (interResult == 0)
                {
                    parser << "The plan fails. Support remains the same.";
                }
                else // >0
                {
                    parser << "The plan is a success, support increases by " << interResult << ".";
                }
                
                std::string holder = parser.str();
                const char* p = holder.c_str();
                
                
                
                MessageBox(p, "Interview");
            }
            else
            {
                MessageBox("IMPLEMENT ME", "IMPLEMENT");
            }
            break;
        
        case BTN_LOBBY:
            if (cf > 1)
            {
                //cf-=2;
                
                flag_decay_frozen = true;
                freezeCounter = getRandomIntInRange(3, 5);
                
                MessageBox("Feature not implemented. CF is not charged.", "IMPLEMENT");
            }
            else
            {
                MessageBox("Feature not implemented. CF is not charged.", "IMPLEMENT");   
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
                MessageBox("You hold a fancy fundraiser, gaining some campaign funds. CF increased by 1.", "Fundraiser");
            }
            else
            {
                MessageBox("You do not have enough PC to do this.", "Not Enough PC");
            }
            break;
        
        case BTN_SOAPBOX:
            if (pc > 0)
            {
                pc--;
                pl++;
                MessageBox("You make an impassioned speech about a popular issue. Your peers are impressed. PL increased by 1.", "Soapbox");
            }
            else
            {
                MessageBox("You do not have enough PC to do this.", "Not Enough PC");
            }
            break;
    }
    
    updateUI();
}

void GameScreen::onGameEnd()
{
    UserDefault::getInstance()->setIntegerForKey("endScore", billsPassed);
    UserDefault::getInstance()->setIntegerForKey("endTurn", turn);
    
    auto newScene = LeaderboardScreen::createScene();
     
    //check ach'ments
    if (billsPassed == 0)
    {
        //lame duck
        unlockAchievement("CgkI56rvkNQREAIQBg");   
        UserDefault::getInstance()->setBoolForKey("duck", true);
    }
    
    if (support > 0)
    {
        unlockAchievement("CgkI56rvkNQREAIQBQ");   
        UserDefault::getInstance()->setBoolForKey("com", true);
    }
    
    Director::getInstance()->replaceScene(newScene);
    
}

void GameScreen::onNextTurn()
{
    
    support--;
    pc+=2;
    turn++;
    
    //check for game end conditions.
    if (support <= 0 || turn == 20)
    {
        onGameEnd();
        return;
    }
    
    if (doesBillExist())
    {
        curBill->appeal--;
    }
    //standard "events" that always happen.
    MessageBox("PC increases by 2. Appeals decrease by 1.","New Turn Report");
    
    
    //check for the end of bonuses
    if (bonusActive)
    {
        bonusCounter--;
        if (bonusCounter == 0)
        {
            bonusActive = false;
            cfMod = 0;
            plMod = 0;
            
            MessageBox("Bonus/Penalty Ended.", "Event");
        }
        else
        {
            pl+= plMod;
            cf+= cfMod;
            
            if (pl < 0) pl = 0;
            if (cf < 0) cf = 0;
        }
        
        updateUI();
    }
    
    //check for random events 
    std::ostringstream parser;
    
    parser << "";
    
    
    //up/down d10 roll, 1-5 = roll on "good event" table, 6-10 = roll on "bad event" table;
    int roll = getRandomIntInRange(1, 10);
    int innerRoll = getRandomIntInRange(0,100);
    int tabRoll = getRandomIntInRange(1,5);
    bool eventHappens = true;
    

    // 0-65 = Nothing happens
    // 65-75 = "minor" good or bad event
    // 75-85 = "moderate" good or bad event
    // 85+ = "massive" good or bad event
    if (roll <= 5) //good "table"
    {    
        //there's no "ranged" switches in C++, need to nest ifs
        if (0 < innerRoll && innerRoll <= 65)
        {
            eventHappens = false;
        }
        else if (66 < innerRoll && innerRoll <= 75)
        {
            switch (tabRoll)
            {
                case 1: //pl event - static
                    parser << "You have lunch with fellow lawmakers and make in-roads with several of them. PL increased by 1.";
                    pl++;
                    break;
                case 2: //pl event - dynamic
                    if (bonusActive)
                    {
                        //do nothing
                        eventHappens = false;
                    }
                    else
                    {
                        parser << "You give an interview supporting the bill of a fellow lawmaker. You gain 1 PL every turn for 3 turns.";
                        bonusActive = true;
                        bonusCounter = 3;
                        plMod = 1;
                    }
                    break;
                case 3: //cf event - static
                    parser <<"You get a modest donation from a supporter. You gain 1 CF";
                    cf++;
                    break;
                case 4: //cf event - dynamic
                    if (bonusActive)
                    {
                        //do nothing
                        eventHappens = false;
                    }
                    else
                    {
                        parser << "A small group of supporters set up a fundraising campaign. You gain 1 CF every turn for 3 turns.";
                        bonusActive = true;
                        bonusCounter = 3;
                        cfMod = 1;
                    }
                    break;
                case 5: // support event
                    parser << "You wear a nifty comical tie during an interview and people like it. You gain 2 SP.";
                    support+=2;
                    break;
            }
        }
        else if (76 < innerRoll && innerRoll <= 85)
        {
            switch (tabRoll)
            {
                case 1: //pl event - static
                    parser << "You vote in favor of a bill by a fellow lawmaker to curry favor. PL increased by 2.";
                    pl+=2;
                    break;
                case 2: //pl event - dynamic
                    if (bonusActive)
                    {
                        //do nothing
                        eventHappens = false;
                    }
                    else
                    {
                        parser << "You give a speech extolling the virtues of your party over the opposition. You gain 2 PL every turn for 3 turns.";
                        bonusActive = true;
                        bonusCounter = 3;
                        plMod = 2;
                    }
                    break;
                case 3: //cf event - static
                    parser << "You get a donation from a corperate sponsor. You gain 2 CF.";
                    cf+=2;
                    break;
                case 4: //cf event - dynamic
                    if (bonusActive)
                    {
                        //do nothing
                        eventHappens = false;
                    }
                    else
                    {
                        parser <<"A large group of supporters start a fundraising campaign. You gain 2 CF every turn for 3 turns.";
                        bonusActive = true;
                        bonusCounter = 3;
                        cfMod = 2;
                    }
                    break;
                case 5: // support event
                    parser << "You make a personal donation to your party's election council. You gain 5 SP.";
                    support+=5;
                    break;
            }
        }
        else // >85
        {
            switch (tabRoll)
            {
                case 1: //pl event - static
                    parser << "You hold a large luncheon for fellow lawmakers. PL increased by 3.";
                    pl+=3;
                    break;
                case 2: //pl event - dynamic
                    if (bonusActive)
                    {
                        //do nothing
                        eventHappens = false;
                    }
                    else
                    {
                        parser << "You help whip up votes for a fellow lawmaker's bill. You gain 3 PL every turn for 3 turns.";
                        bonusActive = true;
                        bonusCounter = 3;
                        plMod = 3;
                    }
                    break;
                case 3: //cf event - static
                    parser << "Your party's election council donates campaign funds to you. You gain 3 CF.";
                    cf+=3;
                    break;
                case 4: //cf event - dynamic
                    if (bonusActive)
                    {
                        //do nothing
                        eventHappens = false;
                    }
                    else
                    {
                        parser << "A Super-PAC is set up in support of you. You gain 3 CF every turn for 3 turns.";
                        bonusActive = true;
                        bonusCounter = 3;
                        cfMod = 3;
                    }
                    break;
                case 5: // support event
                    parser << "You cast the deciding vote on an important bill. You gain 10 SP.";
                    support+=10;
                    break;
            }
        }
    }
    else //bad "table"
    {
        
        //there's no "ranged" switches in C++, need to nest ifs
        if (0 < innerRoll && innerRoll <= 65)
        {
            eventHappens = false;
        }
        else if (66 < innerRoll && innerRoll <= 75)
        {            
            switch (tabRoll)
            {
                case 1: //pl event - static
                    parser << "You forget the name of one of your fellow lawmakers. PL decreased by 1.";
                    if (pl > 0) pl--;
                    break;
                case 2: //pl event - dynamic
                    if (bonusActive)
                    {
                        //do nothing
                        eventHappens = false;
                    }
                    else
                    {
                        parser << "You make a gaffe and accidently insult a special-interest group. You lose 1 PL every turn for 3 turns.";
                        bonusActive = true;
                        bonusCounter = 3;
                        plMod = -1;
                    }
                    break;
                case 3: //cf event - static
                    parser << "An accounting error means you have less funds than you thought. You lose 1 CF.";
                    if (cf > 0) cf--;
                    break;
                case 4: //cf event - dynamic
                    if (bonusActive)
                    {
                        //do nothing
                        eventHappens = false;
                    }
                    else
                    {
                        parser <<"You are involved in a small scandal and must use campaign funds to deflect it. You lose 1 CF every turn for 3 turns.";
                        bonusActive = true;
                        bonusCounter = 3;
                        cfMod = -1;
                    }
                    break;
                case 5: // support event
                    parser << "You publically question the relevance of a fellow lawmaker's bill. You lose 2 SP.";
                    if (support - 2 > 1) support-=2;
                    break;
            }
        }
        else if (76 < innerRoll && innerRoll <= 85)
        {   
            switch (tabRoll)
            {
                case 1: //pl event - static
                    parser << "You fail to know the name of the leader of a foreign nation live on TV. PL decreased by 2.";
                    if (pl-=2 < 0) pl = 0;
                    break;
                case 2: //pl event - dynamic
                    if (bonusActive)
                    {
                        //do nothing
                        eventHappens = false;
                    }
                    else
                    {
                        parser << "You are caught on a hot mic insulting a fellow lawmaker. You lose 2 PL every turn for 3 turns.";
                        bonusActive = true;
                        bonusCounter = 3;
                        plMod = -2;
                    }
                    break;
                case 3: //cf event - static
                    parser << "A staffer informs you that they used campaign funds to make an investment with \"some Nigerian Prince\". You lose 2 CF.";
                    if (cf -= 2 < 0) cf = 0;
                    break;
                case 4: //cf event - dynamic
                    if (bonusActive)
                    {
                        //do nothing
                        eventHappens = false;
                    }
                    else
                    {
                        parser << "You are involved in a large scandal and must use campaign funds to deflect it. You lose 2 CF every turn for 3 turns.";
                        bonusActive = true;
                        bonusCounter = 3;
                        cfMod = -2;
                    }
                    break;
                case 5: // support event
                    parser << "You fillibuster a widely popular bill to gain publicity for an unrelated issue, but it still passes. You lose 5 SP.";
                    if (support - 5 > 1) support-=5;
                    break;
            }
        }
        else // >85
        {   
            switch (tabRoll)
            {
                case 1: //pl event - static
                    parser << "You throw up on a foreign dignitary during an official lunch. PL decreased by 3.";
                    if (pl -= 3 < 0) pl = 0;
                    break;
                case 2: //pl event - dynamic
                    if (bonusActive)
                    {
                        //do nothing
                        eventHappens = false;
                    }
                    else
                    {
                        parser << "You give an explosive interview and threaten to throw a reporter off of a balcony. You lose 3 PL every turn for 3 turns."; 
                        bonusActive = true;
                        bonusCounter = 3;
                        plMod = -3;
                    }
                    break;
                case 3: //cf event - static
                    parser << "Campaign finance reform. It happens. You lose 3 CF.";
                    if (cf-=3 < 0) cf = 0;
                    break;
                case 4: //cf event - dynamic
                    if (bonusActive)
                    {
                        //do nothing
                        eventHappens = false;
                    }
                    else
                    {
                        parser << "You are involved in a massive scandal and must use campaign funds to deflect it.. You lose 3 CF every turn for 3 turns.";
                        bonusActive = true;
                        bonusCounter = 3;
                        cfMod = -3;
                    }
                    break;
                case 5: // support event
                    parser << "You cast the deciding vote to make a fellow lawmaker's bill fail. You lose 10 SP.";
                    if (support - 10 > 1) support-=10;
                    break;
            }
        }
    }
    
    if (eventHappens)
    {
        std::string holder = parser.str();
        const char* p = holder.c_str();
        MessageBox(p ,"Events");
        
        updateUI();
        
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
        parser << " Bill Passes.";
        score += curBill->wording;
        billsPassed++;
        
        //achievement checks
        //cascade flags just in case
        if (billsPassed >= 15)
        {
            unlockAchievement("CgkI56rvkNQREAIQAw");
            unlockAchievement("CgkI56rvkNQREAIQBA");
            UserDefault::getInstance()->setBoolForKey("p15", true);
            UserDefault::getInstance()->setBoolForKey("p10", true);
            UserDefault::getInstance()->setBoolForKey("p5", true);
        }
        else if (billsPassed >= 10)
        {
            unlockAchievement("CgkI56rvkNQREAIQAg");
            UserDefault::getInstance()->setBoolForKey("p10", true);
            UserDefault::getInstance()->setBoolForKey("p5", true);
        }
        else if (billsPassed >= 5)
        {
            unlockAchievement("CgkI56rvkNQREAIQAQ");
            UserDefault::getInstance()->setBoolForKey("p5", true);
        }
    }
    else
    {
        parser << " Bill fails.";
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

extern "C"
{
    void unlockAchievement(const char* text)
    {
        JniMethodInfo target;
        
        if (JniHelper::getStaticMethodInfo(target,
                                           "org/cocos2dx/cpp/AppActivity",
                                           "unlockAchievement",
                                           "(Ljava/lang/String;)V"))
        {
            jstring stringArg = target.env->NewStringUTF(text);
            target.env->CallStaticVoidMethod(target.classID, target.methodID, stringArg);
        }    
    }
}
