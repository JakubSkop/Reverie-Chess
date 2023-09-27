#include "SoundPlayer.hpp"



void SoundPlayer::AddMusic(std::string musicName, std::string filename){
    musicFiles.emplace(std::make_pair(musicName, filename));
}

void SoundPlayer::AddSound(const std::string &soundName, const std::string &filename){
    // Declare a new sound buffer
    auto buffer = std::make_unique<sf::SoundBuffer>();
 
    // Load it from a file
    if (!buffer->loadFromFile(filename))
    {
        throw std::runtime_error("Couldn't Load sound file");
    }

    //Save buffer in map //unique_ptr has to be moved, not copied
    soundBuffers.emplace(std::make_pair(soundName, std::move(buffer)));
    
}

void SoundPlayer::ClearSounds(){
    sounds.remove_if([](sf::Sound sound){return (sound.getStatus() == sf::Sound::Stopped);});
}

void SoundPlayer::PlaySound(const std::string &name){
    ClearSounds();
    if (sounds.size() <= 16){
        // Create a sound source and bind it to the buffer
        sf::Sound sound1;
        sound1.setBuffer(*soundBuffers.at(name));

        //Add to sounds Vector
        sounds.push_back(sound1);

        // Play the sound
        sounds.back().play();
    }
}

void SoundPlayer::PlayMusic(const std::string &name){
    music.openFromFile(musicFiles.at(name));
    music.setLoop(true);
    music.play();
    CurrentMusic = name;
}

const std::string& SoundPlayer::GetCurrentMusic() const{
    return CurrentMusic;
}

void SoundPlayer::SetVolume(int volume){
    music.setVolume(volume);
}