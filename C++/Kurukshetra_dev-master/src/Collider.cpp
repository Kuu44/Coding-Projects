//
// Created by safal on 14/2/19.
//

#include "Collider.h"

Collider::Collider(sf::RectangleShape &body):body(body){}

bool Collider::CheckCollision(Collider other) {
    sf::FloatRect otherBounds = other.GetGlobalBounds();
    sf::FloatRect thisBounds = GetGlobalBounds();
    return thisBounds.intersects(otherBounds);
}
