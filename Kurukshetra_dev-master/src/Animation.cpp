//
// Created by safal on 13/2/19.
//

#include "Animation.h"


void Animation::SetData(sf::Texture *texture, sf::Vector2u imageCount, float switchTime) {
    this -> imageCount = imageCount;
    totalTime = 0;
    this -> switchTime = switchTime;
    currentImage.x = 0;
    currentImage.y = 0;
    uvRect.width = texture->getSize().x / imageCount.x;
    uvRect.height = texture->getSize().y / imageCount.y;
}

void Animation::Update(unsigned row, float deltaTime, bool faceRight){
    currentImage.y = row;
    totalTime += deltaTime;

    if(totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++;

        if(currentImage.x >= imageCount.x)
        {
            currentImage.x = 0;
        }
    }
    uvRect.top = currentImage.y * uvRect.height;
    if(faceRight)
    {
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }
    else
    {
        uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }
}

