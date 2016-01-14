#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <SFML/System.hpp>
#include <iostream>

class Time
{
public :
    Time();
    ~Time();
    int update(int angle);
private :
    sf::Clock clock;
    int elapsed1;
    int hour, day, month, year;
    bool change;
};

#endif // TIME_H_INCLUDED
