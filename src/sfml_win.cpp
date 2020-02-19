#include "sfml_win.h"
#include <algorithm>
sfml_win::sfml_win(int w, int h, std::string win_name, sf::Color clr,uint32_t atr, int cntx_setting):win{sf::VideoMode(w,h), win_name, atr, sf::ContextSettings(cntx_setting)},
                                                                                                     observers_list{},drawables_list{},alive_list{}, event_handler_vec{},
                                                                                                     win_back_color{clr}, clk{}
{
    register_observer(*this);  /// class subscribes itself

    add_event_handler(win_close_event_handler);
    add_event_handler(win_resize_event_handler);

    glEnable(GL_TEXTURE_2D);
    sf::ContextSettings settings;
    win.setVerticalSyncEnabled(true);
    win.setActive(true);
}

sfml_win::~sfml_win()
{

}

void sfml_win::init_all()
{
    std::for_each( std::begin(drawables_list), std::end(drawables_list), [this]( drawable& d){ d.init(win,this);});
}

void sfml_win::clear_all(sf::RenderTarget& rt)
{
    rt.clear(win_back_color);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void sfml_win::display_all()
{
    win.display();
}

void sfml_win::draw_all(sf::RenderTarget& rt)
{
    std::for_each( std::begin(drawables_list), std::end(drawables_list), [&rt]( drawable& d){ d.draw_on(rt); });
}

void sfml_win::notify_all(const sf::Event& e)  /// class as a subject
{
    std::for_each( std::begin(observers_list), std::end(observers_list), [&e]( observer& ob){ ob.get_notification(e); });
}

void sfml_win::update_all(const sf::Time& t)
{
    std::for_each( std::begin(alive_list), std::end(alive_list), [&t]( alive& al){al.time_update(t);});
}

void sfml_win::check_all()
{
    std::for_each( std::begin(drawables_list), std::end(drawables_list), []( drawable& dr){dr.check();});
}

void sfml_win::run_main_loop()
{
    while( win.isOpen())
    {
        sf::Event event;
        update_all(clk.getElapsedTime());

        while(win.pollEvent(event))
        {
            notify_all(event);
        }

        check_all();
        clear_all(win);
        draw_all(win);
        display_all();
    }
}

int sfml_win::register_observer(observer& obs)
{
    observers_list.push_back(obs);
    return observers_list.size()-1;
}

int sfml_win::register_drawable(drawable& drw)
{
    drawables_list.push_back(drw);
    drw.set_id(drawables_list.size()-1);
    return drawables_list.size()-1;
}

int sfml_win::register_alive(alive& al)
{
    alive_list.push_back(al);
    return alive_list.size()-1;
}

void sfml_win::close()
{
     win.setActive(false);
     win.close();
}

void sfml_win::get_notification(const sf::Event& ev)  /// class as an observer
{
    for(auto func: event_handler_vec)
    {
        func(ev, *this);
    }
}

void sfml_win::clock_reset()
{
    clk.restart();
}

void sfml_win::swap_drawables(size_t i, size_t j)
{
    if(i==j || drawables_list.size()-1<i || drawables_list.size()-1<j )
        return;
    else
        {
            int32_t iid = drawables_list[i].get().get_id();
            int32_t jid = drawables_list[j].get().get_id();

            drawables_list[i].get().set_id(jid);
            drawables_list[j].get().set_id(iid);

            std::swap(drawables_list[i],drawables_list[j]);
        }
}

void sfml_win::add_event_handler(const std::function<void(const sf::Event& ev,sfml_win& w)>& f)
{
    event_handler_vec.push_back(f);
}

void sfml_win::win_close_event_handler(const sf::Event& ev,sfml_win& w)
{
    if(ev.type == sf::Event::Closed)
    {
        w.close();
    }
}

void sfml_win::win_resize_event_handler(const sf::Event& ev,sfml_win& w)
{
    if (ev.type == sf::Event::Resized)
    {
        glViewport(0, 0, ev.size.width, ev.size.height);
    }
}

void sfml_win::collision_check(drawable& d) const
{

    sf::FloatRect obj_rect = d.get_global_bounds();
    for(auto& other_d :drawables_list)
    {
        if(d.get_id()!= other_d.get().get_id())
        {
            if(obj_rect.intersects(other_d.get().get_global_bounds()))
            {
                d.collided_with(other_d);
            }
        }
    }
}



