#include "Player.h"

Player::Player() {
    shape.setSize(sf::Vector2f(50.f, 50.f));
    shape.setPosition(400, 550); 
    shape.setFillColor(sf::Color::Yellow);
}

void Player::shoot() {
    bullets.push_back(Bullet(shape.getPosition().x + shape.getSize().x / 2 - 2.5f, shape.getPosition().y));
}

void Player::update() {
    for (int i = 0; i < bullets.size(); ++i) {
        bullets[i].update();
        if (bullets[i].shape.getPosition().x > 800) { 
            bullets.erase(bullets.begin() + i);
            --i;
        }
    }
}