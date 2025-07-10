#include "audioOutput.h"

audioOutput::audioOutput() : isPlaying(false) {
}

bool audioOutput::load(const std::string &filename)
{
    return music.openFromFile(filename);
}

void audioOutput::play()
{
    music.play();
    isPlaying = true;
}

void audioOutput::stop()
{
    music.stop();
    isPlaying = false;
}

void audioOutput::pause()
{
    music.pause();
    isPlaying = false;
}

void audioOutput::resume()
{
    music.play();
    isPlaying = true;
}

bool audioOutput::getIsPlaying() const
{
    return music.getStatus() == sf::Music::Playing;
}

float audioOutput::getPlayingOffset() const
{
    return music.getPlayingOffset().asSeconds();
}

float audioOutput::getDuration() const
{
    return music.getDuration().asSeconds();
}

sf::Music::Status audioOutput::getStatus() const
{
    return music.getStatus();
}