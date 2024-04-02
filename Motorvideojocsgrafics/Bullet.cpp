#include "Bullet.h"

Bullet::Bullet(float x, float y) : velocity(sf::Vector2f(0.5f, 0)) {
    shape.setPosition(x, y);
    shape.setRadius(5.f);
    shape.setFillColor(sf::Color::Red);
}

void Bullet::update() {
    shape.move(velocity);
}