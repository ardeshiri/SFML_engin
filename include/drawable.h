#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include "reactor.h"
class reactor;
class drawable
{
    public:
        virtual ~drawable(){};
        virtual void init(const sf::RenderTarget& rt, const reactor* re) = 0;
        virtual void draw_on(sf::RenderTarget& rt) const = 0;
        virtual sf::FloatRect get_local_bounds() const = 0;
        virtual sf::FloatRect get_global_bounds() const = 0;
        virtual void check() = 0;
        virtual void collided_with(drawable& d) = 0;
        virtual void hide_opt(bool b) = 0;
        virtual void collidable_opt(bool b) = 0;
        virtual void set_id(int32_t) = 0;
        virtual int32_t get_id() const = 0;
    protected:

    private:
};

#endif // DRAWABLE_H
