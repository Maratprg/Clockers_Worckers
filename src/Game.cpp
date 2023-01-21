#include "Game.h"
#include "globalic.h"

//implamentation of variables that define frame speed velocity of game loop by setting.
const float Game::playerSpeed = 400.f;
const sf::Time Game::timePerFrame = sf::seconds(1.f/60.f);  //frames speed by setting 60 hz of monitor framing

//implementation of constructor and destructor of the game class
Game::Game() : mWindow(sf::VideoMode(world_S.x, world_S.y), "Clockers-Workers")
, mIsMovingUp(false)
, mIsMovingDown(false)
, mIsMovingRight(false)
, mIsMovingLeft(false)
, segmentTriger(false)
, timeCControllerSeg(1)
, segIterVar(0)
, digitSecure(0)
{
//initialization of random function
srand(time(nullptr));

//system joystick update
sf::Joystick::update();

//system background autoset
this->autoSetBackG();

//set music volume 70%
YIU.getMusic().setVolume(70.f);

        //ini welders start position coordinates
        w_startPos[0].x = 100.f;
        w_startPos[0].y = 100.f;
        w_startPos[1].x = 150.f;
        w_startPos[1].y = 100.f;

    //welders load
    fWelder.loadWelder();
    fWelder.sprite.setPosition(w_startPos[0].x, w_startPos[0].y);
    fWelder.loadWelderBlame();
    fWelder.setWldrFace();

    sWelder.loadWelder();
    sWelder.sprite.setPosition(w_startPos[1].x, w_startPos[0].y);
    sWelder.loadWelderBlame();
    sWelder.setWldrFace();

//resize bullet vector
bulletVec.reserve(20);

//systemTime autoset and score! text
this->score.visible = true;
this->autoSetTimeText();
//this->buildGame();
this->buildStartMenu();
//this->buildEndMenu();
//this->buildClock();

//YIU.getMusic().play();
this->fillUpMySounds();

}//end of ctor

Game::~Game(){}//end of dtor


void Game::buildGame()
{
    //end music
    YIU.getMusic().stop();

    idScene = S_SCENE::FIRST;

    //score
    this->score.visible = true;

    //player
    mPlayer.setPosition(500.f, 300.f);
    mPlayer.setRadius(50.f);
    mPlayer.setPosition(world_S.x/2 - 50.f, -55.f);
    mPlayer.setFillColor(sf::Color(93, 147, 182, 255));
    mPlayer.setOutlineColor(sf::Color(30,144,255,255));
    mPlayer.setOutlineThickness(8);

    //ini welders start position coordinates
    w_startPos[0].x = 100.f;
    w_startPos[0].y = 100.f;
    w_startPos[1].x = 150.f;
    w_startPos[1].y = 100.f;

    //welders load
    //fWelder.loadWelder();
    fWelder.sprite.setPosition(w_startPos[0].x, w_startPos[0].y);
    fWelder.loadWelderBlame();
    fWelder.setWldrFace();

    //sWelder.loadWelder();
    sWelder.sprite.setPosition(w_startPos[1].x, w_startPos[0].y);
    sWelder.loadWelderBlame();
    sWelder.setWldrFace();

    //G_Column inicialization
    g_column.visible = true;
    g_column.r_shape.setSize(sf::Vector2f(80.f,280.f));
    g_column.r_shape.setFillColor(sf::Color(93, 147, 182, 255)); // red coloring 239 28 109 255
    g_column.r_shape.setPosition(sf::Vector2f(world_S.x/2 - 40.f, world_S.y/2 + 110.f));

    //spider inicialisation
    spider.sprite.setTexture(YIU.getTextureEnemy(SPC_Texture::ID_Enemys::Spider));
    spider.sprite.setScale(0.4, 0.4);
    spider.turn(true);

    //bullet creatures ...
    b_creatures.boxbag.setTexture(YIU.getTextureEnemy(SPC_Texture::ID_Enemys::BoxBag));
    b_creatures.pipiter.setTexture(YIU.getTextureEnemy(SPC_Texture::ID_Enemys::Pipiter));
    b_creatures.r_shape_bag.setFillColor(sf::Color(36,33,155,255));
        b_creatures.r_shape_bag.setOutlineColor(sf::Color(255,255,255,255));
        b_creatures.r_shape_bag.setOutlineThickness(3);
        b_creatures.r_shape_bag.setSize(sf::Vector2f(20.f,20.f));
    b_creatures.r_shape_pipiter.setFillColor(sf::Color(230,45,255,255));
        b_creatures.r_shape_pipiter.setOutlineColor(sf::Color(255,255,255,255));
        b_creatures.r_shape_pipiter.setOutlineThickness(3);
        b_creatures.r_shape_pipiter.setSize(sf::Vector2f(20,20));

    //Indian Creature with Horsefly bullet
    indian_stru.horsefly.setTexture(YIU.getTextureEnemy(SPC_Texture::ID_Enemys::HorseFly));
    indian_stru.horsefly.setTextureRect(sf::IntRect(0,0,178,160) );
    indian_stru.horsefly.setScale(0.2,0.2);
        indian_stru.indian.setTexture(YIU.getTextureEnemy(SPC_Texture::ID_Enemys::Indian));
        indian_stru.indian.makeByChar(true);
        indian_stru.indian.autoSetFight(true);
            //indian plase positions
            indian_stru.i_pos[0].x = 0;
            indian_stru.i_pos[0].y = world_S.y - 300;
            indian_stru.i_pos[1].x = world_S.x - 174; //right
            indian_stru.i_pos[1].y = world_S.y - 300;
            //horsefly start positions
            indian_stru.h_pos[0].x = 150;
            indian_stru.h_pos[0].y = world_S.y - 244;
            indian_stru.h_pos[1].x = world_S.x - 182; //right
            indian_stru.h_pos[1].y = world_S.y - 244;
        indian_stru.horsefly.setTextureRect(sf::IntRect(178,0,-178,160) ); //reverse
        indian_stru.indian.autoSetFight(false);
        indian_stru.indianLeft = false;
        indian_stru.indian.setPosition(indian_stru.i_pos[1]);
        indian_stru.horsefly.setPosition(indian_stru.h_pos[1]);
    indian_stru.indian.visible = false;
    indian_stru.horsefly.visible = false;


            //debugCreature
            debugCreature.setTexture(YIU.getTextureEnemy(SPC_Texture::ID_Enemys::Roster));
            debugCreature.makeByChar(true);
            debugCreature.autoSetWalk(true);
            debugCreature.visible = false;

            //temp_text.loadFromFile("Media/testing/1_32.png");
            //temporary.setTexture(temp_text);

            this->fillUpVectorCreatures(60);

//indication of scene
idScene = S_SCENE::FIRST;

//setting numbers
seg.setBoolNumber(seg.numberOne, 6);
seg.setBoolNumber(seg.numberTwo, 5);
seg.setBoolNumber(seg.numberThree, 3);
seg.setBoolNumber(seg.numberFour, 7);
memDig[0] = 6;
memDig[1] = 5;
memDig[2] = 3;
memDig[3] = 7;
}//end of build

//implementation of the run function --- it is a general stick of the game (GENERAL GAME LOOP)
void Game::run()
{
    iternalCLK.restart();
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        //global mechanik time value
        uint32_t t = iternalCLK.getElapsedTime().asMilliseconds()/100;

        //system time update
        dateText.setString(getSysTime());

        //std::cout << "SEGMENT FOUR UP | DOWN " << seg.fourUP << " | " <<  seg.fourDOWN
        //<< " segmentTRIGER " << segmentTriger << std::endl;

        if (!segmentTriger)
        {
            memDig[0] = (getSysHour()/10)%10 ;
            memDig[1] = (getSysHour())%10 ;
            memDig[2] = (getSysMin()/10)%10 ;
            memDig[3] = (getSysMin())%10 ;

            seg.setBoolNumber(seg.numberOne, memDig[0] );
            seg.setBoolNumber(seg.numberTwo, memDig[1] );
            seg.setBoolNumber(seg.numberThree, memDig[2] );
            seg.setBoolNumber(seg.numberFour,  memDig[3] );
        }; //end of if

        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            processEvents();
            processEnemyBullets(t);
            if(idScene == FIRST) brainWishCollide(t);
            update(timePerFrame, t);
            updateSegMech(timePerFrame, t);
                //storeCreatures();

        }
        processSpecEfects(t);
        storeCreatures();
        playSound();
        render();
    }
}

//implementation of the event (input) controlling function of the game class (INPUT CONTROLS)
void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::KeyPressed:
                handlePlayerInput (event);
                //std::cout << "It is Inputed " << event.key.code << std::endl;
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput (event);
                //std::cout << "It is Released " << event.key.code << std::endl;
                break;
            case sf::Event::JoystickMoved:
                 if(joySUS.getStatus() != JoyPad::Status::READY) { serviceSound[21] = true; checkUpJoy (event); }
                 else { handlePlayerInput(event); }; /*game mooving*/
                break;
            case sf::Event::JoystickButtonPressed:
                 if(joySUS.getStatus() != JoyPad::Status::READY) { serviceSound[21] = true; checkUpJoy (event); }
                 else { handlePlayerInput(event); }; /*game mooving*/
                break;
            case sf::Event::MouseButtonReleased:
                handlePlayerInput (event);
                break;
            case sf::Event::Closed:
                //std::cout << "It is Closed " << std::endl;
                mWindow.close();
                break;
        }
    }
}//end of void

