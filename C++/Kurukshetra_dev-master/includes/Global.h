//
// Created by samip on 27/2/19.
//

#pragma once
#include <SFML/System/Vector2.hpp>

struct clientInfo
{
    sf::Vector2f bodyPosition;
    sf::Vector2f bodyMovement;
    sf::Vector2f bullet;
    bool isshooting;
    bool shootWithTime;
    bool isJumping;
};
