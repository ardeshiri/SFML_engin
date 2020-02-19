#include <iostream>
#include "sfml_win.h"
#include "shape_obj.h"
#include <cmath>
using namespace std;



class behavior
{
int a = 1;
int b = 0;
int speed = 15;

public:
    void operator()(shape_obj& sh)
    {
        auto pos = sh.shape_pointer()->getPosition();
        sf::Vector2u bordr =  sh.get_border();
        if((pos.y+(a*speed) > bordr.y) || ( pos.y < 0) )
        {
            a *= -1;
        }
        if( (pos.x+speed > bordr.x) || (pos.x < 0) )
        {
            a *= -1;
            speed *= -1;
        }
        sh.shape_pointer()->setPosition(pos.x+speed,pos.y+speed*a+b);
    }
};




int main()
{
    shape_obj obj(new sf::CircleShape(70.f));
    obj.shape_pointer()->setFillColor(sf::Color::Red);
    behavior bhv{};
    sfml_win sw{1200,800,"mywin"};

    obj.add_anm_func(make_pair(bhv,sf::milliseconds(1)));

    sw.register_observer(obj);
    sw.register_drawable(obj);
    sw.register_alive(obj);
////////////////////////////////// 0
    sw.init_all();  /// 1
    sw.run_main_loop();  /// 2
    return 0;
}