// implementation of input events
void Game::handlePlayerInput(sf::Event& event)
{
    if (idScene == S_SCENE::ZERRO)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Up && joySUS.getStatus() == JoyPad::Status::READY) { menu.turnTrigger(true); serviceSound[23] = true; }
            else if (event.key.code == sf::Keyboard::Down && joySUS.getStatus() == JoyPad::Status::READY) { menu.turnTrigger(false); serviceSound[23] = true; }
            else if (event.key.code == sf::Keyboard::Enter && joySUS.getStatus() == JoyPad::Status::READY)
            {
                    serviceSound[21] = true;
                    if (menu.threeTrigger == 1){ buildClock(); }
                    else if (menu.threeTrigger == 2) { buildGame(); }
                    else if (menu.threeTrigger == 3)
                        {
                                //default block
                                menu.animaLabelCreatures.trigger = false;
                                menu.animaGameCone.trigger = false;
                                menu.animaSpiderPersonage.trigger = false;
                                menu.text[4].setCharacterSize(32);
                                menu.text[4].setString(joySUS.getCheckReport(0));

                            joySUS.setStatus(JoyPad::Status::SEEK_PORT);
                        } //temporary untrigging menu
                    else {};


            }
            else if (event.key.code == sf::Keyboard::S && joySUS.getStatus() == JoyPad::Status::READY)
            {
                menu.textAlarm.setFillColor(sf::Color(236,205,186,255));
                menu.flagAlarm = true;
                    menu.inserted = "";
            }
            else if (joySUS.getStatus() == JoyPad::Status::READY && menu.flagAlarm && event.key.code > 25 && event.key.code < 36)
            {
               int in = (((event.key.code)%10 + 4)%10);
               if (menu.inserted.size() != 4) menu.inserted = menu.inserted + std::to_string(in);
                // else reset
            }
            else {};
        };

          //temporary **************************************
          //  event.type == sf::Event::JoystickButtonPressed
          //   event.joystickButton.button    button manage
          //  event.type == sf::Event::JoystickMoved
          //   float x = sf::Joystick::getAxisPosition(event.joystickButton.joystickId, sf::Joystick::X)
          //   float y = sf::Joystick::getAxisPosition(event.joystickButton.joystickId, sf::Joystick::Y)


           // std::cout << "ready status " << (joySUS.getStatus() == JoyPad::Status::READY) << std::endl;

          //GAME PAD MENU INPUTS
          if (event.type == sf::Event::JoystickMoved && joySUS.getStatus() == JoyPad::Status::READY &&
             event.joystickButton.joystickId == joySUS.getButtonData(0))
          {
              //HERE

              float y = sf::Joystick::getAxisPosition(joySUS.getButtonData(0), sf::Joystick::Y);
              if (y > joySUS.getAxisData(7).fmin) { menu.turnTrigger(false); serviceSound[23] = true; }
              else if (y < -(joySUS.getAxisData(7).fmin)) { menu.turnTrigger(true); serviceSound[23] = true; }
              else {};
          }
          else if(event.type == sf::Event::JoystickButtonPressed && joySUS.getStatus() == JoyPad::Status::READY &&
                    event.joystickButton.joystickId == joySUS.getButtonData(0))
          {
              if (menu.threeTrigger == 2) { serviceSound[21] = true; buildGame(); }
          }
          else {};
    }
    else if (idScene == S_SCENE::FIRST)
    {
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
        {
            //turn false inputs joy
            turnInputsJK(false);

            bool value;
            if (event.type == sf::Event::KeyPressed) { value = true; }
            else if (event.type == sf::Event::KeyReleased) {value = false;}
            else {};

            if  (event.key.code == sf::Keyboard::Left)    {mIsMovingLeft = value;  }
            else if (event.key.code == sf::Keyboard::Right) {mIsMovingRight = value; }
            else if (event.key.code == sf::Keyboard::Space) { if (bulletVec.empty() || (bulletVec.size() < 20)) mPlayerStartBullet();}

            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::B &&
                     !b_creatures.r_shape_bag_untrigged && !b_creatures.boxbag_anima.trigger)
                {
                    b_creatures.boxbag.setPosition(sf::Vector2f(mPlayer.getPosition().x, mPlayer.getPosition().y));
                    b_creatures.boxbag_anima.trigger = true;
                    b_creatures.boxbag_anima.registrica = (iternalCLK.getElapsedTime().asMilliseconds()/100) + b_creatures.boxbag_anima.timer;
                    score.s_Int--;
                    serviceSound[6] = true; //boxBagBurn
                }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N &&
                    !b_creatures.r_shape_pipiter_untrigged && !b_creatures.pipiter_anima.trigger)
                {
                    b_creatures.pipiter.setPosition(sf::Vector2f(mPlayer.getPosition().x, mPlayer.getPosition().y));
                    b_creatures.pipiter_anima.trigger = true;
                    b_creatures.pipiter_anima.registrica = (iternalCLK.getElapsedTime().asMilliseconds()/100) + b_creatures.pipiter_anima.timer;
                    score.s_Int--;
                    serviceSound[8] = true; //pipiterBurn
                }

           else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::V) { spider.turn(true); }
           else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) { spider.turn(false); }


           //temporary key
           /* else if (event.type == sf::Event::KeyPressed &&
                     event.key.code == sf::Keyboard::Delete && !segmentTriger)
                        {
                           segmentTriger = true; // trigging segment by key
                                curSegPos = seg.posS;     // general array sf::Vector2f PTR
                                currentSeg = seg.rectS;  // general array rectangel entity
                                currentBL = seg.numberTwo; // general array bool PTR
                           digitSecure = 1;
                           std::cout << " segment triger " << multiTriger << std::endl;



                         //NEVER  ERASE  !!!!!
                         segmentTriger = true; // trigging segment by key
                                //seg.segDown = true; //seg.fourDOWN = true; <=>
                                //seg.segUp = false; //seg.fourUP = false; <=>
                                curSegPos = seg.posFR;     // general array sf::Vector2f PTR
                                currentSeg = seg.rectFR;   // general array rectangel entity
                                currentBL = seg.numberFour; // general array bool PTR
                           digitSecure = 3;
                           std::cout << " segment triger " << multiTriger << std::endl;
            }*/

            else if (event.type == sf::Event::KeyPressed &&
                     event.key.code == sf::Keyboard::H)
            {

                debugCreature.changeFrame();
                //creature_vec.at(0).changeFrame();
            }
            else {};
        }; //end of if keyboard input

        //********************GAME PAD DATA EVENTS
        //move event
        if (event.type == sf::Event::JoystickMoved)
        {
           //turn inputs to joy
           turnInputsJK(true);

           float x = sf::Joystick::getAxisPosition(joySUS.getButtonData(0), sf::Joystick::X);
           float y = sf::Joystick::getAxisPosition(joySUS.getButtonData(0), sf::Joystick::Y);

           if (event.joystickButton.joystickId == joySUS.getButtonData(0))
           {
               if (x > joySUS.getAxisData(6).fmin) mIsMovingRight = true;
               else if (x < -(joySUS.getAxisData(6).fmin)) mIsMovingLeft = true;
               else  mIsMovingRight = mIsMovingLeft = false;
           };
        }

        //button events and released are protected if you dont need queue regime
        if (event.type == sf::Event::JoystickButtonPressed || event.type == sf::Event::JoystickButtonReleased)
        {
           if (event.joystickButton.joystickId == joySUS.getButtonData(0) &&
               event.joystickButton.button == joySUS.getButtonData(2)) {  if (bulletVec.empty() || (bulletVec.size() < 20)) animaBulletQueue.trigger = true; };

           if (sf::Event::JoystickButtonReleased && event.joystickButton.joystickId == joySUS.getButtonData(0))
           {
               if (event.joystickButton.button == joySUS.getButtonData(3) &&
                   !b_creatures.r_shape_bag_untrigged && !b_creatures.boxbag_anima.trigger) //bag case
                   {
                        b_creatures.boxbag.setPosition(sf::Vector2f(mPlayer.getPosition().x, mPlayer.getPosition().y));
                        b_creatures.boxbag_anima.trigger = true;
                        b_creatures.boxbag_anima.registrica = (iternalCLK.getElapsedTime().asMilliseconds()/100) + b_creatures.boxbag_anima.timer;
                        score.s_Int--;
                        serviceSound[6] = true; //boxBagBurn
                   }
               else if (event.joystickButton.button == joySUS.getButtonData(4) &&
                        !b_creatures.r_shape_pipiter_untrigged && !b_creatures.pipiter_anima.trigger) //desk case
                   {
                        b_creatures.pipiter.setPosition(sf::Vector2f(mPlayer.getPosition().x, mPlayer.getPosition().y));
                        b_creatures.pipiter_anima.trigger = true;
                        b_creatures.pipiter_anima.registrica = (iternalCLK.getElapsedTime().asMilliseconds()/100) + b_creatures.pipiter_anima.timer;
                        score.s_Int--;
                        serviceSound[8] = true; //pipiterBurn
                   }
               else if  (event.joystickButton.button == joySUS.getButtonData(5) && event.type != sf::Event::JoystickMoved)
               {
                   if (spider.Left == true) spider.turn(false);
                   else spider.turn(true);
               }
               else {};
           };//end of dop button statments
         };//end of joypad button implement

    }//end of first if
    else if(idScene == S_SCENE::SECOND)
    {
        if (event.key.code == sf::Keyboard::Enter || event.joystickButton.button == joySUS.getButtonData(1)) buildStartMenu();
    }//end of else if
    else if (idScene == S_SCENE::THIRD)
    {
      //CLOCK SCENE HANDLE INPUT
      /*if (event.type == sf::Event::KeyPressed &&
          event.key.code == sf::Keyboard::Delete && !segmentTriger)
        {
           segmentTriger = true; // trigging segment by key
                curSegPos = seg.posTH;     // general array sf::Vector2f PTR
                currentSeg = seg.rectTH;  // general array rectangel entity
                currentBL = seg.numberThree; // general array bool PTR
           digitSecure = 2; //from zerro for three
           //std::cout << " segment triger " << multiTriger << std::endl;
        };*/

      if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space && menu.sysAlarmCounter < 20) menu.sysAlarmCounter = 20;
      if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape && !segmentTriger) { menu.sysAlarmCounter = 20; buildStartMenu(); };

    }
    else if(idScene == S_SCENE::LAST)
    {

    }//end of else if
    else {};//end of else

        //TESTING MOUSE COORDINATES
        if (event.type == sf::Event::MouseButtonReleased)
        {
            sf::Vector2i localPosition = sf::Mouse::getPosition(mWindow);
            std::cout << "MOUSE POS X | Y " << localPosition.x << " | " << localPosition.y << std::endl;
        }; //end of if



}// end of void

