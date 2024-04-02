#include "Enemy.h"

Enemy::Enemy(float x, float y) {
    shape.setPosition(x, y);
    shape.setSize(sf::Vector2f(20.f, 20.f));
    shape.setFillColor(sf::Color::Green);
}

void Enemy::update() {
    shape.move(-0.5f, 0);
}