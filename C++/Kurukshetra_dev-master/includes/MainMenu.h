//
// Created by samip on 13/2/19.
//

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Game.h"

// NOTE fontNumber is always at the last of enum to find the size of enum needed for constructor of ResourceHandler
namespace Fonts
{
    enum ID {menuFont, fontNumber};
}

class MainMenu{
public:
    MainMenu(unsigned int width, unsigned int height);
    void run();

private:
    void about();
    void moveUp(bool goUp);
    void render();
    void handlePlayerInput(sf::Keyboard::Key &key, bool isPressed);
    void update();
    void processEvents();
    void onPressEnter();
private:
    sf::Text menu[3];
    sf::Text aboutText;
    std::string aboutTextString;
    ResourceHolder <sf::Font, Fonts::ID> fonts;
    int selectedItem;
    bool isPressedUp, isPressedDown, isPressedReturn, enterAbout;
    unsigned width, height;
    sf::Texture menuTexture;
    sf::RectangleShape menuImage;
protected:
    sf::RenderWindow mWindow2;
};