void Game::fillUpVectorCreatures(int cnt)
{
  //start positions
  float X = 0;
  float rangeX = 0; //first value is zero

    bool randomDirection = 0;
    char randomName = '0';
    int initialArrayNumber = 0;

  Creature ins_cr{10, '0'};
    SPC_Texture::ID_Enemys id;

  Anima x_anima{false, 1, 0};

  //in cycle
  if (cnt < this->maxSingleVecSize)
  {
     for (int i=0; i<cnt; i++)
     {
        //cnstr not_illif and cases only 1 or 0
        if (rand() % 2 == 0) { id = SPC_Texture::ID_Enemys::Volf; initialArrayNumber = 8; randomName = 'v'; } // volf
        else { id = SPC_Texture::ID_Enemys::Roster; initialArrayNumber = 10; randomName = 'r'; }// roster

        //making direction bool
        if ((rand() % 200) > 100) { randomDirection = true; X = (-100) - rangeX; }
        else { randomDirection = false; X = (world_S.x + 100.f) + rangeX; }

         ins_cr.reArrayReName(initialArrayNumber, randomName);
         ins_cr.makeByChar(randomDirection); //reinitialisation of Ffour Array again
         ins_cr.setTexture(YIU.getTextureEnemy(id));
            ins_cr.velocity = (rand() % 3) + 3;
               ins_cr.autoSetWalk(randomDirection);


         //initiate a positions
         ins_cr.setPosition(sf::Vector2f(X, world_S.y - YIU.getSz(id).y));
         rangeX = rangeX + ((rand() % 300));

         std::cout << " posX, posY " << ins_cr.getPosition().x << " | " << ins_cr.getPosition().y
                    << " name " << ins_cr.name << std::endl;
         creature_vec.emplace_back(ins_cr);

           cr_vec_anima.emplace_back(x_anima);
     }
  }

  std::cout << "exoid " << creature_vec.size() << std::endl;

      //making hungry trigger for SPIDER
      spider.animaHungry.registrica = (iternalCLK.getElapsedTime().asMilliseconds()/100) + spider.animaHungry.timer*2;
      spider.animaHungry.trigger = true;

}

//implementation generator of bullets in game
void Game::processEnemyBullets(uint32_t t) {}

//implementation of collidings
void Game::brainWishCollide(uint32_t t)
{
  //segment trigging point
  //in the first we collide an horsefly
  if (indian_stru.horsefly.visible)
  {
     //Horsefly colliding with spam CORRECTOR RIGHT POSITION
     if (indian_stru.indianLeft == spider.Left)
     {
         if (spider.Left)
         {
            if ((int)(indian_stru.horsefly.getPosition().x + 20.f) >=
                 (int)spider.sprite.getPosition().x)
                 {
                     spider.sprite.setColor(sf::Color::White);
                     spider.occurenceHungry = 0;
                       spider.animaHungry.registrica = t + spider.animaHungry.timer;
                         indian_stru.horsefly.visible = false;
                         indian_stru.horsefly.setPosition(indian_stru.h_pos[0]);
                     serviceSound[18] = true; //spider Eat
                     spider.animaHungry.trigger = false;// to service our sound
                         std::cout << "Flying time " << (int)t-indian_stru.timeFly << std::endl;
                         mySound[20].setLoop(false); //FlySoind unable
                 }
         }
         else
         {
            if ((int)(indian_stru.horsefly.getPosition().x) <=
                 (int)spider.sprite.getPosition().x + 80.f)
                 {
                     spider.sprite.setColor(sf::Color::White);
                     spider.occurenceHungry = 0;
                       spider.animaHungry.registrica = t + spider.animaHungry.timer;
                         indian_stru.horsefly.visible = false;
                         indian_stru.horsefly.setPosition(indian_stru.h_pos[1]);
                     serviceSound[18] = true; //spider Eat
                     spider.animaHungry.trigger = false;// to service our sound
                         std::cout << "Flying time " << (int)t-indian_stru.timeFly << std::endl;
                         mySound[20].setLoop(false); //FlySound unable
                 }
         }
     }

     //colliding with clear G_Column
     switch (indian_stru.indianLeft)
     {
         case true:
             /*std::cout << (int)indian_stru.horsefly.getPosition().x << " | "
                        << (int)g_column.r_shape.getPosition().x << " = "
                         << ((int)indian_stru.horsefly.getPosition().x  == (int)g_column.r_shape.getPosition().x ) << std::endl;*/
             if ((int)(indian_stru.horsefly.getPosition().x + 20.f) >=
                 (int)g_column.r_shape.getPosition().x )
                 {
                   indian_stru.horsefly.visible = false;
                   indian_stru.horsefly.setPosition(indian_stru.h_pos[0]);
                   g_column.affected.trigger = true;
                   score.s_Int--;
                   serviceSound[2] = true; //affected voice
                        mySound[20].setLoop(false); //FlySound unable
                 };
             break;
         case false:
             if ((int)indian_stru.horsefly.getPosition().x <=
                 (int) (g_column.r_shape.getPosition().x + g_column.r_shape.getSize().x) )
                 {
                   indian_stru.horsefly.visible = false;
                   indian_stru.horsefly.setPosition(indian_stru.h_pos[1]);
                   g_column.affected.trigger = true;
                   score.s_Int--;
                   serviceSound[2] = true; //affected voice
                        mySound[20].setLoop(false); //FlySound unable
                 };
             break;
         default: break;
     }
  }

  //bullet colliding
  if (bulletVec.size() > 0)
  {
   for (int i=0; i<bulletVec.size(); i++)
   {
           float happendX = bulletVec.at(i).getPosition().x + 4.f;
           float happendY = bulletVec.at(i).getPosition().y + 8.f;

           //indian collider
           if (indian_stru.indian.visible && indian_stru.indianLeft)
           {
              if ((int)happendY >= (int)indian_stru.indian.getPosition().y &&
                  (int)happendX <= (int)YIU.getSz(SPC_Texture::ID_Enemys::Indian).x &&
                  (int)happendX > - 10.f)
                  {

                        mPlayerDetachBullet(bulletVec.begin() + i);
                        indian_stru.lives--;
                        serviceSound[4] = true;
                        if (indian_stru.lives < 0) { indian_stru.indian.visible = false; score.s_Int+=3; serviceSound[5] = true; }
                  }

           }
           else if (indian_stru.indian.visible && !indian_stru.indianLeft)
           {
              if ((int)happendY >= (int)indian_stru.indian.getPosition().y &&
                  (int)happendX >= (int)(world_S.x - YIU.getSz(SPC_Texture::ID_Enemys::Indian).x) &&
                  (int)happendX < (int)world_S.x + 10)
                  {
                        mPlayerDetachBullet(bulletVec.begin() + i);
                        indian_stru.lives--;
                        serviceSound[4] = true;
                        if (indian_stru.lives < 0) { indian_stru.indian.visible = false; score.s_Int+=3; serviceSound[5] = true; }
                  }
           }
           else {};

           //bullet vector colliding and destroing creatures
           if (!creature_vec.empty())
           {
               for (int j=0; j<generalSize(); j++)
               {
                   SPC_Texture::ID_Enemys id;
                     int serviceVoice;
                     int serviceDie;
                       if (creature_vec.at(j).name == 'v') {id = SPC_Texture::ID_Enemys::Volf; serviceVoice = 14; serviceDie = 16;}
                       else {id == SPC_Texture::ID_Enemys::Roster; serviceVoice = 15; serviceDie = 17;}
                          float crWidth = YIU.getSz(id).x;
                          float crHeight = YIU.getSz(id).y;

                   switch (creature_vec.at(j).Mover)
                   {
                        case true:
                             if ((int)happendX >= (int) (creature_vec.at(j).getPosition().x) &&
                                 (int)happendX <= (int) (creature_vec.at(j).getPosition().x + (int)crWidth) &&
                                 (int)happendY >=  (int)creature_vec.at(j).getPosition().y)
                             {
                                  creature_vec.at(j).lives--;
                                  serviceSound[serviceVoice] = true; // damageCreature
                                    std::cout << " bullet report   j " << j << " lives " << creature_vec.at(j).lives << std::endl;
                                  mPlayerDetachBullet(bulletVec.begin() + i);
                             };
                             break;
                        case false:
                             if ((int)happendX >= (int) (creature_vec.at(j).getPosition().x) &&
                                 (int)happendX <= (int) (creature_vec.at(j).getPosition().x + (int)crWidth) &&
                                 (int)happendY >=  (int)creature_vec.at(j).getPosition().y)
                             {
                                  creature_vec.at(j).lives = creature_vec.at(j).lives - 4;
                                  serviceSound[serviceVoice] = true; // damageCreature
                                    std::cout << " bullet report   j " << j << " lives " << creature_vec.at(j).lives << std::endl;
                                  mPlayerDetachBullet(bulletVec.begin() + i);
                             };
                             break;
                   }
               }//end of for
           };


           //detaching in ground
           if ((int)happendY >= (int)world_S.y) mPlayerDetachBullet(bulletVec.begin() + i);

     }//end of for
   }//end of bulletColl if

   //player collide shape
   if (b_creatures.r_shape_bag_untrigged)
      {
          if ((int)(mPlayer.getPosition().x + mPlayer.getRadius()) >=
                   (int)(b_creatures.r_shape_bag.getPosition().x)  &&
               (int)(mPlayer.getPosition().x + mPlayer.getRadius()) <=
                   (int)(b_creatures.r_shape_bag.getPosition().x+20.f))
          {
              serviceSound[10] = true; //byteBoxSquare
              b_creatures.r_shape_bag_untrigged = false;
              b_creatures.r_shape_bag.setPosition(sf::Vector2f(-40,-20.f));
          }
      };

  if (b_creatures.r_shape_pipiter_untrigged)
      {
          if ((int)(mPlayer.getPosition().x + mPlayer.getRadius()) >=
                   (int)(b_creatures.r_shape_pipiter.getPosition().x) &&
               (int)(mPlayer.getPosition().x + mPlayer.getRadius()) <=
                   (int)(b_creatures.r_shape_pipiter.getPosition().x+20.f))
          {
              serviceSound[11] = true; //byteBoxSquare
              b_creatures.r_shape_pipiter_untrigged = false;
              b_creatures.r_shape_pipiter.setPosition(sf::Vector2f(world_S.x + 40.f, -20.f));
          }
      };

  //colliding creatures_vec with G_Column
  if(!creature_vec.empty())
  {
        for (int i=0; i<generalSize(); i++)
          {
              SPC_Texture::ID_Enemys id;
                  if (creature_vec.at(i).name == 'v') id = SPC_Texture::ID_Enemys::Volf;
                  else id = SPC_Texture::ID_Enemys::Roster;
                      float posX = 0;
                      if (creature_vec.at(i).getLeft()) posX = creature_vec.at(i).getPosition().x + YIU.getSz(id).x;
                      else posX = creature_vec.at(i).getPosition().x;
                          float leftBorder = g_column.r_shape.getPosition().x;
                          float rightBorder = g_column.r_shape.getPosition().x + g_column.r_shape.getSize().x;

              //g_column colliding case
              //std::deque<Creature>::iterator srch = creature_vec.begin() + i;
              switch (creature_vec.at(i).getLeft())
              {
                case true:
                    if (posX > leftBorder)
                        {

                                //std::deque<Anima>::iterator an = cr_vec_anima.begin() + i;
                                std::cout << "vec size report "  << i << " | GS " << generalSize() << std::endl;
                                /*Errase animas*/
                                //detachCreature(srch,an);
                                creature_vec.at(i).lives = -10; //storeCreatures();
                                            score.s_Int-=2;
                                            g_column.affected.trigger = true;
                                            serviceSound[2] = true; // g_column Affected
                        }
                    break;
                case false:
                    if (posX < rightBorder)
                        {
                                //std::deque<Anima>::iterator an = cr_vec_anima.begin() + i;
                                std::cout << "vec size report "  << i << " | GS " << generalSize() << std::endl;
                                /*Errase animas*/
                                //detachCreature(srch, an);
                                creature_vec.at(i).lives = -10; //storeCreatures();
                                            score.s_Int-=2;
                                            g_column.affected.trigger = true;
                                            serviceSound[2] = true; // g_column Affected
                        }
                    break;
              }

              // colliding with Volf and Boxbag
              if (id == SPC_Texture::ID_Enemys::Volf && b_creatures.boxbag_anima.trigger &&
                  !b_creatures.r_shape_bag_untrigged)
              {
                 float boxBorderL = b_creatures.boxbag.getPosition().x;
                 float boxBorderR = b_creatures.boxbag.getPosition().x + YIU.getSz(SPC_Texture::ID_Enemys::BoxBag).x;

                 //stop mooving change animation RETURNINIG in Rshape burning place
                 switch(creature_vec.at(i).getLeft())
                 {
                     case true:
                          if (posX > boxBorderL && creature_vec.at(i).Mover)
                          {
                             std::cout << "here ?" << std::endl;
                             creature_vec.at(i).Mover = false; b_creatures.colliderBagObj[i] = i;
                             creature_vec.at(i).autoSetFight(creature_vec.at(i).getLeft());
                             serviceSound[12] = true;
                          }
                          break;
                     case false:
                          if (posX < boxBorderR && creature_vec.at(i).Mover)
                          {
                             creature_vec.at(i).Mover = false; b_creatures.colliderBagObj[i] = i;
                             creature_vec.at(i).autoSetFight(creature_vec.at(i).getLeft());
                             serviceSound[12] = true;
                          }
                          break;
                 }
              };

              // colliding with Roster and Pipiter
              if (id == SPC_Texture::ID_Enemys::Roster && b_creatures.pipiter_anima.trigger &&
                  !b_creatures.r_shape_bag_untrigged)
              {
                 float pipiterBorderL = b_creatures.pipiter.getPosition().x;
                 float pipiterBorderR = b_creatures.pipiter.getPosition().x + YIU.getSz(SPC_Texture::ID_Enemys::Pipiter).x;

                 //stop mooving change animation RETURNINIG in Rshape burning place
                 switch(creature_vec.at(i).getLeft())
                 {
                     case true:
                          if (posX > pipiterBorderL && creature_vec.at(i).Mover)
                          {
                             creature_vec.at(i).Mover = false; b_creatures.colliderPipObj[i] = i;
                             creature_vec.at(i).autoSetFight(creature_vec.at(i).getLeft());
                             serviceSound[13] = true;
                          }
                          break;
                     case false:
                          if (posX < pipiterBorderR && creature_vec.at(i).Mover)
                          {
                             creature_vec.at(i).Mover = false; b_creatures.colliderPipObj[i] = i;
                             creature_vec.at(i).autoSetFight(creature_vec.at(i).getLeft());
                             serviceSound[13] = true;
                          }
                          break;
                 }
              };
          }//end of for
  };//end of if
}//end of block

