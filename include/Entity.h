#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <ctime>
#include <cmath>

class Entity
{
    public:
        Entity();
        ~Entity();

        sf::Texture texture;
        sf::Sprite sprite;

        //moving triger variables
        sf::Vector2f wldrGoPos[4]; //data of secure positions of workers
            bool Syncro;


        int welderShowFire; //this int keeps data time of showing weldring light

        sf::Vector2f uVec;
        sf::Vector2f speed;
            void autoSetSpeed();                //auto setter speed in void
        void moveToPoint(float xP, float yP);  //fast mooving to direct point by speed

        //because workers shows from diferent kinds of view, this voids changes its visible body and fire sprites.
        void loadWelder();
          void setWldrFace();
          void setWldrBack();
          void setWldrSideR();
          void setWldrSideRFire();
          void setWldrSideL();
          void setWldrSideLFire();
        sf::Vector2f wldrSize;

        void loadWelderBlame();
        sf::CircleShape blame;
        sf::CircleShape blameTwo;

        void autoSetBlameFront();
        void autoSetBlameBack();
        void autoSetBlameSideL();
        void autoSetBlameSideR();
            float trans;

        bool blameVisible;
        bool visible;
};

#endif // ENTITY_H
