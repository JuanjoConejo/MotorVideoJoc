#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include <cstdlib> 
#include <ctime> 
#include <SFML/Graphics.hpp>


Game::Game() : mWindow(sf::VideoMode(640, 480), "SFML Game"), mPlayer(), mIsMovingUp(false), mIsMovingDown(false), mIsMovingLeft(false), mIsMovingRight(false), mScore(0), mGameOver(false) {
    srand(time(NULL)); 
    mPlayer.shape.setPosition(320.f - mPlayer.shape.getSize().x / 2, 480.f - mPlayer.shape.getSize().y - 10.f); 
}

void Game::run() {
    sf::Clock clock;
    while (mWindow.isOpen() && !mGameOver) {
        sf::Time deltaTime = clock.restart();
        processEvents();
        update(deltaTime);
        checkCollisions();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (mWindow.pollEvent(event)) {
        switch (event.type) {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        }
    }
}

void Game::update(sf::Time deltaTime) {

    sf::Vector2f movement(0.f, 0.f);
    if (mIsMovingUp) movement.y -= 1.f;
    if (mIsMovingDown) movement.y += 1.f;
    if (mIsMovingLeft) movement.x -= 1.f;
    if (mIsMovingRight) movement.x += 1.f;
    mPlayer.shape.move(movement * 100.f * deltaTime.asSeconds());

    for (auto& bullet : mPlayer.bullets) {
        bullet.update();
    }

    mPlayer.bullets.erase(std::remove_if(mPlayer.bullets.begin(), mPlayer.bullets.end(), [this](const Bullet& b) {
        return b.shape.getPosition().y < 0;
        }), mPlayer.bullets.end());

    if (mTime > 10000) {
        mEnemies.push_back(Enemy(mWindow.getSize().x, rand() % mWindow.getSize().y));
        mTime = 0;
    }
    else {
        mTime++;
    }

    for (auto& enemy : mEnemies) {
        enemy.update();
    }

    mEnemies.erase(std::remove_if(mEnemies.begin(), mEnemies.end(), [this](const Enemy& e) {
        return e.shape.getPosition().y > mWindow.getSize().y;
        }), mEnemies.end());
}

void Game::render() {
    mWindow.clear();
    mWindow.draw(mPlayer.shape);
    for (auto& bullet : mPlayer.bullets) {
        mWindow.draw(bullet.shape);
    }
    for (auto& enemy : mEnemies) {
        mWindow.draw(enemy.shape);
    }
    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::W) mIsMovingUp = isPressed;
    else if (key == sf::Keyboard::S) mIsMovingDown = isPressed;
    else if (key == sf::Keyboard::Space && isPressed) mPlayer.shoot();
}

void Game::checkCollisions() {

    for (auto bulletIt = mPlayer.bullets.begin(); bulletIt != mPlayer.bullets.end();) {
        bool bulletRemoved = false;
        for (auto enemyIt = mEnemies.begin(); enemyIt != mEnemies.end() && !bulletRemoved;) {
            if (bulletIt->shape.getGlobalBounds().intersects(enemyIt->shape.getGlobalBounds())) {
                bulletIt = mPlayer.bullets.erase(bulletIt);
                enemyIt = mEnemies.erase(enemyIt);
                mScore += 1; 
                bulletRemoved = true;
            }
            else {
                ++enemyIt;
            }
        }
        if (!bulletRemoved) ++bulletIt;
    }

   
    for (auto& enemy : mEnemies) {
        if (enemy.shape.getPosition().y + enemy.shape.getSize().y >= mWindow.getSize().y) {
            mGameOver = true;
            break;
        }
    }
}
