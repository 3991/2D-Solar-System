#include "Player.h"

Player::Player(){
}

Player::Player(float width, float height, float positionX, float positionY, sf::Color color){
    player.setSize(sf::Vector2f(width, height));
    player.setPosition(positionX, positionY);
    player.setFillColor(color);
}

Player::~Player(){

}

sf::Vector2f Player::getPosition(){

    return this->player.getPosition();
}

sf::Vector2f Player::getSize(){

    return this->player.getSize();
}

void Player::progress(float frame, sf::View &view1){

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        view1.move(-SPEED*frame, 0);
        player.move(-SPEED*frame, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        view1.move(SPEED*frame, 0);
        player.move(SPEED*frame, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        view1.move(0, -SPEED*frame);
        player.move(0, -SPEED*frame);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        view1.move(0, SPEED*frame);
        player.move(0, SPEED*frame);
    }
}

void Player::updatePosition(float x, float y){
    player.move(x, y);
}

void Player::display(sf::RenderWindow &window){
    window.draw(player);
}
