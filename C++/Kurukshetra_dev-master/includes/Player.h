//
// Created by safal on 13/2/19.
//

#pragma once

#include <SFML/Network/TcpSocket.hpp>
#include "Animation.h"
#include "Collider.h"
#include "GameServer.h"
#include "Bullet.h"
#include "Camera.h"
#include "Platform.h"
#include "../src/ResourceHolder.cpp"
#include <SFML/Audio.hpp>
#include <vector>

class Enemy;

class Player {
public:
	Player();
    void SetData(sf::Texture *playerTexture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position);
	void Update(sf::Texture* bulletTexture , float deltaTime, Camera &gameView, float &baseHeight,float &leftExtremePoint, float &rightExtremePoint, sf::RenderWindow& window, sf::RectangleShape& sky,  sf::Text *info, GameServer& server, Enemy& enemy);
	void Update(sf::Texture* bulletTexture , float deltaTime, Camera &gameView, float &baseHeight,float &leftExtremePoint, float &rightExtremePoint, sf::RenderWindow& window, sf::RectangleShape& sky,  sf::Text *info);
	void Draw(sf::RenderWindow& window, Camera& gameView, Enemy& enemy, float baseHeight);
    Collider GetCollider() { return Collider(body); }
    sf::RectangleShape& GetBody() { return body;}
    bool isDead(){ return health<=0;}
    sf::Vector2f GetSize(){ return body.getSize(); }

private:
	bool HitCheck(Enemy& enemy, Bullet& bullet);
	bool isUp(sf::RectangleShape& shape, float& baseHeight);

private:
    sf::RectangleShape body;
    Animation animation;
	ResourceHolder <sf::SoundBuffer, Sounds::ID> sounds;
	sf::Sound gunSound;
    unsigned row;
    bool faceRight, isJumping, isShooting;
    sf::Vector2f velocity, bulletVelocity, moveDirection;
    std::vector <Bullet> bullets;
    sf::Clock clock;
public:
	int health;
};

