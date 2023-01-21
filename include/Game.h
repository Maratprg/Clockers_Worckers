#ifndef GAME_H
#define GAME_H

#include <globalic.h>
#include <Entity.h>
#include <SmartHolder.h>
#include <Creature.h>
#include <JoyPad.h>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <cstring>
#include <vector>
#include <deque>
#include <fstream>


//temporary
#include <typeinfo>

class Game
{
    public:
            Game();
            ~Game();
        void run();


    //declaration of subfunctional structures
    public:
            //declaration of checking animation structure
           struct Anima {
                Anima() = default;
                Anima(bool b, int tm, int r): trigger(b), timer(tm), registrica(r) {}; // INITIALISER LIST CONSTR?
                Anima (const Anima& a)
                                    {
                                      trigger = a.trigger;
                                      timer = a.timer;
                                      registrica = a.registrica;
                                    }

                Anima (Anima&& a) = default;

                Anima& operator=(const Anima& inc)
                {
                  if (this != &inc)
                  {
                      trigger = inc.trigger;
                      timer = inc.timer;
                      registrica = inc.registrica;
                  }
                  return *this;
                }

                bool trigger = false; //trigger
                int timer = 0;        //milliseconds
                int registrica = 0;   //stop-timer
            };

            static const int maxSingleVecSize = 100; //maximum single vector size

    public:
        void buildGame();
        void buildClock();


    private:
        void processEvents();
        void processEnemyBullets(uint32_t t);
        void processSpecEfects(uint32_t t);
        void update(sf::Time elapsedTime, uint32_t t);
        void updateSegMech(sf::Time elapsedTime, uint32_t t);
        void brainWishCollide(uint32_t t);
        void playSound();
        void render();

        void handlePlayerInput(sf::Event& event);

                void fillUpVectorCreatures(int cnt);
                    bool veryfyVecExist() { return !(creature_vec.empty()); }



    public:
    sf::RenderWindow mWindow;

        JoyPad joySUS; //system joystick
        void checkUpJoy(sf::Event& event); //redifine keys at the end of cpp
        Anima animaJoyWait{false,8,0};
            bool turnJoy = false;
            void turnInputsJK (bool turn)
            {
               if (turnJoy == turn)
               {
                   mIsMovingRight = false;
                   mIsMovingLeft = false;
                   if(turnJoy == true) turnJoy = false;
                   else turnJoy = true;
               }
            };


    public: //system backgroung
    sf::RectangleShape backG;
    void autoSetBackG();

    public: //system time visObj
    sf::Text dateText;
    sf::Font font;
    void autoSetTimeText();

    //start menu
    struct Menu
    {
      sf::Sprite cover;
      Anima animaCover{true, 10, 0};

      sf::Sprite gameCone;
      Anima animaGameCone{true, 9, 0};
        sf::RectangleShape finGC;

          sf::Sprite labelCreatures;
          Anima animaLabelCreatures{true, 20, 0};

          sf::Sprite spiderPersonage;
          Anima animaSpiderPersonage{true, 20, 0};

          sf::Text textAlarm;
          bool setTextAlarmVisible = true;
            bool flagAlarm = false;
            std::string inserted;
            int sysAlrm[2];
              int sysAlarmCounter = 20;

          sf::Text text[6];
          bool textVisible[6];
            int threeTrigger; //menuTrigger

          void turnTrigger(bool up)
              {
                text[threeTrigger].setFillColor(sf::Color::White);

                    if (!up) threeTrigger++;
                    else threeTrigger--;
                    if (threeTrigger==4) threeTrigger = 1;
                    if (threeTrigger==0) threeTrigger = 3;
                text[threeTrigger].setFillColor(sf::Color(255,76,91,255));
              }

    } menu;
    void buildStartMenu(); //at the end cpp
    void buildEndMenu(); //at the end cpp


     struct ScoreText{
          sf::Text s_Txt;
          int s_Int = 0;
          bool visible = false;
          } score;
            void autoSetScoreText();


        //Creatures and Entityes
        sf::CircleShape mPlayer;
            static const float      playerSpeed;
            static const sf::Time   timePerFrame;
            //player driving variables
            bool  mIsMovingUp;
            bool  mIsMovingDown;
            bool  mIsMovingLeft;
            bool  mIsMovingRight;
                //player-bullets
                std::vector<sf::CircleShape> bulletVec;
                float mPbspeed = 10.f;
                void mPlayerStartBullet(); //at end of cpp
                void mPlayerDetachBullet(std::vector<sf::CircleShape>::iterator it); //at end of cpp
                  Anima animaBulletQueue{false, 1, 0};
                  int bulletCountsInQueue = 0; //bullets counter

