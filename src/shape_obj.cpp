    #include "shape_obj.h"


    shape_obj::shape_obj(sf::Shape* shp):shape_obj_ptr{shp},transform_vec{},animate_vec{},
                                        utime{},border_size{},id{-1},reactor_h{nullptr},
                                        collidable{false},hide{false}
    {
        add_tr_func(border_update);
    }


    shape_obj::~shape_obj()
    {
    }


    void shape_obj::init(const sf::RenderTarget& rt, const reactor* re)
    {
        border_size = rt.getSize();
        reactor_h = re;
    }


    sf::Shape* shape_obj::shape_pointer()
    {
        return shape_obj_ptr.get();
    }


    void shape_obj::add_tr_func(const std::function<void(const sf::Event& ev, shape_obj& sh)>& f)
    {
        transform_vec.push_back(f);
    }


    void shape_obj::get_notification(const sf::Event& ev)
    {
        for(auto func:transform_vec)
        {
            func(ev, *this);
        }
    }


    void shape_obj::draw_on(sf::RenderTarget& rt) const
    {
        if(!hide)
        {
            rt.draw(*(shape_obj_ptr.get()));
        }
    }


    void shape_obj::check()
    {
        if(collidable)
        {
            reactor_h->collision_check(*this);
        }
    }


    void shape_obj::time_update(const sf::Time& t)
    {
        utime = t;
        animate();
    }


    const sf::Time& shape_obj::get_time()
    {
        return utime;
    }


    void shape_obj::add_anm_func( const std::pair<std::function<void(shape_obj& sh)>,const sf::Time>& p)
    {
        animate_vec.emplace_back(p,utime);
    }


    void shape_obj::animate()
    {
        if(!hide)
        {
            for(auto& anm: animate_vec)
            {
                std::function<void(shape_obj& sh)>& f = anm.first.first;
                const sf::Time& duration = anm.first.second;
                sf::Time& time_rec = anm.second;
                if(duration < utime - time_rec)
                {
                    time_rec = utime;
                    f(*this);
                }
            }
        }
    }


    const sf::Vector2u& shape_obj::get_border()
    {
        return border_size;
    }


    void shape_obj::set_id(int32_t i)
    {
        id = i;
    }


    int32_t shape_obj::get_id() const
    {
        return id;
    }


    sf::FloatRect shape_obj::get_local_bounds() const
    {
        return shape_obj_ptr.get()->getLocalBounds();
    }


    sf::FloatRect shape_obj::get_global_bounds() const
    {
        return shape_obj_ptr.get()->getGlobalBounds();
    }


    void shape_obj::collided_with(drawable& d)
    {

    }


    void shape_obj::collidable_opt(bool b)
    {
        collidable = b;
    }


    void shape_obj::hide_opt(bool b)
    {
        hide = b;
        if(b == false)
            collidable = b;  /// not sure!!
    }


    void shape_obj::border_update(const sf::Event& ev, shape_obj& sh)
    {
        if (ev.type == sf::Event::Resized)
        {
            sh.border_size.x = ev.size.width;
            sh.border_size.y = ev.size.height;
        }
    }