//implementation of the update function of the game class (LOGIC BLOCK OF THE GAME)
void Game::update(sf::Time elapsedTime, uint32_t t)
{

if (idScene == ZERRO)
{
    if (joySUS.getStatus() == JoyPad::Status::READY && t%menu.animaGameCone.timer == 0)
    {
        if (t != menu.animaGameCone.registrica)
        {
            menu.animaGameCone.registrica = t;
            bool swaper;
            if (menu.animaGameCone.trigger) swaper = false;
            else swaper = true;
                menu.animaGameCone.trigger = swaper;
                menu.animaLabelCreatures.trigger = swaper;
                menu.animaSpiderPersonage.trigger = swaper;
                //menu.textVisible[0] = swaper;
                //menu.textVisible[4] = swaper;
                //menu.textVisible[5] = swaper;
        };
    };

    if (animaJoyWait.trigger && animaJoyWait.registrica == t)
    {
        joySUS.stepStatus();
        menu.text[1].setString(">>>> clock");
        menu.text[2].setString(">>>> start game");
        menu.text[3].setString(">>>> redifine GamePad");

        //remaking C_W controller info
        menu.text[4].setPosition(sf::Vector2f(229.f,694.f));
        menu.text[4].setString("Inputs: Space-Short, V M-turnSpider");
        menu.text[5].setPosition(sf::Vector2f(229.f,694.f + 50.f));
        menu.text[5].setString("        B-dropBag, N-dropDesk");

        animaJoyWait.trigger = false;
        animaJoyWait.registrica = 0;

                //writing to system
                joySUS.pushExprtByRecursion();
    };

    if (joySUS.getStatus() == JoyPad::Status::READY && menu.flagAlarm)
    {
      menu.textAlarm.setString("Alarm Time: " + menu.inserted);

          if (menu.inserted.size() == 4)
          {
            int x = std::stoi(menu.inserted);
              int timeHour = x/100;
              int timeMinut = x%100;

            if (timeHour > 23 || timeMinut > 59) { menu.inserted = ""; }
            else
                {
                    //exit from input mode first!!!
                    menu.flagAlarm = false;

                    menu.sysAlrm[0] = timeHour;
                    menu.sysAlrm[1] = timeMinut;

                        //file stream short
                        std::ofstream of_s("timeAlarm.t");
                        if (of_s.is_open())
                        {
                           of_s << menu.sysAlrm[0] << std::endl;
                           of_s << menu.sysAlrm[1] << std::endl;
                        }
                        of_s.close();

                    menu.textAlarm.setFillColor(sf::Color(205,205,186,255));
                    menu.textAlarm.setString("[S - refresh CloAlrm " + std::to_string(menu.sysAlrm[0]) + ":" + std::to_string(menu.sysAlrm[1]) + "]");
                }
          }
    };

}//end of zerro

else if (idScene == FIRST)
{
    sf::Vector2f movement (0.f, 0.f);

    if (mIsMovingLeft) {movement.x -= playerSpeed; };
    if (mIsMovingRight) {movement.x += playerSpeed; };

    mPlayer.move(movement * elapsedTime.asSeconds());

    //mPlayer queueBullet trigger
    if (animaBulletQueue.trigger && t%animaBulletQueue.timer == 0)
    {
        if (animaBulletQueue.registrica != t)
        {
        animaBulletQueue.registrica = t;

            if (bulletCountsInQueue < 8)
            {
                animaBulletQueue.registrica = t;
                mPlayerStartBullet();
                bulletCountsInQueue++;
            }
            else
            {
                bulletCountsInQueue = 0;
                animaBulletQueue.registrica = 0;
                animaBulletQueue.trigger = false;
            }
        }
    };


    //mechanics of indian reburn and shoot INDIAN BLOCK
    if (t%indian_stru.burn.timer == 0 && !indian_stru.indian.visible)
    {
        if (indian_stru.burn.registrica != t)
        {
            indian_stru.burn.registrica = t; //in case where first entry happends
            serviceSound[0] = true; //Indian Burn
                std::cout << " time: " << t << std::endl;
              int who = rand() % 200;
              //int who = 190;
            indian_stru.lives = indian_stru.livesCount; //reburn lives integer
                indian_stru.horsefly.visible = false; //horsfly inactivity

            if (who <= 100) //burn of indian right case
            {
              indian_stru.indianLeft = true;
               indian_stru.indian.autoSetFight(true);
               indian_stru.horsefly.setTextureRect(sf::IntRect(0,0,178,160) );
               indian_stru.indian.setPosition(indian_stru.i_pos[0]);
               indian_stru.horsefly.setPosition(indian_stru.h_pos[0]);
            }
            else
            {
              indian_stru.indianLeft = false;
               indian_stru.indian.autoSetFight(false);
               indian_stru.horsefly.setTextureRect(sf::IntRect(178,0,-178,160) );
               indian_stru.indian.setPosition(indian_stru.i_pos[1]);
               indian_stru.horsefly.setPosition(indian_stru.h_pos[1]);
            }
                indian_stru.indian.visible = true; //indian active

        }
    }

    if (indian_stru.indian.visible && (t%indian_stru.anima.timer == 0))
    {
        if (indian_stru.anima.registrica != t) //anima case
        {
            indian_stru.anima.registrica = t;
            indian_stru.indian.changeFrame();
        }

        if (t%indian_stru.shot.timer == 0) //short case
        {
            if (indian_stru.shot.registrica != t)
            {
                indian_stru.shot.registrica = t;
                serviceSound[1] = true;
                indian_stru.indian.setFrameByInt(0);
                    indian_stru.horsefly.visible = true;
                    indian_stru.timeFly = t; //temporary for register flying time
                    serviceSound[20] = true;
                    mySound[20].setLoop(true);
            }
        }
    }

    if (indian_stru.horsefly.visible == true) //horsefly moovinger
    {
        if (indian_stru.indianLeft) indian_stru.horsefly.move(+indian_stru.bulletSpeed, 0);
        else indian_stru.horsefly.move(-indian_stru.bulletSpeed, 0);
    }


     //SPIDER HUNGRY STATEMENT
    if (spider.animaHungry.registrica == t)
    {
        spider.animaHungry.registrica = t + spider.animaHungry.timer;

        if (spider.occurenceHungry > 0)
        {
            score.s_Int-=4;
            if (spider.animaHungry.trigger) serviceSound[19] = true;
        }
        else if (spider.occurenceHungry == 0)
        {
            spider.occurenceHungry++;
            spider.sprite.setColor(sf::Color(255,35,68,100));
            if (spider.animaHungry.trigger) serviceSound[19] = true;
                spider.animaHungry.trigger = true;
        }
        else {};
    }

    //BULLET MOVING BLOCK
    if (bulletVec.size() > 0)
    {
        for (int i=0; i<bulletVec.size(); i++) bulletVec.at(i).move(0.f, mPbspeed);
    }
            //std::cout << " bv size " << bulletVec.size() << std::endl;

    //Bullet_CREATURES mooving block
    if(b_creatures.boxbag_anima.trigger == true &&
       b_creatures.boxbag.getPosition().y <= (world_S.y - YIU.getSz(SPC_Texture::ID_Enemys::BoxBag).y - 10.f))
        {
            b_creatures.boxbag.move(0, b_creatures.velocity);
        }

    if(b_creatures.pipiter_anima.trigger == true &&
       b_creatures.pipiter.getPosition().y <= (world_S.y - YIU.getSz(SPC_Texture::ID_Enemys::Pipiter).y - 10.f))
        {
            b_creatures.pipiter.move(0, b_creatures.velocity);
        }

        //Bullet_CREATURES live time cycle t was initiate in collider
        if (t == b_creatures.boxbag_anima.registrica && b_creatures.boxbag_anima.trigger)
        {
               b_creatures.boxbag_anima.trigger = false;
               b_creatures.r_shape_bag_untrigged = true;

               //HERE... <<<===>>>  NEED COLLIDER ARRAY VALUES
               if (!creature_vec.empty())
               {
                    for (int i=0; i<creature_vec.size(); i++)
                    if (b_creatures.colliderBagObj[i] != -1)
                    {
                     creature_vec.at(i).autoSetWalk(creature_vec.at(i).getLeft());
                     creature_vec.at(i).Mover = true;
                     b_creatures.colliderBagObj[i] = -1;
                    }
               }
        }

        if (t == b_creatures.pipiter_anima.registrica && b_creatures.pipiter_anima.trigger)
        {
               b_creatures.pipiter_anima.trigger = false;
               b_creatures.r_shape_pipiter_untrigged = true;

               //HERE... <<<===>>>  NEED COLLIDER ARRAY VALUES
               if (!creature_vec.empty())
               {
                    for (int i=0; i<creature_vec.size(); i++)
                    if (b_creatures.colliderPipObj[i] != -1)
                    {
                     creature_vec.at(i).autoSetWalk(creature_vec.at(i).getLeft());
                     creature_vec.at(i).Mover = true;
                     b_creatures.colliderPipObj[i] = -1;
                    }
               }
        }

        //Bullet_CREATURES r_shape cycle
        if (b_creatures.r_shape_bag_untrigged && !b_creatures.boxbag_anima.trigger)
        {
            if (b_creatures.sh_places[0] != b_creatures.r_shape_bag.getPosition().x) //position change in collider
            {
                b_creatures.sh_places[0] = (float)(rand() % (int)(world_S.x-20.f));
                b_creatures.r_shape_bag.setPosition(b_creatures.sh_places[0], 0.f);
            }
        }

        if (b_creatures.r_shape_pipiter_untrigged && !b_creatures.pipiter_anima.trigger)
        {
            if (b_creatures.sh_places[1] != b_creatures.r_shape_pipiter.getPosition().x) //position change in collider
            {
                b_creatures.sh_places[1] = (float)(rand() % (int)(world_S.x-20.f));
                b_creatures.r_shape_pipiter.setPosition(b_creatures.sh_places[1], 0.f);
            }
        }

     //CREATURES_VEC UPDATE
     if (!creature_vec.empty())
     {
         for (int i=0; i<creature_vec.size(); i++)
         {
             //framing MOVER
             if(t%cr_vec_anima.at(i).timer == 0 && cr_vec_anima.at(i).trigger == true && creature_vec.at(i).Mover)
             {
                    //if()
                if (cr_vec_anima.at(i).registrica != t)
                {
                    cr_vec_anima.at(i).registrica = t;
                    creature_vec.at(i).changeFrame();
                    cr_vec_anima.at(i).trigger = false;
                }
             };

             //moving trigged by anima trigger MOVER
             if (!cr_vec_anima.at(i).trigger && creature_vec.at(i).Mover)
             {

                 switch (creature_vec.at(i).getLeft())
                 {
                    case true:
                        creature_vec.at(i).move(creature_vec.at(i).velocity,0.f);
                        break;
                    case false:
                        creature_vec.at(i).move(-creature_vec.at(i).velocity,0.f);
                        break;
                 }
               cr_vec_anima.at(i).trigger = true;
             };

             //UNMOVER animation ERROR HERE!!! <<<<<================>>>>>
             if (t%cr_vec_anima.at(i).timer == 0 && !creature_vec.at(i).Mover)
             {
                //std::cout << " mover " << std::endl;
                if (cr_vec_anima.at(i).registrica!= t)
                {
                    cr_vec_anima.at(i).registrica = t;
                    creature_vec.at(i).changeFrame();
                }
             }
         }//end of for



     }//end of if

     //UPDATING SCORE TEXT
     if (score.visible) score.s_Txt.setString("S: " + std::to_string(score.s_Int));

     //END OF GAME CASE***********************
     if(creature_vec.empty() && !segmentTriger) buildEndMenu();


}//end of first
else if(idScene == SECOND)
{
    //trigging blink end score items
    if (joySUS.getStatus() == JoyPad::Status::READY && t%menu.animaGameCone.timer == 0)
    {
        if (t != menu.animaGameCone.registrica)
        {
            menu.animaGameCone.registrica = t;
            bool swaper;
            if (menu.animaGameCone.trigger) swaper = false;
            else swaper = true;
                menu.animaGameCone.trigger = swaper;
                menu.textVisible[0] = swaper;
                menu.textVisible[4] = swaper;
                //menu.textVisible[5] = swaper;
        };
    };
}//end of second
else if (idScene == THIRD)
{

    if(animaSegment.registrica == t && !segmentTriger)
    {
       segmentTriger = true;
       animaSegment.registrica = t + animaSegment.timer;

       int expo = rand() % 1000;

               if (expo <= 200)
               {
                    curSegPos = seg.posF;  //.posS;     // general array sf::Vector2f PTR
                        currentSeg = seg.rectF; //rectS;  // general array rectangel entity
                        currentBL = seg.numberOne; //numberTwo; // general array bool PTR
                   digitSecure = 0; //numeration from zerro to three
               }
               else if (expo > 200 && expo <= 400)
               {
                   curSegPos = seg.posS;     // general array sf::Vector2f PTR
                        currentSeg = seg.rectS;  // general array rectangel entity
                        currentBL = seg.numberTwo; // general array bool PTR
                   digitSecure = 1; //numeration from zerro to three

               }
               else if (expo > 400 && expo <= 600)
               {
                   curSegPos = seg.posTH; //posS;     // general array sf::Vector2f PTR
                        currentSeg = seg.rectTH;  // general array rectangel entity
                        currentBL = seg.numberThree; // general array bool PTR
                   digitSecure = 2; //numeration from zerro to three
               }
               else
               {
                   curSegPos = seg.posFR; //.posTH; //posS;     // general array sf::Vector2f PTR
                        currentSeg = seg.rectFR; //.rectTH;  // general array rectangel entity
                        currentBL = seg.numberFour; //.numberThree // general array bool PTR
                   digitSecure = 3; //numeration from zerro to three
               }

               //std::cout << " segment triger " << multiTriger << " digitSecure " << digitSecure << std::endl;
    };

    //system alarm sound controll
    time_t taim = time(nullptr);
    if ((int)getSysHour() == menu.sysAlrm[0] && (int)getSysMin() == menu.sysAlrm[1] && localtime(&taim)->tm_sec == 0)
       {
          menu.sysAlarmCounter = 0;
          YIU.getAlarm().setLoop(false);
          YIU.getAlarm().setVolume(100.f);
       };
    if (menu.sysAlarmCounter < 20  && YIU.getAlarm().getStatus() == sf::SoundStream::Stopped)
       {
          menu.sysAlarmCounter = menu.sysAlarmCounter + 1;
          //std::cout << menu.sysAlarmCounter << " status " << YIU.getAlarm().getStatus() << " status stop " << sf::SoundStream::Stopped << std::endl;
          YIU.getAlarm().stop();
          YIU.getAlarm().play();
       };


}//end of third
else {};

}//end of block

