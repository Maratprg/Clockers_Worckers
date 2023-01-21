#ifndef JOYPAD_H
#define JOYPAD_H

#include <iostream>

#include <string>
#include <fstream>



class JoyPad
{
        //internal structure and enums
        public:
                    struct GamePad_Data{
                        unsigned int port;
                        unsigned int start;
                         float maxX;
                         float maxY;
                         float rngX;
                         float rngY;
                        unsigned int shot;
                        unsigned int dropBag;
                        unsigned int dropDesk;
                        unsigned int spiderSwap;

                    };

                    enum Status
                    {
                        SEEK_PORT,
                        CHECK_X,
                        CHECK_Y,
                        JOY_START,
                        JOY_SHOT,
                        JOY_DROP_BAG,
                        JOY_DROP_DESK,
                        JOY_SWAP,
                        READY,
                    };

                   struct TwoFloat
                   {
                       TwoFloat(float inc_fMax, float inc_fMin): fmax(inc_fMax), fmin(inc_fMin) {};
                       float fmax;
                       float fmin;
                   };


    public:
        JoyPad();
        virtual ~JoyPad();

                //subfunctional template instatiation in header
                template<typename T>
                void wrightToData(Status&& id, T&& t)
                {
                   //template cause in future may float happend cases
                   switch(id)
                   {
                       case SEEK_PORT: data.port = t; break;
                       case CHECK_X: data.maxX = t; data.rngX = 15.f;
                       case CHECK_Y: data.maxY = t; data.rngY = 15.f;
                       case JOY_START: data.start = t; break;
                       case JOY_SHOT: data.shot = t; break;
                       case JOY_DROP_BAG: data.dropBag = t; break;
                       case JOY_DROP_DESK: data.dropDesk = t; break;
                       case JOY_SWAP: data.spiderSwap = t; break;
                   }
                   //std::cout << "writed! " << static_cast<int>(id) << " value " << t << std::endl;
                }


                unsigned int& getButtonData (int number)
                {
                   switch(number)
                       {
                           case 0: return data.port;
                           case 1: return data.start;
                           case 2: return data.shot;
                           case 3: return data.dropBag;
                           case 4: return data.dropDesk;
                           case 5: return data.spiderSwap;
                       }
                    unsigned int x(666);
                    if (number < 0 || number > 5) return x;
                }

                TwoFloat getAxisData (int number)
                {
                    switch (number)
                    {
                        case 6: return TwoFloat(data.maxX, data.rngX);
                        case 7: return TwoFloat(data.maxY, data.rngY);
                    }
                    if (number != 6 || number != 7) return TwoFloat(13.f,13.f);
                }


            Status& getStatus() {return status; };
            void setStatus(Status inc_status) { status = inc_status; };

            //mark string for menu
            std::string& getCheckReport(int number) { if(number < 10 && number >= 0) return chekerReport[number]; };

            void stepStatus();

            bool checkGamePad_Data_File();
            void readGamePad_Data_File();
            void updateGamePad_Data_File();
            void updateGamePad_Data_File_By_Default();

    private:
        GamePad_Data data;
        std::string chekerReport[9];
            Status status;
            std::ofstream o_fs;

    //subfunctional
    private:
                //systemWritingByRecursion
                template<typename... Args>
                void exprtByRecursion(Args&... args)
                {
                    o_fs.close();
                    //std::cout << "plug" << std::endl;
                }

                template<typename Head, typename... Args>
                void exprtByRecursion(Head& head, Args&... args)
                {
                    o_fs << head << std::endl;
                    exprtByRecursion(args...);

                }

    public:
               void pushExprtByRecursion()
               {
                   o_fs.open("gamePad.data");
                   if (o_fs.is_open()) exprtByRecursion(data.port, data.start, data.shot, data.dropBag, data.dropDesk, data.spiderSwap,
                                                        data.maxX, data.maxY, data.rngX, data.rngY);
               }

};

#endif // JOYPAD_H
