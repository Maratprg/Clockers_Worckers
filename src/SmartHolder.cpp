#include "SmartHolder.h"

SmartHolder::SmartHolder()
{
  /*BoxBagW78_H200.png
    HFlyW178_H160.png
    IndianW174_H167_Vertical.png
    PipiterW90_H135.png
    RosterW121(5)_H208(5).png
    SpiderW257_H315.png
    WolfW149_H200.png */

    //ctor
    this->addTextureEnemy(SPC_Texture::ID_Enemys::Volf, "Media/WolfW149_H200.png");
    this->addTextureEnemy(SPC_Texture::ID_Enemys::Roster, "Media/RosterW121(5)_H208(5).png");
    this->addTextureEnemy(SPC_Texture::ID_Enemys::Indian, "Media/IndianW174_H167_Vertical.png");
    this->addTextureEnemy(SPC_Texture::ID_Enemys::Spider, "Media/SpiderW257_H315.png");
    this->addTextureEnemy(SPC_Texture::ID_Enemys::HorseFly, "Media/HFlyW178_H160.png");
    this->addTextureEnemy(SPC_Texture::ID_Enemys::Pipiter, "Media/PipiterW90_H135.png");
    this->addTextureEnemy(SPC_Texture::ID_Enemys::BoxBag, "Media/BoxBagW78_H200.png");

    //manage size map
    creatureSize.insert(std::make_pair(SPC_Texture::ID_Enemys::Volf, sf::Vector2f(149,200)));
    creatureSize.insert(std::make_pair(SPC_Texture::ID_Enemys::Roster, sf::Vector2f(121,208)));
    creatureSize.insert(std::make_pair(SPC_Texture::ID_Enemys::Indian, sf::Vector2f(174,167)));
    creatureSize.insert(std::make_pair(SPC_Texture::ID_Enemys::Spider, sf::Vector2f(257,315)));
    creatureSize.insert(std::make_pair(SPC_Texture::ID_Enemys::HorseFly, sf::Vector2f(178,160)));
    creatureSize.insert(std::make_pair(SPC_Texture::ID_Enemys::Pipiter, sf::Vector2f(90,135)));
    creatureSize.insert(std::make_pair(SPC_Texture::ID_Enemys::BoxBag, sf::Vector2f(78,200)));


        //manage game music
        try
        {
            music.openFromFile("Media/audio/userSound/CW128.ogg");
        }
        catch(std::runtime_error& e)
        {
            std::cout << "Fail load Music " << e.what() << std::endl;
        }

        //manage clock alarm
        try
        {
            alarm.openFromFile("Media/audio/userSound/alarmSound.ogg");
        }
        catch(std::runtime_error& e)
        {
            std::cout << "Fail load Music " << e.what() << std::endl;
        }


        //manage sounds buffer map (like a not Make Pair Style)
        addSBuff(SPC_SoundBuf::ID_Sound::IndianBorn, "Media/audio/0-indianBorn.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::IndianShort, "Media/audio/1-indianShort.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::AffectedG_Column, "Media/audio/2-affectedG_Column.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::StartBullet, "Media/audio/3-startBullet.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::ItemDamage, "Media/audio/4-itemDamage.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::IndianDie, "Media/audio/5-indianDie.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::boxBagBorn, "Media/audio/6-boxBagBorn.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::pipiterBorn, "Media/audio/8-pipiterBorn.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::byteBoxSquare, "Media/audio/10-byteBoxSquare.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::bytePipiterSquare, "Media/audio/11-bytePipiterSquare.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::fightWolf, "Media/audio/12-fightWolf.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::songRoster, "Media/audio/13-songRoster.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::itemDeath, "Media/audio/16-itemDeath.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::spiderEat, "Media/audio/18-spiderEat.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::spiderHungry, "Media/audio/19-spiderHungry.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::flyHorseFly, "Media/audio/20-flyHorseFly.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::Enter, "Media/audio/21-Enter.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::Select, "Media/audio/23-Select.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::Weldering1, "Media/audio/24-weldering1.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::Weldering2, "Media/audio/25-weldering2.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::Weldering3, "Media/audio/26-weldering3.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::GoSecure, "Media/audio/27-GoSecure.ogg");
        addSBuff(SPC_SoundBuf::ID_Sound::ReturnSecure, "Media/audio/28-ReturnSecure.ogg");


        //C:\Users\CodeBlockProjects\Clokers-Workers\Media\covers
        //block of cover upload
        addCover(SPC_Texture::ID_Covers::FrontCover, "Media/covers/FrontCover.png");
        addCover(SPC_Texture::ID_Covers::GameCone, "Media/covers/GameCone.png");
        addCover(SPC_Texture::ID_Covers::Personage, "Media/covers/Personage.png");
        addCover(SPC_Texture::ID_Covers::SpiderPersonage, "Media/covers/spiderPersonage.png");
        addCover(SPC_Texture::ID_Covers::EndCover, "Media/covers/EndCover.png");

        //addFonts
        try
        {
            fonts[SPC_Fonts::Consola].loadFromFile("consola.ttf");
            fonts[SPC_Fonts::BigSquareDots].loadFromFile("Media/covers/bigsquaredots.ttf");

        }
        catch (std::system_error& e)
        {
            std::cout << "Falling font download " << e.what() << std::endl;
        }

}

SmartHolder::~SmartHolder()
{
    //dtor
}

void SmartHolder::addTextureEnemy(SPC_Texture::ID_Enemys id, std::string filePath)
{
    textureEnemy[id].loadFromFile(filePath);
}

sf::Texture& SmartHolder::getTextureEnemy(SPC_Texture::ID_Enemys id)
{
    return textureEnemy[id];
}

void SmartHolder::addCover(SPC_Texture::ID_Covers id, std::string filePath)
{
    textureCover[id].loadFromFile(filePath);
}

sf::Texture& SmartHolder::getCover(SPC_Texture::ID_Covers id)
{
    return textureCover[id];
}

const sf::Vector2f& SmartHolder::getSz(SPC_Texture::ID_Enemys id)
{
    std::map<SPC_Texture::ID_Enemys, sf::Vector2f>::iterator it;
    it = creatureSize.find(id);
    return it->second;
}


sf::SoundBuffer& SmartHolder::getSBuff(SPC_SoundBuf::ID_Sound id)
{
    std::map<SPC_SoundBuf::ID_Sound, sf::SoundBuffer>::iterator it;
    it = buFF.find(id);
    return it->second;
}

void SmartHolder::addSBuff (SPC_SoundBuf::ID_Sound id, std::string filePath)
{
   sf::SoundBuffer add;
   add.loadFromFile(filePath);
   buFF[id] = add;
}

