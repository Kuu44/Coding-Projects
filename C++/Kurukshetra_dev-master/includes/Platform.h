//
// Created by safal on 14/2/19.
//

#pragma once
#include <SFML/Graphics.hpp>

class Platform {
public:
    Platform(){}
    Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
    void SetData(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
    void SetData(sf::Vector2f size, sf::Vector2f position);
    void SetTextureRect(sf::IntRect textureRect);
    void Draw(sf::RenderWindow& window);

private:
    sf::RectangleShape body;
};
