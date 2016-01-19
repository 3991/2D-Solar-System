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
#define _SUN_MARS_DISTANCE_KM 228000.f
#define _SUN_JUPITER_DISTANCE_KM 778000.f
#define _SUN_SATURN_DISTANCE_KM 1427000.f
#define _SUN_URANUS_DISTANCE_KM 2870000.f
#define _SUN_NEPTUNE_DISTANCE_KM 4497000.f

#define _MERCURY_RADIUS_KM 2440.f

#define _VENUS_RADIUS_KM 6050.f

#define _EARTH_RADIUS_KM 6378.f

#define _MARS_RADIUS_KM 3396.f

#define _JUPITER_RADIUS_KM 71492.f

#define _SATURN_RADIUS_KM 60268.f

#define _URANUS_RADIUS_KM 25559.f

#define _NEPTUNE_RADIUS_KM 24766.f

int main()
{
    sf::RenderWindow window(sf::VideoMode(_WINDOW_WIDTH, _WINDOW_HEIGHT), "2S Solar System");
    window.setFramerateLimit(60);


    // **************************** VIEW ****************************
    sf::View view1(sf::FloatRect(0, 0, _WINDOW_WIDTH, _WINDOW_HEIGHT));
    sf::View view2(sf::FloatRect(0, 0, _WINDOW_WIDTH, _WINDOW_HEIGHT));
    sf::View minimap(sf::FloatRect(0, 0, _WINDOW_WIDTH, _WINDOW_HEIGHT));
    minimap.setViewport(sf::FloatRect(0.1f, 0.1f, 0.75f, 0.75f));

    view1.zoom(100.f);
    minimap.zoom(800.f);
    bool minimapview = false;



    sf::RectangleShape rectangle(sf::Vector2f(_WINDOW_WIDTH*0.75, _WINDOW_HEIGHT*0.75));
    rectangle.setPosition(sf::Vector2f(_WINDOW_WIDTH*0.10,_WINDOW_HEIGHT*0.10));
    rectangle.setOutlineColor(sf::Color(0,0,255,100));
    rectangle.setOutlineThickness(80.f);



    // **************************** PLANETS ****************************
    int mercuryAngle = 0, venusAngle = 0, earthAngle = 0, marsAngle = 0, jupiterAngle = 0, saturnAngle = 0, uranusAngle = 0, neptuneAngle = 0;
    float x, y, newX, newY;

    sf::CircleShape sun(Process().translateKmInPixel(_SUN_RADIUS_KM));
    sun.setOrigin({_SUN_X_PX+Process().translateKmInPixel(_SUN_RADIUS_KM), _SUN_Y_PX+Process().translateKmInPixel(_SUN_RADIUS_KM)});
    sun.setPosition({_SUN_X_PX, _SUN_Y_PX});
    sun.setFillColor(sf::Color::Yellow);


    sf::CircleShape mercury(Process().translateKmInPixel(_MERCURY_RADIUS_KM));
    mercury.setOrigin({mercury.getLocalBounds().width/2, mercury.getLocalBounds().height/2});
    mercury.setFillColor(sf::Color::Black);
    x = _SUN_X_PX + (Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM))*cos(mercuryAngle * _PI / 180.0);
    y = _SUN_Y_PX + (Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM))*sin(mercuryAngle * _PI / 180.0);
    mercury.setPosition({x, y});

    sf::CircleShape venus(Process().translateKmInPixel(_VENUS_RADIUS_KM));
    venus.setOrigin({venus.getLocalBounds().width/2, venus.getLocalBounds().height/2});
    venus.setFillColor(sf::Color::Blue);
    x = _SUN_X_PX + (Process().translateKmInPixel(_SUN_VENUS_DISTANCE_KM+_SUN_RADIUS_KM+_VENUS_RADIUS_KM))*cos(venusAngle * _PI / 180.0);
    y = _SUN_Y_PX + (Process().translateKmInPixel(_SUN_VENUS_DISTANCE_KM+_SUN_RADIUS_KM+_VENUS_RADIUS_KM))*sin(venusAngle * _PI / 180.0);
    venus.setPosition({x, y});

    sf::CircleShape earth(Process().translateKmInPixel(_EARTH_RADIUS_KM));
    earth.setOrigin({earth.getLocalBounds().width/2, earth.getLocalBounds().height/2});
    earth.setFillColor(sf::Color::Blue);
    x = _SUN_X_PX + (Process().translateKmInPixel(_SUN_EARTH_DISTANCE_KM+_SUN_RADIUS_KM+_EARTH_RADIUS_KM))*cos(earthAngle * _PI / 180.0);
    y = _SUN_Y_PX + (Process().translateKmInPixel(_SUN_EARTH_DISTANCE_KM+_SUN_RADIUS_KM+_EARTH_RADIUS_KM))*sin(earthAngle * _PI / 180.0);
    earth.setPosition({x, y});

    sf::CircleShape mars(Process().translateKmInPixel(_MARS_RADIUS_KM));
    mars.setOrigin({mars.getLocalBounds().width/2, mars.getLocalBounds().height/2});
    mars.setFillColor(sf::Color::Blue);
    x = _SUN_X_PX + (Process().translateKmInPixel(_SUN_MARS_DISTANCE_KM+_SUN_RADIUS_KM+_MARS_RADIUS_KM))*cos(marsAngle * _PI / 180.0);
    y = _SUN_Y_PX + (Process().translateKmInPixel(_SUN_MARS_DISTANCE_KM+_SUN_RADIUS_KM+_MARS_RADIUS_KM))*sin(marsAngle * _PI / 180.0);
    mars.setPosition({x, y});

    sf::CircleShape jupiter(Process().translateKmInPixel(_JUPITER_RADIUS_KM));
    jupiter.setOrigin({jupiter.getLocalBounds().width/2, jupiter.getLocalBounds().height/2});
    jupiter.setFillColor(sf::Color::Blue);
    x = _SUN_X_PX + (Process().translateKmInPixel(_SUN_JUPITER_DISTANCE_KM+_SUN_RADIUS_KM+_JUPITER_RADIUS_KM))*cos(jupiterAngle * _PI / 180.0);
    y = _SUN_Y_PX + (Process().translateKmInPixel(_SUN_JUPITER_DISTANCE_KM+_SUN_RADIUS_KM+_JUPITER_RADIUS_KM))*sin(jupiterAngle * _PI / 180.0);
    jupiter.setPosition({x, y});

    sf::CircleShape saturn(Process().translateKmInPixel(_SATURN_RADIUS_KM));
    saturn.setOrigin({saturn.getLocalBounds().width/2, saturn.getLocalBounds().height/2});
    saturn.setFillColor(sf::Color::Red);
    x = _SUN_X_PX + (Process().translateKmInPixel(_SUN_SATURN_DISTANCE_KM+_SUN_RADIUS_KM+_SATURN_RADIUS_KM))*cos(saturnAngle * _PI / 180.0);
    y = _SUN_Y_PX + (Process().translateKmInPixel(_SUN_SATURN_DISTANCE_KM+_SUN_RADIUS_KM+_SATURN_RADIUS_KM))*sin(saturnAngle * _PI / 180.0);
    saturn.setPosition({x, y});

    sf::CircleShape uranus(Process().translateKmInPixel(_URANUS_RADIUS_KM));
    uranus.setOrigin({uranus.getLocalBounds().width/2, uranus.getLocalBounds().height/2});
    uranus.setFillColor(sf::Color::Red);
    x = _SUN_X_PX + (Process().translateKmInPixel(_SUN_URANUS_DISTANCE_KM+_SUN_RADIUS_KM+_URANUS_RADIUS_KM))*cos(uranusAngle * _PI / 180.0);
    y = _SUN_Y_PX + (Process().translateKmInPixel(_SUN_URANUS_DISTANCE_KM+_SUN_RADIUS_KM+_URANUS_RADIUS_KM))*sin(uranusAngle * _PI / 180.0);
    uranus.setPosition({x, y});

    sf::CircleShape neptune(Process().translateKmInPixel(_NEPTUNE_RADIUS_KM));
    neptune.setOrigin({neptune.getLocalBounds().width/2, neptune.getLocalBounds().height/2});
    neptune.setFillColor(sf::Color::Black);
    x = _SUN_X_PX + (Process().translateKmInPixel(_SUN_NEPTUNE_DISTANCE_KM+_SUN_RADIUS_KM+_NEPTUNE_RADIUS_KM))*cos(neptuneAngle * _PI / 180.0);
    y = _SUN_Y_PX + (Process().translateKmInPixel(_SUN_NEPTUNE_DISTANCE_KM+_SUN_RADIUS_KM+_NEPTUNE_RADIUS_KM))*sin(neptuneAngle * _PI / 180.0);
    neptune.setPosition({x, y});


    Player player(500.f, 1000.f, earth.getPosition().x, earth.getPosition().y, sf::Color::Red);

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

        if(time.update(mercuryAngle)){
            if(mercuryAngle<360){
                mercuryAngle += 15;
            }else{
                mercuryAngle = 0;
            }
           // mercuryAngle = time.update(mercuryAngle);
            newX = _SUN_X_PX + (Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM))*cos(mercuryAngle * _PI / 180.0);
            newY = _SUN_Y_PX + (Process().translateKmInPixel(_SUN_MERCURY_DISTANCE_KM+_SUN_RADIUS_KM+_MERCURY_RADIUS_KM))*sin(mercuryAngle * _PI / 180.0);
            x = newX;
            y = newY;
            mercury.setPosition({x, y});


            if(venusAngle<360){
                venusAngle += 15;
            }else{
                venusAngle = 0;
            }
           // venusAngle = time.update(venusAngle);
            newX = _SUN_X_PX + (Process().translateKmInPixel(_SUN_VENUS_DISTANCE_KM+_SUN_RADIUS_KM+_VENUS_RADIUS_KM))*cos(venusAngle * _PI / 180.0);
            newY = _SUN_Y_PX + (Process().translateKmInPixel(_SUN_VENUS_DISTANCE_KM+_SUN_RADIUS_KM+_VENUS_RADIUS_KM))*sin(venusAngle * _PI / 180.0);
            x = newX;
            y = newY;
            venus.setPosition({x, y});



            if(earthAngle<360){
                earthAngle += 15;
            }else{
                earthAngle = 0;
            }
            newX = _SUN_X_PX + (Process().translateKmInPixel(_SUN_EARTH_DISTANCE_KM+_SUN_RADIUS_KM+_EARTH_RADIUS_KM))*cos(earthAngle * _PI / 180.0);
            newY = _SUN_Y_PX + (Process().translateKmInPixel(_SUN_EARTH_DISTANCE_KM+_SUN_RADIUS_KM+_EARTH_RADIUS_KM))*sin(earthAngle * _PI / 180.0);
            x = newX;
            y = newY;
            earth.setPosition({x, y});
        }

        // **************************** DISPLAY ****************************
        window.clear(sf::Color::White);

        window.setView(view1);
        window.draw(sun);
        window.draw(mercury);
        window.draw(venus);
        window.draw(earth);
        window.draw(mars);
        window.draw(jupiter);
        window.draw(saturn);
        window.draw(uranus);
        window.draw(neptune);
        player.display(window);

        if(minimapview){
            window.setView(view2);
            window.draw(rectangle);

            window.setView(minimap);
            window.draw(sun);
            window.draw(mercury);
            window.draw(venus);
            window.draw(earth);
            window.draw(mars);
            window.draw(jupiter);
            window.draw(saturn);
            window.draw(uranus);
            window.draw(neptune);
            player.display(window);
        }


        window.display();
    }

    return 0;
}
