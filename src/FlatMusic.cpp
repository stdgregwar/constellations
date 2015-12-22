#include "../include/FlatMusic.h"

FlatMusic::FlatMusic(std::string file)
{
    if(!mMusic.openFromFile(file))
        throw std::runtime_error("Could not open file " + file);

    mMusic.setLoop(true);
}

void FlatMusic::update(float delta_s)
{
    return;
}

void FlatMusic::play()
{
    mMusic.play();
}

void FlatMusic::pause()
{
    mMusic.pause();
}

void FlatMusic::stop()
{
    mMusic.stop();
}

void FlatMusic::setVolume(float volume)
{
    mMusic.setVolume(volume);
}

FlatMusic::~FlatMusic()
{

}

