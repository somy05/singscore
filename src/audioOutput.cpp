#include "audioOutput.h"
bool audioOutput::load(const std::string &filename)
{
    return music.openFromFile(filename);
}

void audioOutput::play()
{
    music.play();
}

void audioOutput::stop()
{
    music.stop();
}