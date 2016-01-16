#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

#include "Process.h"
#include "Player.h"
#include "Time.h"

#define _WINDOW_WIDTH 800
#define _WINDOW_HEIGHT 600

#define _PI 3.14159265

#define _SUN_RADIUS_KM 695500.f
#define _SUN_X_PX 0.f
#define _SUN_Y_PX 0.f
#define _SUN_MERCURY_DISTANCE_KM 58000.f
#define _SUN_VENUS_DISTANCE_KM 108000.f
#define _SUN_EARTH_DISTANCE_KM 150000.f

#define _MERCURY_RADIUS_KM 2440.f

#define _VENUS_RADIUS_KM 6050.f

#define _EARTH_RADIUS_KM 6378.f

int main()
{
    sf::RenderWindow window(sf::VideoMode(_WINDOW_WIDTH, _WINDOW_HEIGHT), "2S Solar System");
    window.setFramerateLimit(60);


    // **************************** VIEW ****************************
    sf::View view1(sf::FloatRect(0, 0, _WINDOW_WIDTH, _WINDOW_HEIGHT));
    sf::View view2(sf::FloatRect(0, 0, _WINDOW_WIDTH, _WINDOW_HEIGHT));
    sf::View minimap(sf::FloatRect(0, 0, _WINDOW_WIDTH, _WINDOW_HEIGHT));
    minimap.setViewport(sf::FloatRect(0.1f, 0.1f, 0.75f, 0.75f));

    view1.zoom(200.f);
    minimap.zoom(500.f);
    bool minimapview = false;



    sf::RectangleShape rectangle(sf::Vector2f(_WINDOW_WIDTH*0.75, _WINDOW_HEIGHT*0.75));
    rectangle.setPosition(sf::Vector2f(_WINDOW_WIDTH*0.10,_WINDOW_HEIGHT*0.10));
    rectangle.setOutlineColor(sf::Color(0,0,255,100));
    rectangle.setOutlineThickness(30.f);
    //rectangle.setFillColor(sf::Color::Blue);



    // **************************** PLANETS ****************************
    int angle = 0;
    float x, y, newX, newY;

    sf::CircleShape sun(Process().translateKmInPixel(_SUN_RADIUS_KM));
    sun.setOrigin({_SUN_X_PX+Process().translateKmInPixel(_SUN_RADIUS_KM), _SUN_Y_PX+Process().translateKmInPixel(_SUN_RADIUS_KM)});
    sun.setPosition({_SUN_X_PX, _SUN_Y_PX});
    sun.setFillColor(sf::Color::Yellow);


    sf::CircleShape mercury(Process().translateKmInPixel(_MERCURY_RADIUS_KM));
    mercury.setOrigin({mercury.getLocalBounds().width/2, mercury.getLocalBounds().height/2});
    mercury.setFillColor(sf::Color::Black);
    x = _SUN_X_PX + (Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM))*cos(angle * _PI / 180.0);
    y = _SUN_Y_PX + (Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM))*sin(angle * _PI / 180.0);
    mercury.setPosition({x, y});

    sf::CircleShape venus(Process().translateKmInPixel(_VENUS_RADIUS_KM));
    venus.setOrigin({venus.getLocalBounds().width/2, venus.getLocalBounds().height/2});
    venus.setFillColor(sf::Color::Blue);
    x = _SUN_X_PX + (Process().translateKmInPixel(_SUN_VENUS_DISTANCE_KM+_SUN_RADIUS_KM+_VENUS_RADIUS_KM))*cos(angle * _PI / 180.0);
    y = _SUN_Y_PX + (Process().translateKmInPixel(_SUN_VENUS_DISTANCE_KM+_SUN_RADIUS_KM+_VENUS_RADIUS_KM))*sin(angle * _PI / 180.0);
    venus.setPosition({x, y});

    sf::CircleShape earth(Process().translateKmInPixel(_EARTH_RADIUS_KM));
    earth.setOrigin({earth.getLocalBounds().width/2, earth.getLocalBounds().height/2});
    earth.setFillColor(sf::Color::Blue);
    x = _SUN_X_PX + (Process().translateKmInPixel(_SUN_EARTH_DISTANCE_KM+_SUN_RADIUS_KM+_EARTH_RADIUS_KM))*cos(angle * _PI / 180.0);
    y = _SUN_Y_PX + (Process().translateKmInPixel(_SUN_EARTH_DISTANCE_KM+_SUN_RADIUS_KM+_EARTH_RADIUS_KM))*sin(angle * _PI / 180.0);
    earth.setPosition({x, y});



    Player player(20000.f, 20000.f, 50000.f, 0.f, sf::Color::Red);

    view1.setCenter(sf::Vector2f(player.getPosition().x+player.getSize().x/2, player.getPosition().y+player.getSize().y/2));

    Time time;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            player.progress(60, view1);

            // on attrape les évènements de redimensionnement
            if (event.type == sf::Event::Resized)
            {
                // on met à jour la vue, avec la nouvelle taille de la fenêtre
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
            minimapview = true;
        }else{
            minimapview = false;
        }


        angle = time.update(angle);
        newX = _SUN_X_PX + (Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM))*cos(angle * _PI / 180.0);
        newY = _SUN_Y_PX + (Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM))*sin(angle * _PI / 180.0);

        //if(player. sur planète)
        //player.updatePosition(newX-x, newY-y);
        x = newX; y = newY;
        mercury.setPosition({x, y});




        // **************************** DISPLAY ****************************
        window.clear(sf::Color::White);

        window.setView(view1);
        window.draw(sun);
        window.draw(mercury);
        window.draw(venus);
        window.draw(earth);
        player.display(window);

        if(minimapview){
            window.setView(view2);
            window.draw(rectangle);

            window.setView(minimap);
            window.draw(sun);
            window.draw(mercury);
            window.draw(venus);
            window.draw(earth);
            player.display(window);
        }


        window.display();
    }

    return 0;
}
