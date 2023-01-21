#include "globalic.h"

Segment::Segment()
: segUp(false)
{
  float margin = 0.f;

  float startX = world_S.x/6 - 20 - margin/2;
  float startY = world_S.y/5;
  float goX = startX;
  float goY = startY;
  float stepX = 50.f;
  float stepY = 50.f;
  float range = 20.f;

    float goSX = startX + (stepX*4 + range);
    float goTHX = startX + (stepX*4 + range)*2 + margin;
    float goFRX = startX + (stepX*4 + range)*3 + margin;

    for (int pF=0; pF<28; pF++)
    {
        posF[pF].x = goX;
        posF[pF].y = goY;
         posS[pF].x = goSX;
         posS[pF].y = goY;
          posTH[pF].x = goTHX;
          posTH[pF].y = goY;
           posFR[pF].x = goFRX;
           posFR[pF].y = goY;

        if (goX == startX + (stepX*3)) {
            goX = startX;
             goSX = startX + (stepX*4 + range);
              goTHX = startX + (stepX*4 + range)*2 + margin;
               goFRX = startX + (stepX*4 + range)*3 + margin;
            goY = goY + stepY;
        }//end of if
        else {
            goX = goX + stepX;
             goSX = goSX + stepX;
              goTHX = goTHX + stepX;
               goFRX = goFRX + stepX;
        }//end of else
    }// end of for

  //making form of segment looks like and it positions
  for (int rS=0; rS<28; rS++)
  {
    rectF[rS].setSize(sf::Vector2f(40.f, 40.f));
    rectF[rS].setFillColor(sf::Color(30,144,255,255));
    rectF[rS].setOutlineColor(sf::Color(0,255,255,255));
    rectF[rS].setOutlineThickness(-2.f);
    rectF[rS].setPosition(posF[rS]);
     rectS[rS].setSize(sf::Vector2f(40.f, 40.f));
     rectS[rS].setFillColor(sf::Color(30,144,255,255));
     rectS[rS].setOutlineColor(sf::Color(0,255,255,255));
     rectS[rS].setOutlineThickness(-2.f);
     rectS[rS].setPosition(posS[rS]);
      rectTH[rS].setSize(sf::Vector2f(40.f, 40.f));
      rectTH[rS].setFillColor(sf::Color(30,144,255,255));
      rectTH[rS].setOutlineColor(sf::Color(0,255,255,255));
      rectTH[rS].setOutlineThickness(-2.f);
      rectTH[rS].setPosition(posTH[rS]);
       rectFR[rS].setSize(sf::Vector2f(40.f, 40.f));
       rectFR[rS].setFillColor(sf::Color(30,144,255,255));
       rectFR[rS].setOutlineColor(sf::Color(0,255,255,255));
       rectFR[rS].setOutlineThickness(-2.f);
       rectFR[rS].setPosition(posFR[rS]);
  }//end of for

  this->setBoolNumberNothing(1);
  this->setBoolNumberNothing(2);
  this->setBoolNumberNothing(3);
  this->setBoolNumberNothing(4);

  this->setLeaders();
}//end of ctor

Segment::~Segment()
{

}//end of dtor

void Segment::setBoolNumberNothing(unsigned int who)
{
  if (who > 0 && who < 5)
  {
    if (who == 1) {  for (int bN=0; bN<28; bN++) { numberOne[bN] = false; };  }
    else if (who == 2) {  for (int bN=0; bN<28; bN++) { numberTwo[bN] = false; };  }
    else if (who == 3) {  for (int bN=0; bN<28; bN++) { numberThree[bN] = false; };  }
    else if (who == 4) {  for (int bN=0; bN<28; bN++) { numberFour[bN] = false; };  }
    else {};
  }
  else {  std::cout << " SEGMENT ERR Wrong number identifyer!!! Can't complete! " << std::endl;  }

}//end of void

