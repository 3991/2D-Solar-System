#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "process.h"

#define _WINDOW_WIDTH 800
#define _WINDOW_HEIGHT 600

#define _PI 3.14159265

#define _SUN_RADIUS_KM 695500.f
#define _SUN_X_PX 0.f
#define _SUN_Y_PX 0.f
#define _SUN_MERCURY_DISTANCE_KM 58000.f

#define _MERCURY_RADIUS_KM 400000.f

int main()
{
    sf::RenderWindow window(sf::VideoMode(_WINDOW_WIDTH, _WINDOW_HEIGHT), "SFML works!");

    sf::View view1(sf::FloatRect(0, 0, _WINDOW_WIDTH, _WINDOW_HEIGHT));
    sf::View minimap(sf::FloatRect(0, 0, _WINDOW_WIDTH, _WINDOW_HEIGHT));
    minimap.setViewport(sf::FloatRect(0.1f, 0.1f, 0.75f, 0.75f));

   sf::RectangleShape rectangle(sf::Vector2f(_WINDOW_WIDTH*0.75, _WINDOW_HEIGHT*0.75));
   rectangle.setPosition(sf::Vector2f(_WINDOW_WIDTH*0.10,_WINDOW_HEIGHT*0.10));
   rectangle.setOutlineColor(sf::Color::Black);
   rectangle.setOutlineThickness(5.f);

    //minimap.zoom(50000.f);
    minimap.zoom(500.f);

    bool change = false;
    bool minimapview = false;

    sf::Clock clock;
    int elapsed1 = 0;

    int hour = 0, day = 1, month = 1, year = 1;


    sf::CircleShape sun(Process().translateKmInPixel(_SUN_RADIUS_KM));
    //sun.setPosition({_SUN_X_PX/*-Process().translateKmInPixel(_SUN_RADIUS_KM)*/, _SUN_Y_PX/*-Process().translateKmInPixel(_SUN_RADIUS_KM)*/});
    sun.setOrigin({_SUN_X_PX+Process().translateKmInPixel(_SUN_RADIUS_KM), _SUN_Y_PX+Process().translateKmInPixel(_SUN_RADIUS_KM)});
    sun.setPosition({_SUN_X_PX/*-Process().translateKmInPixel(_SUN_RADIUS_KM)*/, _SUN_Y_PX/*-Process().translateKmInPixel(_SUN_RADIUS_KM)*/});
    sun.setFillColor(sf::Color::Yellow);


    sf::CircleShape ecliptic(Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM));
    //ecliptic.setPosition({_SUN_X_PX/*-Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM)*/, _SUN_Y_PX/*-Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM)*/});
    ecliptic.setOrigin({_SUN_X_PX+Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM), _SUN_Y_PX+Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM)});
    ecliptic.setPosition({_SUN_X_PX/*-Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM)*/, _SUN_Y_PX/*-Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM)*/});
    ecliptic.setFillColor(sf::Color::Blue);

    sf::CircleShape mercury(Process().translateKmInPixel(_MERCURY_RADIUS_KM));
    mercury.setOrigin({mercury.getLocalBounds().width/2, mercury.getLocalBounds().height/2});
    mercury.setFillColor(sf::Color::Black);
    float x, y;
    int angle = 0;
    x = _SUN_X_PX/*-Process().translateKmInPixel(_SUN_RADIUS_KM)*/ + (Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM))*cos(angle * _PI / 180.0);
    y = _SUN_Y_PX/*-Process().translateKmInPixel(_SUN_RADIUS_KM)*/ + (Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM))*sin(angle * _PI / 180.0);
    mercury.setPosition({x, y});


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                view1.move(-10, 0);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                view1.move(10, 0);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                view1.move(0, -10);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                view1.move(0, 10);
            }


        }



if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                minimapview = true;
            }else{
                minimapview = false;
            }
        if(elapsed1 == 7){
            change = true;
            hour++;
            if(hour == 24){
                    hour = 0;
                    day++;
            }
            if(day == 31){
                day = 1;
                month++;
            }
            if(month == 12){
                year++;
            }



            if(angle<360){
                angle += 15;
            }else{
                angle=0;
            }
            x= _SUN_X_PX/*-Process().translateKmInPixel(_SUN_RADIUS_KM)*/ + (Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM))*cos(angle * _PI / 180.0);
            y = _SUN_Y_PX/*-Process().translateKmInPixel(_SUN_RADIUS_KM)*/ + (Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM))*sin(angle * _PI / 180.0);

            mercury.setPosition({x, y});
            elapsed1 = 0;
            clock.restart();
        }
        elapsed1 = (int)clock.getElapsedTime().asSeconds();

        if(change){
            std::cout << "Date:" << day << "/" << month << "/" << year << std::endl;
            std::cout << "Hour:" << hour << ".00" << std::endl;
            change = false;
        }



        window.clear(sf::Color::White);

        window.setView(view1);
        window.draw(sun);
        window.draw(mercury);

        if(!minimapview){
            window.draw(rectangle);
            window.setView(minimap);
            window.draw(ecliptic);
            window.draw(sun);
            window.draw(mercury);
        }


        window.display();
    }

    return 0;
}

void open(){
}