//TRIGING SEGMENT LOGIC BLOCK
void Game::updateSegMech(sf::Time elapsedTime, uint32_t t)
{
    /*0-falling digit, 1-goSecure, 2-goToHeap, 3-returnHeap(segUp), 4-goWeldering, 5-goShowFire, 6-returnWeldering, 7-goReturn*/

    //FALLING DIGIT 0
    if (segmentTriger && multiTriger == 0)
    {
       int digExp = seg.leaderTop[memDig[digitSecure]]; //puts in array of numbersleads value of digit four

       for(int sG=0; sG<28; sG++)
       {
         if (currentSeg[sG].getPosition().y != (world_S.y - currentSeg[sG].getSize().y) && currentBL[sG])
         {
           currentSeg[sG].move(0, +1.f);
         }
         else if (sG == digExp && currentSeg[sG].getPosition().y == (world_S.y - currentSeg[sG].getSize().y) && currentBL[sG])
         {
           seg.segUp = false; // it is first time up triging moment
            multiTriger++;
             //std::cout << " Falling digit closed and " << multiTriger << std::endl;
         }
         else{};
       };//end of for
    };//end of if

    //GO SECURE 1
    if (multiTriger == 1)
    {
        float goSX = fWelder.wldrGoPos[digitSecure].x;
        float goSY = fWelder.wldrGoPos[digitSecure].y;

        if((int)fWelder.sprite.getPosition().x != (int)goSX ||
              (int)fWelder.sprite.getPosition().y != (int)goSY)
        {
            fWelder.moveToPoint(goSX, goSY);
        }

                if((int)fWelder.sprite.getPosition().x == (int)goSX &&
                    (int)fWelder.sprite.getPosition().y == (int)goSY) fWelder.Syncro = true;

        if((int)sWelder.sprite.getPosition().x != (int)goSX + 115.f ||
              (int)sWelder.sprite.getPosition().y != (int)goSY)
        {
            sWelder.moveToPoint(goSX + 115.f, goSY);
        }
                if ((int)sWelder.sprite.getPosition().x == (int)goSX + 115.f &&
                    (int)sWelder.sprite.getPosition().y == (int)goSY) sWelder.Syncro = true;


        //search bouth
        if (fWelder.Syncro && sWelder.Syncro)
        {
             fWelder.Syncro = false; sWelder.Syncro = false;
             fWelder.autoSetSpeed(); sWelder.autoSetSpeed();
             fWelder.setWldrFace();

                sWelder.setWldrSideL();
                sWelder.autoSetBlameSideL();

             multiTriger++;
             //std::cout << " Bouth welders in places and  " << multiTriger <<  std::endl;
        };//end of if
    };// end of if (moovement root)

    //GO TO HEAP (fWelder) 2
    if (multiTriger == 2)
    {
        fWelder.setWldrFace();
        fWelder.blameVisible = false;
        fWelder.autoSetSpeed();


        if ((int)fWelder.sprite.getPosition().y != (int)(world_S.y - fWelder.wldrSize.y -  40.f))
        {
            fWelder.moveToPoint( fWelder.sprite.getPosition().x, (world_S.y - fWelder.wldrSize.y -  40.f) );
        }//end of if
        else
        {
            multiTriger++;
            seg.segUp = true;
            //std::cout << "Welder in Heap " << multiTriger << std::endl;
        }//end of else
    };//end of if

    if (segIterVar > 27) segIterVar = 0;   //SEGMENT ITERATOR!!!
    //FROM HERE!!!

    //RETURN FROM HEAP (segUp)
    if (multiTriger == 3 && seg.segUp && currentBL[segIterVar] == true)
    {
       /*std::cout << " MULT_TRIG " << multiTriger
                  << "are is true condition here" << (multiTriger == 3 && seg.segUp && currentBL[segIterVar] == true)
                   << std::endl;*/

       //inpression is the last digit cube number
       int digInpr = seg.leaderBottom[memDig[digitSecure]];

       //std::cout << " segIter " << segIterVar << " int digInpr " << digInpr << std::endl;

       if ((int)currentSeg[segIterVar].getPosition().y != (int)curSegPos[segIterVar].y)
       {
         currentSeg[segIterVar].move(0, -1.f);
         //std::cout << "exoid " << currentSeg[segIterVar].getPosition().x << " | " << currentSeg[segIterVar].getPosition().y << std::endl;
         float posX = currentSeg[segIterVar].getPosition().x - 25.f;
         float posY = currentSeg[segIterVar].getPosition().y + 40.f;
         fWelder.sprite.setPosition(sf::Vector2f(posX, posY));
         fWelder.setWldrBack();
         fWelder.autoSetBlameBack();
       }// end of if
       else
       {
        // next point of movements
        seg.segUp = false;
        multiTriger = 4;  //sWelder.GoWeldring = true; // <=>  4
        ++segIterVar; // ITERATOR HERE!!!
       };//end of else

       if ((int)currentSeg[digInpr].getPosition().y == (int)curSegPos[digInpr].y) //solve the problem last weldering
       {
        //std::cout << "exoid from seven" << std::endl;
        seg.segUp = false;  fishHook = true;
        segIterVar = 0;
        multiTriger = 7; //fWelder.GoReturn = true; // <=> 7
            fWelder.Syncro = false; sWelder.Syncro = false;
            fWelder.setWldrFace();
            sWelder.setWldrFace();
       };//end of if
     }//end of if
    else if (seg.segUp && currentBL[segIterVar] == false)
    {
          if (segIterVar < 28) segIterVar++;
    }//end of else
    else {};

    //GO WELDERING 4
    if (multiTriger == 4)//sWelder.GoWeldring == true)
    {
        float goesX = fWelder.sprite.getPosition().x + 40.f;
        float goesY = fWelder.sprite.getPosition().y - 45.f;

      if ((int)sWelder.sprite.getPosition().x != (int)goesX || (int)sWelder.sprite.getPosition().y != (int)goesY)
      {
        sWelder.autoSetBlameSideL();
        sWelder.moveToPoint(goesX,goesY);
      }
      else
      {
        sWelder.welderShowFire = t + 50;
        sWelder.autoSetSpeed();
        multiTriger++;  // sWelder.GoShowFire = true; // goes process speceffects  <=> 5
      }
    };//end of if

    //RETUURN WELDERING <=> 6
    if (multiTriger == 6)  //sWelder.GoFromWeldering == true)
    {
      float goesX = sWelder.wldrGoPos[digitSecure].x + 100.f;
      float goesY = sWelder.wldrGoPos[digitSecure].y;

      if ((int)sWelder.sprite.getPosition().x != (int)goesX || (int)sWelder.sprite.getPosition().y != (int)goesY)
      {
        sWelder.autoSetBlameSideR();
        sWelder.moveToPoint(goesX,goesY);
      }
      else
      {
         sWelder.setWldrSideL();
         sWelder.autoSetBlameSideL();
         multiTriger = 2;  // <=> fWelder.GoToHeap = true;
            sWelder.autoSetSpeed();
      }

    };//end of if

    //GO RETURN <=> 7
    if (multiTriger == 7)  //fWelder.GoReturn == true)
    {
        if  ((int)fWelder.sprite.getPosition().x != (int)w_startPos[0].x ||
               (int)fWelder.sprite.getPosition().y != (int)w_startPos[0].y )
        {
            fWelder.moveToPoint(w_startPos[0].x, w_startPos[0].y);
        }
                if  ((int)fWelder.sprite.getPosition().x == (int)w_startPos[0].x &&
                       (int)fWelder.sprite.getPosition().y == (int)w_startPos[0].y ) fWelder.Syncro = true;

        if  ((int)sWelder.sprite.getPosition().x != (int)w_startPos[1].x ||
              (int)sWelder.sprite.getPosition().y != (int)w_startPos[1].y )
        {
            sWelder.moveToPoint(w_startPos[1].x, w_startPos[1].y);
        }
                if  ((int)sWelder.sprite.getPosition().x == (int)w_startPos[1].x &&
                       (int)sWelder.sprite.getPosition().y == (int)w_startPos[1].y ) sWelder.Syncro = true;

        if (fWelder.Syncro && sWelder.Syncro)
        {
           fWelder.Syncro = false; sWelder.Syncro = false;
           fWelder.autoSetSpeed(); sWelder.autoSetSpeed();

           multiTriger = 0;//fWelder.GoReturn = false; <=> 0
           segmentTriger = false; // making triger in a Returned action
           seg.segUp = false;
        };//end of if
    }//end of if

}//end of void