void Segment::setBoolNumber (bool(&arr)[28], unsigned int digit)
{
  if (digit < 0 || digit > 9) { std::cout << " SEGMENT ERR Sorry digit number is out of range! Can't complete! " << std::endl;  }
  else
  {
    for (int i=0; i<28; i++) { arr[i] = false; };

    if (digit == 0)
    {
        arr[0] = arr[1] = arr[2] = arr[3] = true;
         arr[7] = arr[11] = arr[15] = arr[19] = arr[23] = true;
        arr[27] = arr[26] = arr[25] = arr[24] = true;
         arr[20] = arr[16] = arr[12] = arr[8] = arr[4] = true;
    }//end of if
    else if (digit == 1)
    {
        arr[12] = arr[9] = arr[6] = arr[3] = true;
         arr[7] = arr[11] = arr[15] = arr[19] = arr[23] = true;
        arr[27] = true;

    }//end of else if
    else if (digit == 2)
    {
        arr[4] = arr[0] = arr[1] = arr[2] = arr[3] = true;
          arr[7] = arr[11] = arr[15] = true;
         arr[18] = arr[21] = arr[24] = true;
        arr[25] = arr[26] = arr[27] = true;
    }//end of else if
    else if (digit == 3)
    {
        arr[0] = arr[1] = arr[2] = arr[3] = true;
         arr[7] = arr[11] = true;
          arr[13] = arr[14] = arr[15]  = true;
         arr[19] = arr[23] = true;
        arr[24] = arr[25] = arr[26] = arr[27] = true;
    }//end of else if
    else if (digit == 4)
    {
        arr[0] = arr[4] = arr[8] = arr[12] = true;
         arr[13] = arr[14] = true;
        arr[3] = arr[7] = arr[11] = arr[15] = arr[19] = arr[23] = true;
        arr[27] = true;
    }//end of else if
    else if (digit == 5)
    {
        arr[3] = arr[2] = arr[1] = arr[0] = true;
         arr[4] = arr[8] = true;
        arr[12] = arr[13] = arr[14] = arr[15] = true;
         arr[19] = arr[23] = true;
        arr[27] = arr[26] = arr[25] = arr[24] = true;
    }//end of else if
    else if (digit == 6)
    {
        arr[0] = arr[1] = arr[2] = arr[3] = true;
         arr[4] = arr[8] = true;
        arr[12] = arr[13] = arr[14] = arr[15] = true;
         arr[19] = arr[23] = true;
        arr[27] = arr[26] = arr[25] = arr[24] = true;
         arr[20] = arr[16] = true;
    }//end of else if
    else if (digit == 7)
    {
        arr[0] = arr[1] = arr[2] = arr[3] = true;
        arr[4] = true;
         arr[7] = arr[11] = arr[15] = true;
         arr[18] = arr[21] = arr[25] = true;
    }//end of else if
    else if (digit == 8)
    {
        arr[0] = arr[1] = arr[2] = arr[3] = true;
         arr[7] = arr[11] = arr[15] = arr[19] = arr[23] = true;
        arr[27] = arr[26] = arr[25] = arr[24] = true;
         arr[20] = arr[16] = arr[12] = arr[8] = arr[4] = true;
        arr[13] = arr[14] = true;
    }//end of else if
    else if (digit == 9)
    {
        arr[0] = arr[1] = arr[2] = arr[3] = true;
         arr[7] = arr[11] = arr[15] = true;
        arr[14] = arr[13] = arr[12] = true;
         arr[8] = arr[4] = true;
          arr[19] = arr[23] = true;
          arr[27] = arr[26] = arr[25] = arr[24] = true;
    }//end of else if
    else{};//end of else
  }//end of else
}//end of void

void Segment::resetSegPos()
{
   for(int rS=0; rS<28; rS++)
   {
      rectF[rS].setPosition(posF[rS]);
      rectS[rS].setPosition(posS[rS]);
      rectTH[rS].setPosition(posTH[rS]);
      rectFR[rS].setPosition(posFR[rS]);
   }//end of for
}//end of void

void Segment::setLeaders()
{
   leaderTop[0] = 0;
   leaderBottom[0] = 27;
   leaderTop[1] = 3;
   leaderBottom[1] = 27;
   leaderTop[2] = 0;
   leaderBottom[2] = 27;
   leaderTop[3] = 0;
   leaderBottom[3] = 27;
   leaderTop[4] = 0;
   leaderBottom[4] = 27;
   leaderTop[5] = 0;
   leaderBottom[5] = 27;
   leaderTop[6] = 0;
   leaderBottom[6] = 27;
   leaderTop[7] = 0;
   leaderBottom[7] = 25;
   leaderTop[8] = 0;
   leaderBottom[8] = 27;
   leaderTop[9] = 0;
   leaderBottom[9] = 27;
}
