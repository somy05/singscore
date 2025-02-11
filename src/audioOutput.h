#ifndef GAME_AUDIO_OUTPUT_H
#define GAME_AUDIO_OUTPUT_H
#include <SFML/Audio.hpp>
#include <string>

class audioOutput
{
private:
    sf::Music music;
public:
    bool load(const std::string &filename);
    void play();
    void stop();
};







#endif //GAME_AUDIO_OUTPUT_H