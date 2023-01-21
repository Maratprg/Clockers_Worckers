#ifndef GLOBALIC_H
#define GLOBALIC_H
#include <SFML/Graphics.hpp>
#include <iostream>

static sf::Vector2f world_S(1200.f, 800.f);

struct Segment
{
        Segment(); // in constr ini rectangles how looks like and makes a matrix position of each over
        ~Segment();
  sf::RectangleShape rectF[28];
  sf::Vector2f posF[28];
  sf::RectangleShape rectS[28];
  sf::Vector2f posS[28];
  sf::RectangleShape rectTH[28];
  sf::Vector2f posTH[28];
  sf::RectangleShape rectFR[28];
  sf::Vector2f posFR[28];

  void resetSegPos(); //inicialize segment positions by sf::Vector2f objects witch fill up in cnstr

  //arrays wich controll represent digit
  bool numberOne[28];
  bool numberTwo[28];
  bool numberThree[28];
  bool numberFour[28];

   int leaderTop[10]; // this int array keeping data that have top leader of segmetns
   int leaderBottom[10]; // this int array keeping data that have bottop leader of segmetns
   void setLeaders(); // this void set leaders of arrays

   void setBoolNumberNothing(unsigned int who); // this void goes reset all segment rects unvisible
   void setBoolNumber(bool(&arr)[28], unsigned int digit); //this void make visible digit from seg rect

  public:
     bool segUp;

};


#endif // GLOBALIC_H
