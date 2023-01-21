#include "JoyPad.h"

JoyPad::JoyPad()
{
    //ctor
    //set status
    status = READY;

    //default axis data set
    data.maxX = 100.f;
    data.maxY = 100.f;
    data.rngX = 15.f;
    data.rngY = 15.f;

    //set checkerReportStrings
    chekerReport[0] = "Seeking port...(press button one time)...";
    chekerReport[1] = "Turn to check X-axis... ";
    chekerReport[2] = "Turn to check Y-axis... ";
    chekerReport[3] = "Press Start button... ";
    chekerReport[4] = "Press Shot button... ";
    chekerReport[5] = "Press DrobBag button... ";
    chekerReport[6] = "Press DropDesk button... ";
    chekerReport[7] = "Press spiderSwap button... ";
    chekerReport[8] = "Complete! Good! Wait...";

    if (!checkGamePad_Data_File()) this->updateGamePad_Data_File_By_Default();
    readGamePad_Data_File();

     /*std::cout << "pad data " << data.port << " " << data.start << " " << data.shot << " " << data.dropBag << " "
                << data.dropDesk << " " << data.spiderSwap << " " << data.maxX << " " << data.maxY << " "
                 << data.rngX << " " << data.rngY << std::endl;*/

}

JoyPad::~JoyPad()
{
    //dtor
}

bool JoyPad::checkGamePad_Data_File()
{
    std::ifstream in_f("gamePad.data");
    if(in_f.is_open()) { in_f.close(); return true; }
    else
    {
    in_f.close();
    return false;
    };
}

void JoyPad::readGamePad_Data_File()
{
    std::ifstream in_f("gamePad.data");
    if(in_f.is_open())
    {
        in_f >> data.port >> data.start >> data.shot >> data.dropBag >> data.dropDesk >> data.spiderSwap
              >> data.maxX >> data.maxY >> data.rngX >> data.rngY;
     in_f.close();
    }
    else
    {
      in_f.close();
      std::cout << "SORRY but i cant find the gamePad.data file!" << std::endl;
    }
}

void JoyPad::updateGamePad_Data_File()
{
   if(checkGamePad_Data_File())
        {
        std::ofstream out_f("gamePad.data");
        if (out_f.is_open() && status == READY)
            {
            out_f << data.port << std::endl;
            out_f << data.start << std::endl;
            out_f << data.shot << std::endl;
            out_f << data.dropBag << std::endl;
            out_f << data.dropDesk << std::endl;
            out_f << data.spiderSwap << std::endl;
            out_f << data.maxX << std::endl;
            out_f << data.maxY << std::endl;
            out_f << data.rngX << std::endl;
            out_f << data.rngY << std::endl;
            }//end of if
        out_f.close();
        }//end of if
}

void JoyPad::updateGamePad_Data_File_By_Default()
{
        // making game pad struct values by default
        data.port = 0;
        data.start = 9;
        data.shot = 3;
        data.dropBag = 2;
        data.dropDesk = 1;
        data.spiderSwap = 0;
        data.maxX = 89.f;
        data.maxY = 89.f;
        data.rngX = 15.f;
        data.rngY = 15.f;

            // making file if it dose not exist
            std::ofstream out_f("gamePad.data");
            if (out_f.is_open() && status == READY)
            {
            out_f << data.port << std::endl;
            out_f << data.start << std::endl;
            out_f << data.shot << std::endl;
            out_f << data.dropBag << std::endl;
            out_f << data.dropDesk << std::endl;
            out_f << data.spiderSwap << std::endl;
            out_f << data.maxX << std::endl;
            out_f << data.maxY << std::endl;
            out_f << data.rngX << std::endl;
            out_f << data.rngY << std::endl;
            }//end of if
            out_f.close();
}


void JoyPad::stepStatus()
{
   if (status == Status::READY) status = Status::SEEK_PORT;
   else status = static_cast<Status>(static_cast<int>(status)+1);
}
