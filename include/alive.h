#ifndef ALIVE_H
#define ALIVE_H


class alive
{
    public:
        alive(){}
        virtual ~alive(){}
        virtual void time_update(const sf::Time& t) = 0;

    protected:

    private:
};

#endif // ALIVE_H
