#ifndef GAME_AUDIO_OUTPUT_H
#define GAME_AUDIO_OUTPUT_H
#include <SFML/Audio.hpp>
#include <string>

class audioOutput
{
private:
    sf::Music music;
    bool isPlaying;
    
public:
    audioOutput();
    bool load(const std::string &filename);
    void play();
    void stop();
    void pause();
    void resume();
    bool getIsPlaying() const;
    float getPlayingOffset() const; // Get current playback position in seconds
    float getDuration() const;      // Get total duration in seconds
    sf::Music::Status getStatus() const;
};

#endif //GAME_AUDIO_OUTPUT_H