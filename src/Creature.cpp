#include "Creature.h"

void Creature::iniFrameArray(int N)
{
    frameArr = new FourF[N];
}

void Creature::reArrayReName(int N, char inc_name)
{
     INI = N;

            //realloc memory
            delete [] frameArr;
            frameArr = new FourF[N];

     name = inc_name;
}


void Creature::makeByChar(bool left)
{
    Left = left;

    //VARIABLES FOR VOLF ROSTER AND INDIAN
    if (name == 'v')
    {
      tW = 596;
      tH = 401;
         cutterW = tW/4;
         cutterH = tH/2;
            cur_posx = 0;
            cur_posy = 0;
    }
    else if (name == 'r')
    {
      tW = 607;
      tH = 417;
        cutterW = tW/5;
        cutterH = tH/2;
            cur_posx = 0;
            cur_posy = 0;
    }
    else if (name == 'i')
    {
      tW = 174;
      tH = 502;
        cutterW = tW;
        cutterH = tH/3;
            cur_posx = 0;
            cur_posy = 0;
    }
    else {};

        //MAKING ARRAY FOR EACH CASES
        if (name == 'i' && left)
        {
             //std::cout << right << " here? INI " << INI << std::endl;

              for (int i=0; i<INI; i++)
              {
                  frameArr[i].x1 = cur_posx;
                  frameArr[i].y1 = cur_posy;
                  frameArr[i].x2 = cutterW;
                  frameArr[i].y2 = cutterH;

                  if (cur_posy < (tH - cutterH)) cur_posy = cur_posy + cutterH;
                  else cur_posy = 0;
              }
        }
        else if (name == 'i' && !left)
        {
              //std::cout << right << " here? INI " << INI << std::endl;

              cur_posx = tW;
              for (int i=0; i<INI; i++)
              {
                  frameArr[i].x1 = cur_posx;
                  frameArr[i].y1 = cur_posy;
                  frameArr[i].x2 = -cutterW;
                  frameArr[i].y2 = cutterH;

                  if (cur_posy < (tH - cutterH)) cur_posy = cur_posy + cutterH;
                  else cur_posy = 0;
              }
        }
        else if (left)
        {
               for (int i=0; i<INI; i++)
               {

                    if (cur_posx <= (tW - cutterW))
                    {
                        frameArr[i].x1 = cur_posx;
                        frameArr[i].y1 = cur_posy;
                        frameArr[i].x2 = cutterW;
                        frameArr[i].y2 = cutterH;
                           cur_posx = cur_posx + cutterW;
                    }
                    else
                    {
                        cur_posy = cur_posy + cutterH;
                        cur_posx = 0;
                            frameArr[i].x1 = cur_posx;
                            frameArr[i].y1 = cur_posy;
                            frameArr[i].x2 = cutterW;
                            frameArr[i].y2 = cutterH;
                                cur_posx = cur_posx + cutterW;

                    }

                    /*std::cout << "true case x1 | y1 | x2 | y2 " << frameArr[i].x1 << " | "
                                                                  << frameArr[i].y1 << " | "
                                                                    << frameArr[i].x2 << " | "
                                                                      << frameArr[i].y2 << std::endl;*/
               }
        }
        else
        {
              cur_posx = tW;

              for (int i=0; i<INI; i++)
              {
                  frameArr[i].x1 = cur_posx;
                  frameArr[i].y1 = cur_posy;
                  frameArr[i].x2 = -cutterW;
                  frameArr[i].y2 = +cutterH;


                  /*std::cout << " false case x1 | y1 | x2 | y2 " << frameArr[i].x1 << " | "
                                                                  << frameArr[i].y1 << " | "
                                                                    << frameArr[i].x2 << " | "
                                                                      << frameArr[i].y2 << std::endl;*/

                  if (cur_posx > cutterW)
                  {
                     if(i != ((INI/2)-1)) cur_posx -= cutterW;
                     else
                     {
                       cur_posx = tW;
                       cur_posy += cutterH;
                     }
                  }
                  else
                  {
                      cur_posx = tW;
                      cur_posy += cutterH;
                  }

              }
        }

    //first frame
    this->setTextureRect(sf::IntRect(frameArr[0].x1, frameArr[0].y1,
                                     frameArr[0].x2, frameArr[0].y2  ));

}

void Creature::autoSetWalk(bool left)
{
    if (left != Left) makeByChar(left);

    switch (name)
    {
            case 'v':
                frameRangerDown = frameRoter = (INI/2);
                frameRangerUP = INI-1;
                break;
            case 'r':
                frameRangerDown = frameRoter = (INI/2);
                frameRangerUP = INI-1;
                break;
            case 'i':
                frameRangerDown = frameRoter = 0;
                frameRangerUP = INI - 1;
                break;
            default:

                break;
    }

}

void Creature::autoSetFight(bool left)
{
    if (left != Left) makeByChar(left);

    switch (name)
    {
            case 'v':
                frameRangerDown = frameRoter = 0;
                frameRangerUP = (INI/2) - 1;
                break;
            case 'r':
                frameRangerDown = frameRoter = 0;
                frameRangerUP = (INI/2) - 1;
                break;
            case 'i':
                frameRangerDown = frameRoter = 0;
                frameRangerUP = INI - 1;
                break;
            default:

                break;
    }

}

//mech framing
void Creature::changeFrame()
{
      //std::cout << frameRoter << std::endl;
      this->setTextureRect(sf::IntRect(frameArr[frameRoter].x1, frameArr[frameRoter].y1,
                                       frameArr[frameRoter].x2, frameArr[frameRoter].y2  ));

      if(frameRoter < frameRangerUP) frameRoter++;
      else frameRoter = frameRangerDown;

      /*std::cout << "frameRoter " << frameRoter << " " << frameArr[frameRoter].x1 << "|" << frameArr[frameRoter].y1 << "|"
                                   <<  frameArr[frameRoter].x2 << "|" << frameArr[frameRoter].y2 << std::endl;*/
}

void Creature::setFrameByInt(int frame)
{
    if (frame <= INI-1) setTextureRect( sf::IntRect(frameArr[frame].x1, frameArr[frame].y1, frameArr[frame].x2, frameArr[frame].y2 ));
}




