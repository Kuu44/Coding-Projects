//
// Created by samip on 25/2/19.
//

#include <iostream>
#include <cmath>
#include <GameServer.h>
#include "Player.h"
#include "Global.h"
#include "Enemy.h"

Enemy::Enemy()
	:sounds(Sounds::soundNumber)
{
	sounds.load(Sounds::gunShot, "../Media/Audio/gunShot0.wav");
	gunSound.setBuffer(sounds.get(Sounds::gunShot));
}

void Enemy::SetData(sf::Texture *EnemyTexture, sf::Vector2u imageCount, float switchTime) {
	animation.SetData(EnemyTexture, imageCount, switchTime);
	row = 0;
	faceRight = true;
	health = 100;
	bulletVelocity = sf::Vector2f(0.f, 0.f);

	const sf::Vector2f EnemySize = sf::Vector2f(250.0f, 250.0f);
	body.setSize(EnemySize);
//	body.setPosition(position);
	body.setTexture(EnemyTexture);
	body.setOrigin(EnemySize);
//    body.setOrigin(EnemySize.x/2, EnemySize.y/2);
}

void Enemy::Update(sf::Texture* bulletTexture, float deltaTime, Camera &gameView, float &baseHeight, sf::RenderWindow& window, sf::RectangleShape& sky, sf::Text *info, GameClient& client)
{
	struct clientInfo localClient= client.getRecievedData();
	body.setPosition(localClient.bodyPosition);
	if (localClient.isshooting){
	    std::cout << "Enemy is Shooting!!! \n";

	}
	if (localClient.isshooting)
	{
		gunSound.play();
		sf::Vector2f localBulletPos;
		if (faceRight)
			localBulletPos.x = body.getPosition().x - body.getSize().x*0.2f;
		else
			localBulletPos.x = body.getPosition().x - body.getSize().y*0.8f;
		localBulletPos.y = body.getPosition().y - body.getSize().y/1.45f;
		bullets.emplace_back(bulletTexture, sf::Vector2f(20.f, 12.4f), localBulletPos, localClient.bullet);
		client.setNotShooting();
	}
//
//	if (not isUp(body, baseHeight))
//	{
//		body.setPosition(body.getPosition().x, baseHeight);
//	}

	if( localClient.bodyMovement.x == 0.f)
		row = 0;
	else
	{
		row = 1;
		faceRight = localClient.bodyMovement.x > 0.f;
	}

	if(localClient.isJumping)
		row = 2;

	if (localClient.isshooting) {
		row = 3;
		faceRight = localClient.bullet.x> 0.f;
	}

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	info[1].setString(client.getName());
	gameView.showInfo(&info[1], body);
}
void Enemy::Draw(sf::RenderWindow &window, Camera& gameView, Player& player, float baseHeight) {
	window.draw(body);
	for (auto &bullet : bullets)
	{
		bullet.draw(window);
		bullet.fire();
	}

	for (int i = 0; i < int(bullets.size()); i++)
	{
		if (HitCheck(player, bullets[i]) or bullets[i].getBullet().getPosition().y>baseHeight)
			bullets.erase(bullets.begin() + i--);
	}
}

bool Enemy::HitCheck(Player& player, Bullet& bullet)
{
	if(player.GetCollider().CheckCollision(Collider(bullet.getBullet())))
	{
		player.health -= 10;
		return true;
	}
	return false;
}
//
//bool Enemy::isUp(sf::RectangleShape &shape, float &baseHeight) {
//	return shape.getPosition().y <= baseHeight;
//}