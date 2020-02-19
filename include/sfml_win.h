#ifndef SFML_WIN_H
#define SFML_WIN_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <functional>
#include "obsrvr.h"
#include "drawable.h"
#include "alive.h"
#include "reactor.h"
class sfml_win:public observer,public reactor
{
    public:
        sfml_win(int w, int h, std::string win_name,sf::Color clr = sf::Color::Black,uint32_t atr = sf::Style::Default,
                int cntx_setting = 32);
        virtual ~sfml_win();
        void run_main_loop();
        int register_observer(observer& obs);
        int register_drawable(drawable& drw);
        int register_alive(alive& al);
        void init_all();
        void clear_all(sf::RenderTarget& rt);
        void display_all();
        void draw_all(sf::RenderTarget& rt);
        void notify_all(const sf::Event& e);
        void update_all(const sf::Time& t);
        void check_all();
        void collision_check(drawable& d) const override;
        void swap_drawables(size_t i, size_t j);
        void clock_reset();
        void close();
        void get_notification(const sf::Event& ev) override;
        void add_event_handler(const std::function<void(const sf::Event& ev,sfml_win& w)>& f);
    protected:

    private:
    sf::RenderWindow win;
    std::vector<std::reference_wrapper<observer>> observers_list;
    std::vector<std::reference_wrapper<drawable>> drawables_list;
    std::vector<std::reference_wrapper<alive>> alive_list;
    std::vector<std::function<void(const sf::Event& ev,sfml_win& w)>> event_handler_vec;
    sf::Color win_back_color;
    sf::Clock clk;
    static void win_close_event_handler(const sf::Event& ev,sfml_win& w);
    static void win_resize_event_handler(const sf::Event& ev,sfml_win& w);
};

#endif // SFML_WIN_H
