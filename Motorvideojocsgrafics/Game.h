#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include <vector>

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow mWindow;
    Player mPlayer;
    std::vector<Enemy> mEnemies;
    std::vector<Bullet> mBullets;
    bool mIsMovingUp, mIsMovingDown, mIsMovingLeft, mIsMovingRight;
    int mScore;
    bool mGameOver;
    int mTime = 0;

    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void updateBullets(sf::Time deltaTime);
    void updateEnemies(sf::Time deltaTime);
    void checkCollisions();
};
