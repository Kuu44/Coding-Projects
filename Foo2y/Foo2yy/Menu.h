#pragma once
#include<iostream>
#include<SFML\graphics.hpp>
class Menu
{
public:
    static int mainmenu(sf::RenderWindow&);
    static int teamselect(sf::RenderWindow& window1, int i);
};


