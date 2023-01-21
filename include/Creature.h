#ifndef CREATURE_H
#define CREATURE_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Creature : public sf::Sprite
{
    public:
        Creature() = default; //: INI(10), name('v'), Left(false), Mover(true), visible(true) {this->iniFrameArray(INI);};
        Creature(int N): INI(N){ this->iniFrameArray(N); }
        Creature(int N, char inc_name):INI(N), name(inc_name){ this->iniFrameArray(N); }
        Creature(const Creature& inc)
                                    {
                                         INI = inc.INI;
                                         name = inc.name;
                                         Left = inc.Left;
                                         Mover = inc.Mover;
                                         visible = inc.visible;
                                            lives = inc.lives;
                                            velocity = inc.velocity;
                                         this->iniFrameArray(INI);
                                            for (int i=0; i<INI; i++)
                                            {
                                                frameArr[i].x1 = inc.frameArr[i].x1;
                                                frameArr[i].y1 = inc.frameArr[i].y1;
                                                frameArr[i].x2 = inc.frameArr[i].x2;
                                                frameArr[i].y2 = inc.frameArr[i].y2;
                                            }

                                            this->setTexture(*(inc.getTexture()));
                                            this->makeByChar(Left);
                                            this->autoSetWalk(Left);
                                            this->setPosition(sf::Vector2f(inc.getPosition().x, inc.getPosition().y));

                                            /*std::cout << " Creature(&) INI | name | Left | visible "
                                                        << INI << " | " << name << " | " << std::endl;*/
                                    }
        Creature (Creature&& inc) = default;

        Creature& operator=(const Creature& inc)
            {
               if (this != &inc)
               {
                    INI = inc.INI;
                     name = inc.name;
                      Left = inc.Left;
                       Mover = inc.Mover;
                        visible = inc.visible;
                          lives = inc.lives;
                            velocity = inc.velocity;
                    this->iniFrameArray(INI);
                    for (int i=0; i<INI; i++)
                    {
                        frameArr[i].x1 = inc.frameArr[i].x1;
                        frameArr[i].y1 = inc.frameArr[i].y1;
                        frameArr[i].x2 = inc.frameArr[i].x2;
                        frameArr[i].y2 = inc.frameArr[i].y2;
                    }

                    this->setTexture(*(inc.getTexture()));
                    this->makeByChar(Left);
                    this->autoSetWalk(Left);
                    this->setPosition(sf::Vector2f(inc.getPosition().x, inc.getPosition().y));
               }
                    return *this;
                    //std::cout << " >>>>>  opertor= & " << std::endl;
           }




        virtual ~Creature() { delete[] frameArr; }

        //functional
        void iniFrameArray(int N);
        void reArrayReName(int N, char inc_name); //IMPORTANT! errase previous array values



        //subfunctional
        void makeByChar(bool left);

        void autoSetWalk(bool left);
        void autoSetFight(bool left);

        void changeFrame();
          void setFrameByInt(int frame);

        const bool& getLeft() const { return Left; }


    public:
        struct FourF
        {
            int x1 = 0;
            int y1 = 0;
            int x2 = 0;
            int y2 = 0;
        };

    public:
        bool visible = true;
        FourF * frameArr;
         char name = '0';

         int velocity = 3;

         bool Mover = true;
         int lives = 20;

    private:
        int INI;
          int frameRangerUP = 0;
          int frameRangerDown = 0;
        int frameRoter = 0;
        bool Left = false; //this value must keep direction of creature from 'bool right'

        //mech vars
        int tW, tH, cutterW, cutterH, cur_posx, cur_posy = 0;

};

#endif // CREATURE_H
