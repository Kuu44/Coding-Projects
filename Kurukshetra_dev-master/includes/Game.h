//
// Created by maverick on 12/2/19.
//

#pragma once

#include "Player.h"
#include "Platform.h"
#include "GameServer.h"
#include "Enemy.h"
#include "Camera.h"
#include <vector>

// NOTE: textureNumber and fontNumber is always at the last of enum to find the size of enum needed for constructor of ResourceHandler
namespace Textures
{
    enum ID {skyTexture, groundTexture, rockTexture, playerTexture, grassTexture, bulletTexture, wallTexture, barrelTexture, enemyTexture, textureNumber};
}

namespace GameFonts
{
	enum ID {info, fontNumber};
}

class Game {
public:
    Game(unsigned viewWidth, unsigned viewHeight,std::string Ip,bool isPlayer1);
    void run();

private:
    void processEvents();
    void update();
    void render();
    void ResizedWindow(sf::RenderWindow& window, Camera& view);
    void setWalls();
    void gameOver();
    void deadAnimate(std::string info, sf::Clock& waitClock);

private:
    sf::RenderWindow window;
    ResourceHolder <sf::Texture, Textures::ID> textures;
    ResourceHolder <sf::Font, GameFonts::ID> fonts;
    sf::Text info[2];
    sf::Text deadInfo;
	friend class Player;
	Player player;
    GameServer server;
    GameClient client;
    Enemy enemy;
    sf::RectangleShape sky, rock;
    Animation playerAnimation, enemyAnimation;
    sf::Clock clock;
    Camera gameView;
    sf::View minimapView;
    Platform walls[2];
    Platform ground;
    float viewWidth;
    float viewHeight, baseHeight;

public:
    float leftExtremePoint, rightExtremePoint;
};
