//
// Created by safal on 25/2/19.
//

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Camera.h"

void Camera::SetData(sf::Vector2f center, sf::Vector2f size, sf::FloatRect rect) {
    this -> SetCenter(center);
    this -> SetSize(size);
    this -> SetViewPort(rect);
}

void Camera::Update(sf::RectangleShape &player, sf::RenderWindow &window, sf::RectangleShape &sky) {

    view.setCenter(player.getPosition().x, player.getPosition().y - 300);

    std::cout << player.getPosition().x << std::endl;

}

void Camera::showInfo(sf::Text* info, sf::RectangleShape &player) {
        info->setPosition(player.getPosition().x - player.getSize().x, player.getPosition().y - (3.f / 2.f) * player.getSize().y);
        info->setFillColor(sf::Color::Red);
}
