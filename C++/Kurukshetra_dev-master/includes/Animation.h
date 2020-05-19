//
// Created by safal on 13/2/19.
//

#pragma once


#include <SFML/Graphics.hpp>

class Animation {
public:

    void SetData(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
    void Update(unsigned row, float deltaTime, bool faceRight);

public:
    sf::IntRect uvRect;

private:
    sf::Vector2u imageCount;
    sf::Vector2u currentImage;

    float totalTime;
    float switchTime;
};
