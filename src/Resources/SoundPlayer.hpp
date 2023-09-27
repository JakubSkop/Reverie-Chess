#pragma once
#include "SFML/Audio.hpp"
#include <map>
#include <list>
#include <memory>


class SoundPlayer{
    private:
        std::map<const std::string, const std::string> musicFiles; //Map between music titles and music file names
        sf::Music music; //Max 1 music Track playing at once
        std::string CurrentMusic;

        std::map<const std::string,std::unique_ptr<sf::SoundBuffer>> soundBuffers; //Map between sound names and the corresponding soundBuffer
        std::list<sf::Sound> sounds{}; //Max 8 different sounds playing at once, stored in this vector

        void ClearSounds();

    public:
        void AddSound(const std::string &soundName, const std::string &filename); //Loads a new soundBuffer from a file
        void AddMusic(std::string musicName, std::string filename); //Loads a new music track from a file
        void PlayMusic(const std::string &name);
        void PlaySound(const std::string &name);
        void SetVolume(int volume);
        const std::string& GetCurrentMusic() const;

};