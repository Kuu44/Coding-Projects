//
// Created by safal on 13/2/19.
//

#include <iostream>
#include <cmath>
#include <GameServer.h>
#include "Enemy.h"
#include "Player.h"

Player::Player()
	:sounds(Sounds::soundNumber)
{
	sounds.load(Sounds::gunShot, "../Media/Audio/gunShot0.wav");
	gunSound.setBuffer(sounds.get(Sounds::gunShot));
}

void Player::SetData(sf::Texture *playerTexture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position) {
	animation.SetData(playerTexture, imageCount, switchTime);
	row = 0;
	faceRight = true;
	isJumping = isShooting = false;
	health = 100;
	bulletVelocity = moveDirection = sf::Vector2f(0.f, 0.f);

	const sf::Vector2f playerSize = sf::Vector2f(250.0f, 250.0f);
	body.setSize(playerSize);
	body.setPosition(position);
	body.setTexture(playerTexture);
	body.setOrigin(playerSize);

	velocity = sf::Vector2f(2*speed, 3*speed);
}
void Player::Update(sf::Texture* bulletTexture, float deltaTime, Camera &gameView, float &baseHeight,float &leftExtremePoint, float &rightExtremePoint, sf::RenderWindow& window, sf::RectangleShape &sky, sf::Text *info)
{
	static sf::Vector2f movement(0.f, 0.f);
	static float localVelocity = velocity.y;
	const float g = 9.81f;
	if (not isJumping and sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		movement.x -= velocity.x * deltaTime;
	if (not isJumping and sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		movement.x += velocity.x * deltaTime;

	//NOTE: Make a collision detection by comparing the positions of the wall and player
	if (body.getPosition().x <= leftExtremePoint + body.getSize().x)
	{
		if (movement.x<0)
			movement.x = 0;
		body.setPosition(leftExtremePoint+body.getSize().x, body.getPosition().y);
	}
	else if(body.getPosition().x >= rightExtremePoint)
	{
		if(movement.x>0)
			movement.x = 0;
		body.setPosition(rightExtremePoint, body.getPosition().y);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		isJumping = true;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and clock.getElapsedTime().asSeconds()>=0.2f)
	{
		sf::Vector2i pixelMousePos = sf::Mouse::getPosition(window);
		sf::IntRect viewport = gameView.GetViewport(window);
		if (viewport.contains(pixelMousePos))
		{
			sf::Vector2f mousePos = window.mapPixelToCoords(pixelMousePos);
			if (mousePos.y<=baseHeight)
			{
				sf::Vector2f localBulletPos;
				if (faceRight)
					localBulletPos.x = body.getPosition().x - body.getSize().x*0.2f;
				else
					localBulletPos.x = body.getPosition().x - body.getSize().x*0.8f;
				localBulletPos.y = body.getPosition().y - body.getSize().y/1.45f;

				sf::Vector2f displacement = sf::Vector2f(mousePos.x - localBulletPos.x, mousePos.y - localBulletPos.y);
				double distance = sqrt(double(displacement.x * displacement.x + displacement.y * displacement.y));

				moveDirection = sf::Vector2f(float(displacement.x / distance), float(displacement.y / distance));

				bulletVelocity = sf::Vector2f(
					4 * velocity.x * moveDirection.x * deltaTime, 4 * velocity.y * moveDirection.y * deltaTime);

				gunSound.play();
				bullets.emplace_back(Bullet(bulletTexture, sf::Vector2f(20.f, 12.4f), localBulletPos, bulletVelocity));
				isShooting = true;
				clock.restart();
			}
		}
	}

	if (not isUp(body, baseHeight))
	{
		body.setPosition(body.getPosition().x, baseHeight);
		isJumping = false;
		localVelocity = velocity.y;
	}

	if(movement.x == 0)
		row = 0;
	else
	{
		row = 1;
		faceRight = movement.x > 0;
	}
	if(isJumping)
		row = 2;
	if(isShooting or clock.getElapsedTime().asSeconds()<=0.2f)
	{
		row = 3;
		if (isShooting)
		{
			faceRight = bulletVelocity.x > 0;
			std::cout << "Shooting !! \n";
		}
	}

	gameView.Move(movement);
	animation.Update(row, deltaTime, faceRight);
	isShooting = false;
	body.setTextureRect(animation.uvRect);
	body.move(movement);
	gameView.showInfo(&info[0], body);

	if (not isJumping)
		movement = sf::Vector2f(0.f, 0.f);
	else
	{
		movement.y = -localVelocity * deltaTime;
		localVelocity -= g;
	}
}

void Player::Update(sf::Texture* bulletTexture, float deltaTime, Camera &gameView, float &baseHeight,float &leftExtremePoint, float &rightExtremePoint, sf::RenderWindow& window, sf::RectangleShape &sky, sf::Text *info, GameServer& server, Enemy& enemy)
{
	static sf::Vector2f movement(0.f, 0.f);
	static float localVelocity = velocity.y;
	const float g = 9.81f;
	if (not isJumping and sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		movement.x -= velocity.x * deltaTime;
	if (not isJumping and sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		movement.x += velocity.x * deltaTime;

	//NOTE: Make a collision detection by comparing the positions of the wall and player
	if (body.getPosition().x <= leftExtremePoint + body.getSize().x)
	{
		if (movement.x<0)
			movement.x = 0;
		body.setPosition(leftExtremePoint+body.getSize().x, body.getPosition().y);
	}
	else if(body.getPosition().x >= rightExtremePoint)
	{
		if(movement.x>0)
			movement.x = 0;
		body.setPosition(rightExtremePoint, body.getPosition().y);
	}

	if(((body.getPosition().x <= enemy.GetPosition().x - body.getSize().x and body.getPosition().x + movement.x >= enemy.GetPosition().x - body.getSize().x)
			or (body.getPosition().x >= enemy.GetPosition().x + body.getSize().x and body.getPosition().x + movement.x <= enemy.GetPosition().x + body.getSize().x))
			and body.getPosition().y + body.getSize().y >= enemy.GetPosition().y)
	{
		movement.x = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		isJumping = true;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and clock.getElapsedTime().asSeconds()>=0.2f)
	{
		sf::Vector2i pixelMousePos = sf::Mouse::getPosition(window);
		sf::IntRect viewport = gameView.GetViewport(window);
		if (viewport.contains(pixelMousePos))
		{
			sf::Vector2f mousePos = window.mapPixelToCoords(pixelMousePos);
			if (mousePos.y<=baseHeight)
			{
				sf::Vector2f localBulletPos;
				if (faceRight)
					localBulletPos.x = body.getPosition().x - body.getSize().x*0.2f;
				else
					localBulletPos.x = body.getPosition().x - body.getSize().x*0.8f;
				localBulletPos.y = body.getPosition().y - body.getSize().y/1.45f;

				sf::Vector2f displacement = sf::Vector2f(mousePos.x - localBulletPos.x, mousePos.y - localBulletPos.y);
				double distance = sqrt(double(displacement.x * displacement.x + displacement.y * displacement.y));

				moveDirection = sf::Vector2f(float(displacement.x / distance), float(displacement.y / distance));

				bulletVelocity = sf::Vector2f(
					4 * velocity.x * moveDirection.x * deltaTime, 4 * velocity.y * moveDirection.y * deltaTime);

				gunSound.play();
				bullets.emplace_back(Bullet(bulletTexture, sf::Vector2f(20.f, 12.4f), localBulletPos, bulletVelocity));
				isShooting = true;
				clock.restart();
			}
		}
	}

	if (not isUp(body, baseHeight))
	{
		body.setPosition(body.getPosition().x, baseHeight);
		isJumping = false;
		localVelocity = velocity.y;
	}

	if(movement.x == 0)
		row = 0;
	else
	{
		row = 1;
		faceRight = movement.x > 0;
	}
	if(isJumping)
		row = 2;
	if(isShooting or clock.getElapsedTime().asSeconds()<=0.2f)
	{
		row = 3;
		if (isShooting)
		{
			std::cout << "Shooting !! \n";
			faceRight = bulletVelocity.x > 0;
		}
	}

    server.update(body.getPosition(),movement,bulletVelocity,isShooting,true, isJumping);
	isShooting = false;
	gameView.Move(movement);
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
	gameView.showInfo(&info[0], body);

	if (isJumping)
	{
		movement.y = -localVelocity * deltaTime;
		localVelocity -= g;
	}
	else
		movement = sf::Vector2f(0.f,0.f);

}

void Player::Draw(sf::RenderWindow &window, Camera& gameView,  Enemy& enemy, float baseHeight) {
	window.draw(body);
	for (auto &bullet : bullets)
	{
		bullet.draw(window);
		bullet.fire();
	}
	for (int i = 0; i < int(bullets.size()); i++)
	{
		if (HitCheck(enemy, bullets[i]) or bullets[i].getBullet().getPosition().y>baseHeight)
			bullets.erase(bullets.begin() + i--);
	}
}

bool Player::HitCheck(Enemy& enemy, Bullet& bullet)
{
	if(enemy.GetCollider().CheckCollision(Collider(bullet.getBullet())))
	{
		enemy.health -= 10;
		return true;
	}
	return false;
}

bool Player::isUp(sf::RectangleShape &shape, float &baseHeight)
{
	return shape.getPosition().y <= baseHeight;
}
