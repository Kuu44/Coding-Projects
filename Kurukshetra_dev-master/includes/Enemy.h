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
#include "GameClient.h"
#include "ResourceHolder.h"
#include <SFML/Audio.hpp>
#include <vector>

class Player;

class Enemy {
public:
    Enemy();
    void SetData(sf::Texture *EnemyTexture, sf::Vector2u imageCount, float switchTime);
    void Update(sf::Texture* bulletTexture, float deltaTime, Camera &gameView, float &baseHeight, sf::RenderWindow& window, sf::RectangleShape& sky, sf::Text* info, GameClient& client);
    void Draw(sf::RenderWindow& window, Camera& gameView , Player& player, float baseHeight);
    Collider GetCollider() { return Collider(body); }
    sf::Vector2f GetPosition(){ return body.getPosition(); }
	bool isDead(){ return health<=0;}
private:
	bool HitCheck(Player& player, Bullet& bullet);
//    bool isUp(sf::RectangleShape& shape, float& baseHeight);
private:
    sf::RectangleShape body;
    Animation animation;
	ResourceHolder <sf::SoundBuffer, Sounds::ID> sounds;
	sf::Sound gunSound;
    unsigned row;
    bool faceRight;
    sf::Vector2f bulletVelocity;
    std::vector <Bullet> bullets;
    friend class Player;
public:
    int health;
};
