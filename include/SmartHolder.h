#ifndef SMARTHOLDER_H
#define SMARTHOLDER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>


namespace SPC_Fonts
{
    enum ID_Fonts
    {
       Consola,
       BigSquareDots,
       LAST
    };
}


namespace SPC_Texture
{
    enum ID_Enemys
    {
     Volf,
     Roster,
     Indian,
     Spider,
     HorseFly,
     Pipiter,
     BoxBag,
     ENUM_COUNT
    };

    enum ID_Covers
    {
        FrontCover,
        GameCone,
        Personage,
        SpiderPersonage,
        EndCover,
        LAST
    };
}

namespace SPC_SoundBuf
{
    enum ID_Sound
    {
        IndianBorn,
        IndianShort,
        AffectedG_Column,
        StartBullet,
        ItemDamage,
        IndianDie,
        boxBagBorn,
        pipiterBorn,
        byteBoxSquare,
        bytePipiterSquare,
        fightWolf,
        songRoster,
        itemDeath,
        spiderEat,
        spiderHungry,
        flyHorseFly,
        Enter,
        Select,
        Weldering1,
        Weldering2,
        Weldering3,
        GoSecure,
        ReturnSecure,
        ENUM_COUNT
    };

    enum ID_music
    {
        CW128,
        alarmSound,
        LAST
    };
}


class SmartHolder
{
    public:
        SmartHolder();
        virtual ~SmartHolder();

        //subfunctional
        void loadTextureEnemy();
        void loadSoundBuff();

        sf::Texture& getTextureEnemy(SPC_Texture::ID_Enemys id);
        void addTextureEnemy(SPC_Texture::ID_Enemys id, std::string filePath);

        sf::Texture& getCover(SPC_Texture::ID_Covers id);
        void addCover(SPC_Texture::ID_Covers id, std::string filePath);

        const sf::Vector2f& getSz(SPC_Texture::ID_Enemys id);

        sf::SoundBuffer& getSBuff(SPC_SoundBuf::ID_Sound id);
        void addSBuff (SPC_SoundBuf::ID_Sound id, std::string filePath);

        sf::Music& getMusic() { return music; };
        sf::Music& getAlarm() { return alarm; };

        sf::Font& getFont(SPC_Fonts::ID_Fonts id) {return fonts[id];};

    private:
        sf::Texture textureCover[SPC_Texture::ID_Covers::LAST];
        sf::Texture textureEnemy[SPC_Texture::ID_Enemys::ENUM_COUNT];
        std::map <SPC_Texture::ID_Enemys, sf::Vector2f> creatureSize;

        sf::Font fonts[SPC_Fonts::ID_Fonts::LAST];

        sf::Music music;
        sf::Music alarm;
        std::map <SPC_SoundBuf::ID_Sound, sf::SoundBuffer> buFF;

};

#endif // SMARTHOLDER_H
