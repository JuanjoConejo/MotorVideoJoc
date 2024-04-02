#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
public:
    sf::CircleShape shape;
    sf::Vector2f velocity;

    Bullet(float x, float y);
    void update();
};

#endif