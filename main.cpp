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

#define _MERCURY_RADIUS_KM 400000.f

int main()
{
    sf::RenderWindow window(sf::VideoMode(_WINDOW_WIDTH, _WINDOW_HEIGHT), "2S Solar System");
    window.setFramerateLimit(60);


    sf::View view1(sf::FloatRect(0, 0, _WINDOW_WIDTH, _WINDOW_HEIGHT));
    sf::View minimap(sf::FloatRect(0, 0, _WINDOW_WIDTH, _WINDOW_HEIGHT));
    minimap.setViewport(sf::FloatRect(0.1f, 0.1f, 0.75f, 0.75f));

    view1.zoom(500.f);
    minimap.zoom(500.f);

    sf::RectangleShape rectangle(sf::Vector2f(_WINDOW_WIDTH*0.75, _WINDOW_HEIGHT*0.75));
    rectangle.setPosition(sf::Vector2f(_WINDOW_WIDTH*0.10,_WINDOW_HEIGHT*0.10));
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(5.f);




    bool minimapview = false;




    sf::CircleShape sun(Process().translateKmInPixel(_SUN_RADIUS_KM));
    sun.setOrigin({_SUN_X_PX+Process().translateKmInPixel(_SUN_RADIUS_KM), _SUN_Y_PX+Process().translateKmInPixel(_SUN_RADIUS_KM)});
    sun.setPosition({_SUN_X_PX, _SUN_Y_PX});
    sun.setFillColor(sf::Color::Yellow);


   /*sf::CircleShape ecliptic(Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM));
    ecliptic.setOrigin({_SUN_X_PX+Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM), _SUN_Y_PX+Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM)});
    ecliptic.setPosition({_SUN_X_PX, _SUN_Y_PX});
    ecliptic.setFillColor(sf::Color::Blue);*/

    sf::CircleShape mercury(Process().translateKmInPixel(_MERCURY_RADIUS_KM));
    mercury.setOrigin({mercury.getLocalBounds().width/2, mercury.getLocalBounds().height/2});
    mercury.setFillColor(sf::Color::Black);

    float x, y, newX, newY;
    int angle = 0;
    x = _SUN_X_PX + (Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM))*cos(angle * _PI / 180.0);
    y = _SUN_Y_PX + (Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM))*sin(angle * _PI / 180.0);
    mercury.setPosition({x, y});


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



        //if(player sur planète)
        player.updatePosition(newX-x, newY-y);
        x = newX; y = newY;

        mercury.setPosition({x, y});


        window.clear(sf::Color::White);

        window.setView(view1);
        window.draw(sun);
        window.draw(mercury);
        player.display(window);

        if(minimapview){
            window.draw(rectangle);
            window.setView(minimap);
            //window.draw(ecliptic);
            window.draw(sun);
            window.draw(mercury);
            player.display(window);
        }


        window.display();
    }

    return 0;
}
