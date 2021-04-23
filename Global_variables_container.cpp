#include "Global_variables_container.h"

Global_variables_container::Global_variables_container(SDL_Window* window, SDL_Surface*  screen, SDL_Renderer*  renderer)
{
    m_window = window;
    m_screen = screen;
    m_renderer = renderer;
    m_frame_counter = 0;
    m_difficulty = INTERMEDIATE;
    m_cursor_pos[X] = 0;
    m_cursor_pos[Y] = 0;
}

Global_variables_container::~Global_variables_container()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
}

SDL_Window* Global_variables_container::window()
{
    return m_window;
}

SDL_Surface* Global_variables_container::screen()
{
    return m_screen;
}

SDL_Renderer* Global_variables_container::renderer()
{
    return m_renderer;
}

void Global_variables_container::update_frame(){m_frame_counter ++;}

void Global_variables_container::reset_frame(){m_frame_counter = 0;}

int Global_variables_container::get_frame(){return m_frame_counter;}

void Global_variables_container::set_difficulty(int new_difficulty){m_difficulty = new_difficulty;}

int Global_variables_container::get_difficulty(){return m_difficulty;}

void Global_variables_container::set_cursor_pos(int x, int y){m_cursor_pos[X] = x;m_cursor_pos[Y] = y;}

int Global_variables_container::get_cursor_pos(int x_or_y){return m_cursor_pos[x_or_y];}
