#ifndef OBSRVR_H
#define OBSRVR_H
#include <SFML/Window.hpp>
#include <vector>
class observer
{
    public:
        virtual ~observer(){};
        virtual void get_notification(const sf::Event& ev) = 0;
    protected:

    private:
};

#endif // OBSRVR_H
