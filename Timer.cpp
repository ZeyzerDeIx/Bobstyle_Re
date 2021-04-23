#include "Timer.h"

using namespace std;

Timer::Timer()
{
    m_last_time_save = SDL_GetTicks();
}

int Timer::get_elapsed_time()
{
    return SDL_GetTicks() - m_last_time_save;
}

int Timer::get_and_restart()
{
    int elapsed_time(this->get_elapsed_time());

    this->restart();

    return elapsed_time;
}

void Timer::restart()
{
    m_last_time_save = SDL_GetTicks();
}
