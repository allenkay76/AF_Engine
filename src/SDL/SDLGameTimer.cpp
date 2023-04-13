#include "SDL/SDLGameTimer.h"

bool SDLGameTimer::Initialize()
{
    return false;
}

void SDLGameTimer::Shutdown()
{
}

void SDLGameTimer::start() 
{
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();
    pausedTicks = 0;
}

void SDLGameTimer::stop()  
{
    started = false;
    paused = false;
    startTicks = 0;
    pausedTicks = 0;
}

void SDLGameTimer::pause()
{
    if(started && !paused)
    {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void SDLGameTimer::unpause()
{
    if(paused)
    {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

int SDLGameTimer::getTicks() const
{
    int time = 0;
    if(started)
    {
        if(paused)
        {
            time = pausedTicks;
        }
        else
        {
            time = SDL_GetTicks() - startTicks;
        }
    }
    return time;
}

bool SDLGameTimer::isStarted()
{
    return started;
}

bool SDLGameTimer::isPaused()
{
    return paused && started;
}

SDLGameTimer::SDLGameTimer() : startTicks(0), pausedTicks(0), paused(false), started(false)
{

}

SDLGameTimer::~SDLGameTimer()
{
}
