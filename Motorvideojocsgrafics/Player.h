#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.h"

class Player {
public:
    sf::RectangleShape shape;
    std::vector<Bullet> bullets;

    Player();
    void shoot();
    void update();
};

#endif