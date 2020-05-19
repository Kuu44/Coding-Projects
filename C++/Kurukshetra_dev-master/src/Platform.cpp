//
// Created by safal on 14/2/19.
//

#include "Platform.h"


void Platform::SetData(sf::Texture *texture, sf::Vector2f size, sf::Vector2f position) {
    body.setSize(size);
//    body.setOrigin(size);
    body.setTexture(texture);
    body.setPosition(position);
}

void Platform::Draw(sf::RenderWindow &window) {
    window.draw(body);
}

void Platform::SetData(sf::Vector2f size, sf::Vector2f position) {
    body.setSize(size);
    body.setPosition(position);
}

void Platform::SetTextureRect(sf::IntRect textureRect) {
    body.setTextureRect(textureRect);
}

Platform::Platform(sf::Texture *texture, sf::Vector2f size, sf::Vector2f position) {
    body.setSize(size);
    body.setTexture(texture);
    body.setPosition(position);
}

