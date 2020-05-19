//
// Created by safal on 25/2/19.
//

#pragma once
#include <SFML/Graphics.hpp>

class Camera {
private:
    sf::View view;

public:
    void SetData(sf::Vector2f center, sf::Vector2f size, sf::FloatRect rect);
    void SetView(sf::RenderWindow& window){window.setView(view);}
    void SetSize(sf::Vector2f size){view.setSize(size);}
    void Move(sf::Vector2f newCameraPosition){view.move(newCameraPosition.x, 0);}
    void showInfo(sf::Text* info, sf::RectangleShape& player);
    void Update(sf::RectangleShape& player, sf::RenderWindow& window, sf::RectangleShape& sky);
    sf::IntRect GetViewport(sf::RenderWindow& window){return static_cast<sf::IntRect>(window.getViewport(view));}
    void SetCenter(sf::Vector2f center){view.setCenter(center);}
    void SetViewPort(sf::FloatRect rect){view.setViewport(rect);}
    sf::Vector2f GetCenter() { return view.getCenter(); }
};

