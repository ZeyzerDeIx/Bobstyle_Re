#include "Text_boxe.h"

using namespace std;

Text_boxe::Text_boxe(Global_variables_container* GVC, string text_longer, int parameter): Menu(GVC, 0, 1, screenshot(GVC, 150))
{
    m_GVC = GVC;

    m_text_longer = text_longer;

    int i(0);

    m_size[W] = 0;

    while(i<text_longer.size())
    {
        string line("");
        while(text_longer[i] != ENTER)
        {
            line += text_longer[i];
            i++;
        }
        i++;
        m_text_displayers.push_back(new Text(GVC, line));
        m_text_displayers.back()->change_text("SAME", false, 255, 255, 255);

        if(m_size[W] < m_text_displayers.back()->get_size(W))
        {
            m_size[W] = m_text_displayers.back()->get_size(W);
        }
    }

    m_size[H] = (m_text_displayers[0]->get_size(H)+5)*m_text_displayers.size()-5;

    for(int i=0 ; i< m_text_displayers.size() ; i++)
    {
        if(parameter == LEFT)
        {
            m_text_displayers[i]->set_pos(GVC->screen()->w/2 - m_size[W]/2 + m_text_displayers[i]->get_size(W)/2,
                                          GVC->screen()->h/2 - m_size[H]/2 + m_text_displayers[i]->get_size(H)/2 + i*(m_text_displayers[i]->get_size(H)+5));
        }
        else if(parameter == RIGHT)
        {
            m_text_displayers[i]->set_pos(GVC->screen()->w/2 + m_size[W]/2 - m_text_displayers[i]->get_size(W)/2,
                                          GVC->screen()->h/2 - m_size[H]/2 + m_text_displayers[i]->get_size(H)/2 + i*(m_text_displayers[i]->get_size(H)+5));
        }
        else
        {
            m_text_displayers[i]->set_pos(GVC->screen()->w/2,
                                          GVC->screen()->h/2 - m_size[H]/2 + m_text_displayers[i]->get_size(H)/2 + i*(m_text_displayers[i]->get_size(H)+5));
        }
    }
}

Text_boxe::~Text_boxe()
{
    for(int i=0 ; i<m_text_displayers.size() ; i++)
    {
        delete m_text_displayers[i];
    }
}

void Text_boxe::display()
{
    draw_box(m_GVC, m_size[W]+10, m_size[H]+10, 10);

    for(int i=0 ; i<m_text_displayers.size() ; i++)
    {
        m_text_displayers[i]->display();;
    }
}

void Text_boxe::click(int up_or_down)
{
    m_done = true;
}
