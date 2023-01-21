#include "Entity.h"
#include <iostream>

Entity::Entity()
: visible(true)
, blameVisible(false)
, welderShowFire(0)
, Syncro(false)
{
    //ctor
    //initialization position of welders secure
    wldrGoPos[0].x = 230.f;
    wldrGoPos[0].y = 100.f;

    wldrGoPos[1].x = 460.f;
    wldrGoPos[1].y = 100.f;

    wldrGoPos[2].x = 690.f;
    wldrGoPos[2].y = 100.f;

    wldrGoPos[3].x = 900.f;
    wldrGoPos[3].y = 100.f;

    //initialization welders unit vectors
    uVec.x = uVec.y = 0.f;

    //speed
    this->autoSetSpeed();
}

Entity::~Entity()
{
    //dtor
}

//welder block
void Entity::loadWelder()
{
    try
    {
    texture.loadFromFile("Media/welderRobotW87H94.png");
    sprite.setTexture(texture);
    wldrSize.x = 87.5f;
    wldrSize.y = 94.f;
    sprite.setTextureRect(sf::IntRect(0, 0, wldrSize.x, wldrSize.y));
    }
    catch (std::runtime_error& e)
    {
    std::cout << "ENTITY ERR:: " << e.what() << std::endl;
    }
}//end of void

void Entity::setWldrFace()
{
    sprite.setTextureRect(sf::IntRect(0, 0, wldrSize.x, wldrSize.y));
    blameVisible = false;
}

void Entity::setWldrBack()
{
    sprite.setTextureRect(sf::IntRect(wldrSize.x, 0, wldrSize.x, wldrSize.y));
    this->autoSetBlameBack();
}

void Entity::setWldrSideR()
{
    sprite.setTextureRect(sf::IntRect(wldrSize.x*2, 0, wldrSize.x, wldrSize.y));
    this->autoSetBlameSideR();
}

void Entity::setWldrSideRFire()
{
    sprite.setTextureRect(sf::IntRect(wldrSize.x*3, 0, wldrSize.x, wldrSize.y));
    this->autoSetBlameSideR();
}

void Entity::setWldrSideL()
{
    sprite.setTextureRect(sf::IntRect(wldrSize.x*3, 0, -wldrSize.x, wldrSize.y));
    this->autoSetBlameSideL();
}

void Entity::setWldrSideLFire()
{
    sprite.setTextureRect(sf::IntRect(wldrSize.x*4, 0, -wldrSize.x, wldrSize.y));
    this->autoSetBlameSideL();
}

void Entity::loadWelderBlame()
{
blame.setFillColor(sf::Color::Red);
blame.setRadius(wldrSize.x/17);
blame.setOutlineThickness(-1.f);
blame.setOutlineColor(sf::Color(0,255,255,255));

blameTwo.setFillColor(sf::Color::Red);
blameTwo.setRadius(wldrSize.x/17);
blameTwo.setOutlineThickness(-1.f);
blameTwo.setOutlineColor(sf::Color(0,255,255,255));

float x = sprite.getPosition().x + wldrSize.x/3 + 5.f;
float y = sprite.getPosition().y + wldrSize.y/2 + 15.f;
float xT = sprite.getPosition().x + wldrSize.x/3 + 15.f;
float yT = sprite.getPosition().y + wldrSize.y/2 + 15.f;

blame.setPosition(x + 0.8f, y);
blameTwo.setPosition(xT + 0.8f, yT);

//std::cout << "BLAME POSITION Y ONE | TWO " << y << " | " << yT << std::endl;
}

void Entity::autoSetBlameFront()
{
   blameVisible = false;
}

void Entity::autoSetBlameBack()
{
    float x = sprite.getPosition().x + wldrSize.x/3 + 5.f;
    float y = sprite.getPosition().y + wldrSize.y/2 + 15.f;
    float xT = sprite.getPosition().x + wldrSize.x/3 + 15.f;
    float yT = sprite.getPosition().y + wldrSize.y/2 + 15.f;

    trans = 100 + rand()%100;
    blame.setFillColor(sf::Color(0,116,255, trans));
    trans = 100 + rand()%100;
    blameTwo.setFillColor(sf::Color(0,116,255, trans));
    //std::cout << "TRANS " << trans << std::endl;

    blame.setPosition(x + 0.8f, y);
    blameTwo.setPosition(xT + 0.8f, yT);

    blameVisible = true;
}//end of void

void Entity::autoSetBlameSideL()
{
   float x = sprite.getPosition().x + wldrSize.x - 13.f;
   float y = sprite.getPosition().y + wldrSize.y/2 + 4.f;

   blame.setFillColor(sf::Color(255,255,255, 255));
   trans = 100 + rand()%100;
   blameTwo.setFillColor(sf::Color(0,116,255, trans));
   //std::cout << "TRANS " << trans << std::endl;

   blame.setPosition(x + 0.8f, y);
   blameTwo.setPosition(x + 0.8f, y);

   blameVisible = true;
}//end of void

void Entity::autoSetBlameSideR()
{
  float x = sprite.getPosition().x + 1.f;
  float y = sprite.getPosition().y + wldrSize.y/2 + 4.f;

  blame.setFillColor(sf::Color(255,255,255, 255));
  trans = 100 + rand()%100;
  blameTwo.setFillColor(sf::Color(0,116,255, trans));
  //std::cout << "TRANS " << trans << std::endl;

  blame.setPosition(x + 0.8f, y);
  blameTwo.setPosition(x + 0.8f, y);

  blameVisible = true;
}//end of void

void Entity::autoSetSpeed()
{
    speed.x = 6;
    speed.y = 6;
}

void Entity::moveToPoint(float xP, float yP)
{
  float posX = sprite.getPosition().x;
  float posY = sprite.getPosition().y;

     float signX, signY;
     if ((int)posX < (int)xP) signX = +1.f;
     else if ((int)posX > (int)xP) signX = -1.f;
     if ((int)posY < (int)yP) signY = +1.f;
     else if ((int)posY > (int)yP) signY = -1.f;

          //speed correction
          if(abs(posX - xP) < speed.x) speed.x = 1;
          if(abs(posY - yP) < speed.y) speed.y = 1;


     if ((int)posX != (int)xP && (int)posY != (int)yP)
     {
         sprite.setPosition(posX+(signX*speed.x), posY+(signY*speed.y));
     }
     else if ((int)posX == (int)xP)
     {
         sprite.setPosition(posX, posY+(signY*speed.y));
     }
     else if ((int)posY == (int)yP)
     {
         sprite.setPosition(posX+(signX*speed.x), posY);
     }
     else {}
}

