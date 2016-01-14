#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#define SPEED 10.f

class Player
{
public :

    Player();
    Player(float width, float height, float positionX, float positionY, sf::Color color);
    ~Player();
    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    void progress(float frame, sf::View &view1);
    void updatePosition(float x, float y);
    void display(sf::RenderWindow &window);
private :
    sf::RectangleShape player;
};

#endif // PLAYER_H_INCLUDED