//spec effects like fliking void
void Game::processSpecEfects(uint32_t t)
{
  //GO SHOW FIRE <=> 5
  if (multiTriger == 5) //sWelder.GoShowFire == true)
  {
     if (sWelder.welderShowFire > t)
     {
        if (t%9 < 4) sWelder.setWldrSideLFire();
        else sWelder.setWldrSideL();
     }//end of if
     else
     {
        sWelder.setWldrSideL();
        //sWelder.GoShowFire = false;
        sWelder.setWldrSideR();
         multiTriger++; //sWelder.GoFromWeldering = true; // <=> 6

     };//end of else
  };


  //GO CHANGE COLOR OF g_column
  if (g_column.affected.trigger == true)
  {
    g_column.r_shape.setFillColor(sf::Color(255,102,181,255)); //239 28 109 255
    mPlayer.setFillColor(sf::Color(255,102,181,255));
  }
  else
  {
    g_column.r_shape.setFillColor(sf::Color(93, 147, 182, 255));
    mPlayer.setFillColor(sf::Color(93, 147, 182, 255));
  };

    if (g_column.affected.trigger == true && t%g_column.affected.timer == 0) //mech
    {
        if (g_column.affected.registrica != t)
        {
            g_column.affected.registrica = t;
            g_column.affected.trigger = false;
        }
    }


}//end of void

//implementation of the render function of the game class (DRAW OBJECTS)
void Game::render()
{
        mWindow.clear();
        mWindow.draw(backG);


    if (idScene == S_SCENE::ZERRO)
    {
          if (menu.animaCover.trigger) mWindow.draw(menu.cover);
          if (menu.animaGameCone.trigger) mWindow.draw(menu.gameCone);
          if (menu.animaLabelCreatures.trigger) mWindow.draw(menu.labelCreatures);
          if (menu.animaSpiderPersonage.trigger) mWindow.draw(menu.spiderPersonage);

          for(int i=0; i<6; i++) if(menu.textVisible[i]) mWindow.draw(menu.text[i]);

            if (menu.setTextAlarmVisible) mWindow.draw(menu.textAlarm);
    }

    else if (idScene == S_SCENE::FIRST)
    {

            if(b_creatures.r_shape_bag_untrigged) mWindow.draw(b_creatures.r_shape_bag);
            if(b_creatures.r_shape_pipiter_untrigged) mWindow.draw(b_creatures.r_shape_pipiter);

            if (g_column.visible) mWindow.draw(g_column.r_shape); //Draw Border G_Column
            if (spider.visible) mWindow.draw(spider.sprite); //Draw Spider
            if (score.visible) mWindow.draw(score.s_Txt); //score show on front of G_Column

            //draw segment
            for (int rS=0; rS<28; rS++)
            {
              if (seg.numberOne[rS]) mWindow.draw(seg.rectF[rS]);
              if (seg.numberTwo[rS]) mWindow.draw(seg.rectS[rS]);
              if (seg.numberThree[rS]) mWindow.draw(seg.rectTH[rS]);
              if (seg.numberFour[rS]) mWindow.draw(seg.rectFR[rS]);
            };//end of for


            //draw creatures
            if (indian_stru.indian.visible) mWindow.draw(indian_stru.indian);
            if (indian_stru.horsefly.visible) mWindow.draw(indian_stru.horsefly);
            if (creature_vec.size()>0) for (int i=0; i<creature_vec.size(); i++) mWindow.draw(creature_vec.at(i));


                 //draw bullet sections

                 //mWindow.draw(temporary);
                 if (debugCreature.visible) mWindow.draw(debugCreature);

            //draw b_creatures
            if(b_creatures.boxbag_anima.trigger) mWindow.draw(b_creatures.boxbag);
            if(b_creatures.pipiter_anima.trigger) mWindow.draw(b_creatures.pipiter);

            mWindow.draw(mPlayer);
            if (fWelder.visible) mWindow.draw(fWelder.sprite);
            if (fWelder.blameVisible)
                {
                 mWindow.draw(fWelder.blame);
                 mWindow.draw(fWelder.blameTwo);
                };

            if (sWelder.visible) mWindow.draw(sWelder.sprite);
            if (sWelder.blameVisible)
                {
                 mWindow.draw(sWelder.blame);
                 mWindow.draw(sWelder.blameTwo);
                };

            mWindow.draw(dateText);

            if(bulletVec.size() > 0) for (int i=0; i<bulletVec.size(); i++) mWindow.draw(bulletVec.at(i));
    }
    else if (idScene == S_SCENE::SECOND)
    {
       if (menu.animaCover.trigger) mWindow.draw(menu.cover);
       if (menu.animaGameCone.trigger) { mWindow.draw(menu.finGC); mWindow.draw(menu.gameCone); }
       if (menu.textVisible[0]) mWindow.draw(menu.text[0]);
       if (menu.textVisible[4]) mWindow.draw(menu.text[4]);
    }
    else if (idScene == S_SCENE::THIRD)
    {
        //CLOCK SCENE
        //DRAW SEGMENT
        for (int rS=0; rS<28; rS++)
        {
          if (seg.numberOne[rS]) mWindow.draw(seg.rectF[rS]);
          if (seg.numberTwo[rS]) mWindow.draw(seg.rectS[rS]);
          if (seg.numberThree[rS]) mWindow.draw(seg.rectTH[rS]);
          if (seg.numberFour[rS]) mWindow.draw(seg.rectFR[rS]);
        };//end of for


        //DRAW WELDERS
        if (fWelder.visible) mWindow.draw(fWelder.sprite);
            if (fWelder.blameVisible)
                {
                 mWindow.draw(fWelder.blame);
                 mWindow.draw(fWelder.blameTwo);
                };

            if (sWelder.visible) mWindow.draw(sWelder.sprite);
            if (sWelder.blameVisible)
                {
                 mWindow.draw(sWelder.blame);
                 mWindow.draw(sWelder.blameTwo);
                };

        //DRAW TEXT
        mWindow.draw(dateText);

        mWindow.draw(menu.text[4]);
        mWindow.draw(menu.text[5]);

    }
    else if (idScene == S_SCENE::LAST)
    {

    }
    else;

        mWindow.display();
}//end of void

