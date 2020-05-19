//
// Created by safal on 14/2/19.
//

#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

class Collider {
public:
    Collider(sf::RectangleShape& body);
    bool CheckCollision(Collider other);
    sf::FloatRect GetGlobalBounds() { return body.getGlobalBounds(); }

private:
    sf::RectangleShape& body;
};
