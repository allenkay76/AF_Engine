#include "SDL/SDLGameTimer.h"

bool SDLGameTimer::Initialize()
{
    return true;
}


void SDLGameTimer::Shutdown()
{
}

void SDLGameTimer::start() 
{
    m_started = true;
    m_paused = false;
    m_startTicks = SDL_GetTicks();
    m_pausedTicks = 0;
}

void SDLGameTimer::stop()  
{
    m_started = false;
    m_paused = false;
    m_startTicks = 0;
    m_pausedTicks = 0;
}

void SDLGameTimer::pause()
{
    if(m_started && !m_paused)
    {
        m_paused = true;
        m_pausedTicks = SDL_GetTicks() - m_startTicks;
        m_startTicks = 0;
    }
}

void SDLGameTimer::unpause()
{
    if(m_paused)
    {
        m_paused = false;
        m_startTicks = SDL_GetTicks() - m_pausedTicks;
        m_pausedTicks = 0;
    }
}

unsigned int SDLGameTimer::getFrameTicks()
{
   
    return m_frameTicks;
}

/*--------------------------------------------------------------------------------
This function is called every frame
It calculates the average frame rate
It also calculates the number of frames per second
It also calculates the number of ticks (ms) for each frame
---------------------------------------------------------------------------------*/
void SDLGameTimer::countFrameTick()
{
    int time = 0;
    if(m_started)
    {
        if(m_paused)
        {
            time = m_pausedTicks;
        }
        else
        {
            time = SDL_GetTicks() - m_startTicks;
        }
    }

    m_countedFrames++;
    m_frameTicks = time;
    m_frameRate = 1000.0f / time;//m_countedFrames / (m_frameTicks / 1000.f);
}

float SDLGameTimer::getAvgFrameRate()
{
    return m_frameRate;
}

unsigned int SDLGameTimer::getCountedFrames()
{
    return m_countedFrames;
}

bool SDLGameTimer::isStarted()
{
    return m_started;
}

bool SDLGameTimer::isPaused()
{
    return m_paused && m_started;
}

SDLGameTimer::SDLGameTimer() : m_startTicks(0), m_pausedTicks(0), m_countedFrames(0), m_frameTicks(0), m_frameRate(0),m_paused(false), m_started(false)
{
    ITimerLocator::provide(this);
}

SDLGameTimer::~SDLGameTimer()
{
}
