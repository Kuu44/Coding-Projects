//camera zoom mode
#include<iostream>
#include<SFML\graphics.hpp>
#include<fstream>
#include "game.cpp"
#include "Menu.h"

using namespace std;
using namespace sf;

const int CheckPeriodms=15;
const int RefreshTimeMaxms=1;
const int Time_BufsPerInput=10;
const float ProcessTimeMaxms=CheckPeriodms-RefreshTimeMaxms;//+Time_BufsPerInput;
const int max_toBdrawn=20;
const int winLen=1920;
const int winWid=1080;
const float fieldScale=winWid/3*.7;
const int deltaTime=17;

sf::Vector2i FieldCenter(winLen/2,winWid/2);

//Drawable toBdrawn[];
enum formation {attack,defense,hold};

//int gameEventHandle(Event event);

int main()
{
    Mainmenu m;
    TeamSelect t;
    sf::RenderWindow w(sf::VideoMode(winLen,winWid),"Main Menu",Style::Default);
    int i=m.mainmenu(w);
    w.setTitle("Formations");
    t.teamselect(w,i);
    w.setTitle("Foo2Y");
    //w.setFramerateLimit(20);
    Clock frameClock;
    w.clear();
    sf::Event event;//,event1;
    game g;
    Clock clk;
    int jhanda;
    while(w.isOpen()){
        while(frameClock.getElapsedTime().asMilliseconds()<deltaTime){
            if(w.pollEvent(event)){
                if(event.type==Event::Closed)
                    w.close();
            }
        }
        g.playerskeyUpdate(.001*deltaTime);
        jhanda=g.ballUpdate(.001*deltaTime);
        if(jhanda==7||jhanda==-7){
                break;
        }
        g.refresh(&w);
        while(clk.getElapsedTime().asMilliseconds()<=CheckPeriodms);
        clk.restart();
        frameClock.restart();
        //cout << "\n"<<deltaTime.asSeconds();
    }
    Texture text;
    if(jhanda==7){
        if(!text.loadFromFile("TeamA.png"))
            cout<<"teamA image failed";
        }
    else if(jhanda==-7){
            if(!text.loadFromFile("TeamB.png"))
                cout<<"teamB image failed";
    }
    Sprite s;
    s.setTexture(text);
    while(w.isOpen()){
            w.clear();
            w.draw(s);
            w.display();
            if(w.pollEvent(event)){
                if(event.type==Event::Closed)
                    w.close();
            }
    }
return 0;
}