//****************SYS*******************
//other game class functions under there
std::string Game::getSysTime()
{
  time_t seconds = time(nullptr);
  char timeBuf[45];
  for (int ch=0; ch<45; ch++)
      {
      if (ch == 44) {  timeBuf[ch] = '\0';  }
      else {  timeBuf[ch] = NULL;  };
      }
  char* timeFormat  =  "%A, %d %B, %d.%m.%Y %H:%M:%S";

  strftime (timeBuf, 45, timeFormat, localtime(&seconds));
  return std::string(timeBuf, sizeof(timeBuf));
}

unsigned int Game::getSysHour()
{
  time_t seconds = time(nullptr);
  return localtime(&seconds)->tm_hour;
}

unsigned int Game::getSysMin()
{
  time_t seconds = time(nullptr);
  return localtime(&seconds)->tm_min;
}

void Game::autoSetTimeText()
{
  if (!font.loadFromFile("consola.ttf")) {  std::cout << " FONT ERR: Cant find font file! " << std::endl; }
  else
  {
  font.loadFromFile("consola.ttf");
  dateText.setFont(font);
  dateText.setCharacterSize(40);
  dateText.setColor(sf::Color::White);
  dateText.setPosition(sf::Vector2f(world_S.x/7, 50.f));
        autoSetScoreText();
  };
}//end of void

void Game::autoSetScoreText()
{
   //load Score Text
   score.s_Txt.setFont(font);
   score.s_Txt.setCharacterSize(40);
   score.s_Txt.setColor(sf::Color::Red);
   score.s_Txt.setRotation(270.f);
   score.s_Txt.setPosition(sf::Vector2f(world_S.x/2 - 30.f, world_S.y - 20.f));
      score.s_Txt.setString("S: " + std::to_string(score.s_Int));
}

void Game::autoSetBackG()
{
  backG.setPosition(0.f, 0.f);
  backG.setSize(sf::Vector2f(world_S.x, world_S.y));
  backG.setFillColor(sf::Color::Black);
  //backG.setFillColor(sf::Color(210,180,140, 255));
}//end of void

void Game::mPlayerStartBullet()
{
    float sX = mPlayer.getPosition().x + ((mPlayer.getRadius()/2) + 20);
    float sY = mPlayer.getPosition().y + mPlayer.getRadius()*2;

    sf::CircleShape c_s(8.f,12);
    c_s.setFillColor(sf::Color(255, 255, 255, 255));
    c_s.setOutlineColor(sf::Color(193, 193, 193, 255));
    c_s.setOutlineThickness(1.f);
    c_s.setPosition(sf::Vector2f(sX, sY));
    serviceSound[3] = true;

    bulletVec.push_back(c_s);

}

void Game::mPlayerDetachBullet(std::vector<sf::CircleShape>::iterator dell)
{
  if(dell != bulletVec.end()) bulletVec.erase(dell);
  //std::cout << "bullet deque " << bulletVec.size() << std::endl;
}

bool Game::detachCreature(std::deque<Creature>::iterator& cr, std::deque<Anima>::iterator& an)
{

    //std::cout << " exoid 3.9 " << " " << "size creature_Vec " << creature_vec.size() << std::endl;
    //std::cout << " is end | is begin " << (cr == creature_vec.end()) << " | " << (cr == creature_vec.begin()) << " ";

    //IN DEQUE
    if (!creature_vec.empty()) creature_vec.erase(cr);
    if (!cr_vec_anima.empty()) cr_vec_anima.erase(an);

        //std::cout << " detacher(rep) creature | anima " << creature_vec.size() << " | " << cr_vec_anima.size() << std::endl;

    if (creature_vec.empty() && cr_vec_anima.empty()) return false;
    return true;
}

void Game::storeCreatures()
{
    //well, it's necessary to cook soup from something and sew fur coats (it is a joke, the creatures go teleporting)
    //std::cout << "exoid 1";
    for (int i=0; i<generalSize(); i++)
    {
       if(creature_vec.at(i).lives < 0)
       {
         score.s_Int++;
         if (creature_vec.at(i).name = 'v' && creature_vec.at(i).lives!=-10) serviceSound[16] = true;
         else if (creature_vec.at(i).name = 'r' && creature_vec.at(i).lives!=-10)  serviceSound[17] = true;
         else {};

          std::deque<Creature>::iterator cr = creature_vec.begin()+i;
          std::deque<Anima>::iterator an =  cr_vec_anima.begin()+i;

           //std::cout << " exoid 3 " << " ";
           if(detachCreature(cr,an)) std::cout << i << " lives " << cr->lives << "Done! Nexx t!" << std::endl;
       }
    }
}

void Game::fillUpMySounds()
{

    mySound[0].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::IndianBorn));
    mySound[1].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::IndianShort));
    mySound[2].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::AffectedG_Column));
    mySound[3].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::StartBullet));
    mySound[4].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::ItemDamage));
    mySound[5].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::IndianDie));
    mySound[6].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::boxBagBorn));
    //mySound[7]
    mySound[8].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::pipiterBorn));
    //mySound[9]
    mySound[10].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::byteBoxSquare));
    mySound[11].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::bytePipiterSquare));
    mySound[12].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::fightWolf));
    mySound[13].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::songRoster));
    //mySound[14]
    //mySound[15]
    mySound[16].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::itemDeath));
    //mySound[17]
    mySound[18].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::spiderEat));
    mySound[19].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::spiderHungry));
    mySound[20].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::flyHorseFly));
    mySound[21].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::Enter));
    mySound[23].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::Select));
    mySound[24].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::Weldering1));
    mySound[25].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::Weldering2));
    mySound[26].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::Weldering3));
    mySound[27].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::GoSecure));
    mySound[28].setBuffer(YIU.getSBuff(SPC_SoundBuf::ID_Sound::ReturnSecure));
    //mySound[29]
    //7 9 14 15 17 29


    for (int s=0; s<29; s++)
                        {
                            serviceSound[s] = false;
                            mySound[s].setVolume(90);
                        }
    mySound[3].setVolume(70);
    mySound[4].setVolume(60);
    mySound[2].setVolume(100);

    // IMPORTANT MAKE SOUND WELDERING ACTIVE!!!


}

//player sound function
void Game::playSound()
{

    for (int s=0; s<30; s++)
    {
        if (serviceSound[s])
        {

          if (s==14 || s==15) mySound[4].play();
          else if (s==16 || s==17) mySound[16].play();
          else if (s==7 || s==9 || s==29) continue;
          else mySound[s].play();

             serviceSound[s] = false;
             //std::cout << s << std::endl;
        }
    }

        if (soundWelderCounter == 1 && multiTriger == 1)
        {
            soundWelderCounter = 5;
            serviceSound[27] = true; //goSecure
        }
        else if (soundWelderCounter == 5 && multiTriger == 5)
        {

            soundWelderCounter = 7;
                //goWeldering soundEnabling
                int rndWldr = rand() % 300;
                if (rndWldr <= 100) serviceSound[24] = true;
                else if (rndWldr > 100 && rndWldr < 200) serviceSound[25] = true;
                else serviceSound[26] = true;
        }
        else if (soundWelderCounter == 7 && multiTriger == 2)
        {
            soundWelderCounter = 5; //goHeapcase
        }
        else if (fishHook)
        {
            soundWelderCounter = 1;
            serviceSound[28] = true; //returnSecure
            fishHook = false;
        }
        else {};
}

