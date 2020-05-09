//
// Created by samip on 13/2/19.
//

#include <iostream>
#include <fstream>
#include "MainMenu.h"
#include "Game.h"
#include "IpEnter.h"

void MainMenu::render(){
    if (enterAbout == false)
    {
        mWindow2.clear();
        mWindow2.draw(menuImage);
        for(int i=0;i<3;i++) {
            menu[i].setFillColor(i==selectedItem? sf::Color::Red : sf::Color::Black);
            mWindow2.draw(menu[i]);
        }
        mWindow2.display();
    }
    else
    {
        about();
    }
}
MainMenu::MainMenu(unsigned int width, unsigned int height)
	:fonts(Fonts::fontNumber),
    selectedItem(0),
	isPressedUp(false),
	isPressedDown(false),
	isPressedReturn(false),
	enterAbout(false),
	mWindow2(sf::VideoMode(width, height), "Kurukshetra"),
	width(width),
    height(height)
{
    fonts.load(Fonts::menuFont, "../Media/Fonts/DejaVuSans.ttf");
    for (auto &font : menu)
        font.setFont(fonts.get(Fonts::menuFont));
    menu[0].setString("Play");
    menu[1].setString("About");
    menu[2].setString("Exit");
    for (int i=0; i<3; i++)
        menu[i].setPosition(width - (width/4.f),(height / 2.f) + (height/6.f*i));
    menuTexture.loadFromFile("../Media/Textures/menu.png");
    menuImage.setSize(sf::Vector2f(width, height));
    menuImage.setPosition(0,0);
    menuImage.setTexture(&menuTexture);
    aboutText.setFont(fonts.get(Fonts::menuFont));

    std::string detail;
    std::fstream aboutFile;
    aboutFile.open(("../about.txt"));
    if(aboutFile)
    {
        while(getline(aboutFile, detail))
        {
            aboutTextString.append(detail + "\n");
        }
    }
}
void MainMenu::moveUp(const bool goUp = true) {
    if (goUp and selectedItem != 0)
        selectedItem--;
    else if(not goUp and selectedItem!=2)
        selectedItem++;
}
void MainMenu::handlePlayerInput(sf::Keyboard::Key &key, bool isPressed) {
    switch (key){
        case sf::Keyboard::Up:
            isPressedUp=isPressed;
            break;
        case sf::Keyboard::Down:
            isPressedDown=isPressed;
            break;
        case sf::Keyboard::Return:
            isPressedReturn=isPressed;
            break;
        case sf::Keyboard::Escape:
            enterAbout = false;
            break;
    }
    update();
}

void MainMenu::update() {
    if(isPressedUp)
        moveUp();
    if(isPressedDown)
        moveUp(false);
    if(isPressedReturn)
        onPressEnter();
}

void MainMenu::onPressEnter(){
    switch (selectedItem)
    {
        case 1:
            enterAbout = true;
            break;
        case 2:
            std::cout<<"Program exited successfully!"<<std::endl;
            exit(0);
        case 0:
            mWindow2.close();
            IpEnter ipEnter(1377,720);
            ipEnter.run();
            break;
    }
}

void MainMenu::about() {
    mWindow2.clear(sf::Color(255, 255, 255, 150));
    aboutText.setString(aboutTextString);
    aboutText.setFillColor(sf::Color::Black);
    aboutText.setCharacterSize(18);
    aboutText.setPosition(10, 50);
    mWindow2.draw(aboutText);
    mWindow2.display();
}

void MainMenu::run() {
    while (mWindow2.isOpen())
    {
        processEvents();
        render();
    }
}

void MainMenu::processEvents() {
    sf::Event event = {};
    while (mWindow2.pollEvent(event))
    {
        switch (event.type) {
            case sf::Event::KeyPressed:
                handlePlayerInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handlePlayerInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                mWindow2.close();
                break;
        }
    }
}

