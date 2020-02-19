#ifndef REACTOR_H
#define REACTOR_H
#include "drawable.h"
class drawable;
class reactor
{
    public:
        reactor(){};
        virtual ~reactor(){};
        virtual void collision_check(drawable& d) const = 0;

    protected:

    private:
};

#endif // REACTOR_H