//making menus of Game
void Game::buildStartMenu() //at the end cpp
{
    idScene = S_SCENE::ZERRO;
    score.s_Int = 0;

    //sprites ini
    menu.cover.setTexture(YIU.getCover(SPC_Texture::ID_Covers::FrontCover));
    menu.cover.setPosition(sf::Vector2f(0.f, 0.f));
    menu.animaCover.trigger = true;

    menu.gameCone.setTexture(YIU.getCover(SPC_Texture::ID_Covers::GameCone));
    menu.gameCone.setPosition(sf::Vector2f(16.f, 12.f));
    menu.animaGameCone.trigger = true;

    menu.labelCreatures.setTexture(YIU.getCover(SPC_Texture::ID_Covers::Personage));
    menu.labelCreatures.setPosition(sf::Vector2f(12.f, 626.f));
    menu.labelCreatures.setColor(sf::Color(255,255,255,200));
    menu.animaLabelCreatures.trigger = true;

    menu.spiderPersonage.setTexture(YIU.getCover(SPC_Texture::ID_Covers::SpiderPersonage));
    menu.spiderPersonage.setScale(0.35,0.35);
    menu.spiderPersonage.setColor(sf::Color(255,248,153,210));
    menu.spiderPersonage.setPosition(sf::Vector2f(1099.f, 699.f));
    menu.animaSpiderPersonage.trigger = true;

    //texture ini
    float posX = world_S.x - (world_S.x/3 + 60.f);
    float posY = 200;
    float rangeY = 50.f;

    for (int t=0; t<6; t++)
        {
            menu.text[t].setFont(YIU.getFont(SPC_Fonts::ID_Fonts::BigSquareDots));
            menu.text[t].setFillColor(sf::Color::White);
            menu.text[t].setCharacterSize(36);
            menu.text[t].setString("<<<");
            menu.text[t].setPosition (posX, posY + rangeY*t);
            menu.textVisible[t] = true;
        }

   //making C_W cover label
   menu.text[0].setCharacterSize(50);
   menu.text[0].setString("Clockers Workers");
   menu.text[0].setPosition(sf::Vector2f(685, 142));

   //making C_W controller info
   menu.text[4].setPosition(sf::Vector2f(229.f,694.f));
   menu.text[4].setString("Inputs: Space-Short, V M-turnSpider");
   menu.text[5].setPosition(sf::Vector2f(229.f,694.f + rangeY));
   menu.text[5].setString("        B-dropBag, N-dropDesk.");

   //setMenuStrings
   menu.text[1].setString(">>>> clock");
   menu.text[2].setString(">>>> start game");
   menu.text[3].setString(">>>> redifine GamePad");

      menu.threeTrigger = 1;
      menu.text[1].setColor(sf::Color(255,76,91,255));

          std::ifstream in_s("timeAlarm.t");
          if(in_s.is_open())
          {
             in_s >> menu.sysAlrm[0] >> menu.sysAlrm[1];
             in_s.close();
          }
          else
          {
              in_s.close();
                  menu.sysAlrm[0] = 6;
                  menu.sysAlrm[1] = 0;
              std::ofstream of_s("timeAlarm.t");
              of_s << menu.sysAlrm[0] << std::endl;
              of_s << menu.sysAlrm[1] << std::endl;
              of_s.close();
          };

      menu.setTextAlarmVisible = true;
      menu.textAlarm.setFont(YIU.getFont(SPC_Fonts::ID_Fonts::BigSquareDots));
      menu.textAlarm.setFillColor(sf::Color(205,205,186,255));
      menu.textAlarm.setPosition(sf::Vector2f(754,434)); //744,424
      menu.textAlarm.setCharacterSize(28);
      menu.textAlarm.setString("[S - refresh CloAlrm " + std::to_string(menu.sysAlrm[0]) + ":" + std::to_string(menu.sysAlrm[1]) + "]");

     YIU.getMusic().stop();
     YIU.getMusic().setLoop(true);
     YIU.getMusic().play();
}

void Game::buildEndMenu() //at the end cpp
{
  //end music
  YIU.getMusic().stop();
  YIU.getMusic().play();

  idScene = S_SCENE::SECOND;
  menu.cover.setTexture(YIU.getCover(SPC_Texture::ID_Covers::EndCover));

  menu.text[0].setString("Final Score: " + std::to_string(score.s_Int));
  menu.text[0].setPosition(sf::Vector2f(400, 300));

  menu.animaGameCone.trigger = true;
  menu.finGC.setFillColor(sf::Color(232,238,255,200));
  menu.finGC.setSize(sf::Vector2f(243,33)); //266 51
  menu.finGC.setPosition(sf::Vector2f(23,18));
  menu.finGC.setOutlineColor(sf::Color(150,157,173,255));
  menu.finGC.setOutlineThickness(2);

  menu.text[4].setString("Press Enter or Start to continue...");

}

void Game::buildClock()
{
    YIU.getMusic().stop();

    //switch scene
    idScene = S_SCENE::THIRD;

    //make watch alarm text
    menu.text[4].setString("[CloAlrm " + std::to_string(menu.sysAlrm[0]) + ":" + std::to_string(menu.sysAlrm[1]) + "]");
    menu.text[5].setString("Make Alarm Working, turn of WinScreenSaver!");


        //setting numbers
        seg.setBoolNumber(seg.numberOne, 6);
        seg.setBoolNumber(seg.numberTwo, 5);
        seg.setBoolNumber(seg.numberThree, 3);
        seg.setBoolNumber(seg.numberFour, 7);
        memDig[0] = 6;
        memDig[1] = 5;
        memDig[2] = 3;
        memDig[3] = 7;

   //initiating trigging timing
   uint32_t t = iternalCLK.getElapsedTime().asMilliseconds()/100;
   animaSegment.registrica = animaSegment.timer/20 + t;
}

//redifinekeys
void Game::checkUpJoy(sf::Event& event)
{
    sf::Joystick::update();

    switch(joySUS.getStatus())
    {

    case JoyPad::Status::SEEK_PORT:
            //std::cout << " event " << std::endl;
            /*
              event.type == sf::Event::JoystickButtonPressed
                event.joystickButton.button    button manage
              event.type == sf::Event::JoystickMoved
                float x = sf::Joystick::getAxisPosition(event.joystickButton.joystickId, sf::Joystick::X)
                float y = sf::Joystick::getAxisPosition(event.joystickButton.joystickId, sf::Joystick::Y)
            */

            if (event.type ==  sf::Event::JoystickButtonPressed || event.type == sf::Event::JoystickMoved)
            {
                //std::cout << "is pressed " << event.type << std::endl;
                if (event.joystickButton.joystickId <= 57)
                {
                    joySUS.wrightToData(JoyPad::Status::SEEK_PORT, event.joystickButton.joystickId);
                      menu.text[5].setString("Port number " + std::to_string(joySUS.getButtonData(0)));
                    joySUS.stepStatus();
                      menu.text[4].setString(joySUS.getCheckReport(1));
                }
            }
            break;

    case JoyPad::Status::CHECK_X:

            if (event.type == sf::Event::JoystickMoved && event.joystickButton.joystickId == joySUS.getButtonData(0))
            {
                if (sf::Joystick::getAxisPosition(event.joystickButton.joystickId, sf::Joystick::X) > 40 ||
                     sf::Joystick::getAxisPosition(event.joystickButton.joystickId, sf::Joystick::X) < -40)
                       {
                       //std::cout << " Y axis moving " << std::endl;
                       joySUS.wrightToData(JoyPad::Status::CHECK_X, 100.f); //IMPORTANT
                         menu.text[5].setString("Fixed X axis " + std::to_string((int)joySUS.getAxisData(6).fmax) + " " + std::to_string((int)joySUS.getAxisData(6).fmin));
                       joySUS.stepStatus();
                         menu.text[4].setString(joySUS.getCheckReport(2));
                       }
            }
            //joySUS.setStatus(JoyPad::Status::CHECK_Y);*/
            break;

    case JoyPad::Status::CHECK_Y:

            if (event.type == sf::Event::JoystickMoved && event.joystickButton.joystickId == joySUS.getButtonData(0))
            {
                if (sf::Joystick::getAxisPosition(event.joystickButton.joystickId, sf::Joystick::Y) > 40 ||
                     sf::Joystick::getAxisPosition(event.joystickButton.joystickId, sf::Joystick::Y) < -40)
                       {
                       //std::cout << " X axis moving " << std::endl;
                       joySUS.wrightToData(JoyPad::Status::CHECK_Y, 90.f); //IMPORTANT
                         menu.text[5].setString("Fixed Y axis " + std::to_string((int)joySUS.getAxisData(7).fmax) + " " + std::to_string((int)joySUS.getAxisData(7).fmin));
                       joySUS.stepStatus();
                         menu.text[4].setString(joySUS.getCheckReport(3));
                       }
            }
            //joySUS.setStatus(JoyPad::Status::);
            break;

    case JoyPad::Status::JOY_START:

            if (event.type ==  sf::Event::JoystickButtonPressed && event.joystickButton.joystickId == joySUS.getButtonData(0))
            {
                //std::cout << " button fixed " << std::endl;
                joySUS.wrightToData(JoyPad::Status::JOY_START, event.joystickButton.button);
                   menu.text[5].setString("Fixed Start button " + std::to_string(joySUS.getButtonData(1)));
                joySUS.stepStatus();
                   menu.text[4].setString(joySUS.getCheckReport(4));
            }
            break;

    case JoyPad::Status::JOY_SHOT:
            if (event.type ==  sf::Event::JoystickButtonPressed && event.joystickButton.joystickId == joySUS.getButtonData(0))
            {
               //std::cout << " button fixed " << std::endl;
               joySUS.wrightToData(JoyPad::Status::JOY_SHOT, event.joystickButton.button);
                   menu.text[5].setString("Fixed Shot button " + std::to_string(joySUS.getButtonData(2)));
               joySUS.stepStatus();
                   menu.text[4].setString(joySUS.getCheckReport(5));
            }
            break;

    case JoyPad::Status::JOY_DROP_BAG:
            if (event.type ==  sf::Event::JoystickButtonPressed && event.joystickButton.joystickId == joySUS.getButtonData(0))
            {
               //std::cout << " button fixed " << std::endl;
               joySUS.wrightToData(JoyPad::Status::JOY_DROP_BAG, event.joystickButton.button);
                   menu.text[5].setString("Fixed Shot button " + std::to_string(joySUS.getButtonData(3)));
               joySUS.stepStatus();
                   menu.text[4].setString(joySUS.getCheckReport(6));
            }
            break;

    case JoyPad::Status::JOY_DROP_DESK:
            if (event.type ==  sf::Event::JoystickButtonPressed && event.joystickButton.joystickId == joySUS.getButtonData(0))
            {
               //std::cout << " button fixed " << std::endl;
               joySUS.wrightToData(JoyPad::Status::JOY_DROP_DESK, event.joystickButton.button);
                   menu.text[5].setString("Fixed Shot button " + std::to_string(joySUS.getButtonData(4)));
               joySUS.stepStatus();
                   menu.text[4].setString(joySUS.getCheckReport(7));
            }
            break;

    case JoyPad::Status::JOY_SWAP:
            if (event.type ==  sf::Event::JoystickButtonPressed && event.joystickButton.joystickId == joySUS.getButtonData(0))
            {
               //std::cout << " button fixed " << std::endl;
               joySUS.wrightToData(JoyPad::Status::JOY_SWAP, event.joystickButton.button);
                   menu.text[5].setString("Fixed spiderSwap button " + std::to_string(joySUS.getButtonData(5)));
                   menu.text[4].setString(joySUS.getCheckReport(8));
                      animaJoyWait.registrica = animaJoyWait.timer + iternalCLK.getElapsedTime().asMilliseconds()/100;
                      animaJoyWait.trigger = true;
            }
            break;
    }
}