        //bullet entities (the triggering of each creature and visability lay out on too bools anima.trigg and untrigging bool)
        struct B_creatures {
            Creature boxbag {1, 'b'};
            Anima boxbag_anima {false, 89, 0};
            Creature pipiter {1, 'p'};
            Anima pipiter_anima {false, 89, 0};
                sf::RectangleShape r_shape_bag;
                sf::RectangleShape r_shape_pipiter;
                bool r_shape_bag_untrigged = false; //shape bag and live time cycle in handle player input
                bool r_shape_pipiter_untrigged = false;
                   float sh_places[2]; //keepeng last positions
                   float velocity = 10;
                       int colliderBagObj[maxSingleVecSize] = {-1};
                       int colliderPipObj[maxSingleVecSize] = {-1};
        } b_creatures;

            //temporary debug creature must be deleted son
            Creature debugCreature {10, 'r'};

            //temporary debug sprite
            //sf::Sprite temporary;
            //sf::Texture temp_text;

            int soundWelderCounter = 1; //trigging welders sounds
            bool fishHook = false;

        Entity fWelder;
        Entity sWelder;
            int digitSecure; //variable to drive selected digit (0-3)
            sf::Vector2f w_startPos[2];

        struct Indian_Stru {
            Creature horsefly {1,'h'}; //indian bullet entity
            Creature indian {3, 'i'};
                const float bulletSpeed = 3;
                    bool indianLeft = true; //indicator of working place
              sf::Vector2f i_pos[2];
              sf::Vector2f h_pos[2];
                Anima burn {false, 200, 0};
                Anima anima {false, 8, 0};
                Anima shot {false, 50, 0};
              const int livesCount = 50;
              int lives = livesCount;
                    int timeFly = 0;
        } indian_stru;


        struct G_Column {
            sf::RectangleShape r_shape;
            bool visible = true;
            Anima affected {false, 6, 0};
        } g_column;

        struct Spider {
            sf::Sprite sprite;
              void turn(bool left)
              {
                if(!left) sprite.setPosition(world_S.x/2 - 10.f, world_S.y/2 + 90.f); // right case
                else sprite.setPosition(world_S.x/2 - 90.f, world_S.y/2 + 90.f); // left case
                Left = left;
              }
             bool visible = true;
            bool Left = true;
           Anima animaHungry{false, 200, 0}; //hungry statement
              int occurenceHungry = 0;       //hungry
        } spider;

        std::deque<Creature> creature_vec;
        std::deque<Anima>cr_vec_anima;
            bool detachCreature(std::deque<Creature>::iterator& cr, std::deque<Anima>::iterator& an); // at the end of cpp
            int generalSize() { return creature_vec.size(); }
                void storeCreatures(); // at the end of cpp (GENERAL DELETER)
            //detaucher always One!!! to or more must two hapend cases at single time
        //Anima vec_anima {false, 1, 0};


    /*important sound: logic. 0-indian burn, 1-indian short, 2-affected g_column, 3-start bullet,
                              4-indianDamage, 5-indianDie, 6-boxbagBurn, 7-boxbagDeath, 8-pipiterBurn,
                              9-pipiterDeath, 10-byteBoxSquare, 11-bytePipiterSquare
                              12-fightWolf, 13-songRoster, 14-volfDamage, 15-rosterDamage,
                              16-volfDie, 17-rosterDie, 18-spiderEat, 19-spiderHungry
                              20-flyHorseFly, 21-Enter, 23-Select, 24-weldering1, 25-weldering2,
                              26-weldering3, 27-welderGoSecure, 28-returnSecure */
    bool serviceSound[30];
    sf::Sound mySound[30];

            void fillUpMySounds(); //at end of cpp

    //important resurse holder
    SmartHolder YIU;

    //mech of segment
    public:
        Segment seg;
        bool segmentTriger;
        int32_t timeCControllerSeg;
        int segIterVar; // general variable to switch squears(0-27) in driving digit when it need to move
          int memDig[4]; //general array to fill each segment with digit
            sf::RectangleShape* currentSeg; //general PTR driver
            sf::Vector2f* curSegPos; //general PTR position
            bool* currentBL; //general PTR driver
        int multiTriger = 0b00000000; // triggin background
        /*0-falling digit, 1-goSecure, 2-goToHeap, 3-returnHeap(segUp), 4-goWeldering, 5-goShowFire, 6-returnWeldering, 7-goReturn*/
                Anima animaSegment{false, 4200, 0};

    public: //system iternal time obj
        sf::Clock iternalCLK;

    public: //system time subfunctional
        std::string getSysTime();
        unsigned int getSysHour();
        unsigned int getSysMin();

    //mech of scene switching
    public:
        enum S_SCENE
        {
            ZERRO,
            FIRST,
            SECOND,
            THIRD,
            LAST,
            ENUM_COUNT
        };
        S_SCENE idScene;
};



#endif // GAME_H
