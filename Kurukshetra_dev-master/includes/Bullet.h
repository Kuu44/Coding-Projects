//
// Created by maverick on 25/2/19.
//

#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Bullet
{
public:
	Bullet(sf::Texture* bulletTexture, sf::Vector2f bulletSize, sf::Vector2f bulletPos, sf::Vector2f bulletVelocity);
	void fire();
	void draw(sf::RenderWindow& window);
	sf::RectangleShape& getBullet(){ return bullet; }
private:
	sf::RectangleShape bullet;
	sf::Vector2f velocity;
};
