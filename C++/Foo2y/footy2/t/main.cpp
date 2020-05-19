//camera zoom mode
#include<iostream>
#include<SFML\graphics.hpp>
#include "game.cpp"

using namespace std;
using namespace sf;

const int CheckPeriodms=15;
const int RefreshTimeMaxms=1;
const int Time_BufsPerInput=10;
const float ProcessTimeMaxms=CheckPeriodms-RefreshTimeMaxms;//+Time_BufsPerInput;
const int max_toBdrawn=20;

const int winLen=1920/2;
const int winWid=1080/2;
const float fieldScale=winWid/3*.95;
sf::Time deltaTime;

sf::Vector2i FieldCenter(winLen/2,winWid/2);

//Drawable toBdrawn[];
enum formation {attack,defense,hold};

//int gameEventHandle(Event event);


int main()
{
    sf::RenderWindow w(sf::VideoMode(winLen,winWid),"Foo2Y",Style::Default);
    w.setFramerateLimit(20);
    Clock frameClock;
    w.clear();
    sf::Event event,event1;
    game g;
    Clock clk;
    while(w.isOpen()){
        while(clk.getElapsedTime().asMilliseconds()<=ProcessTimeMaxms){
            int yesEvent=1;
            if(event.type!=event1.type){
                yesEvent=1;
                event=event1;
            }
            else if(w.pollEvent(event1)){
                event=event1;                                  //this is required
                yesEvent=1;
                while(event.type==event1.type){                //event.type==(event=event1).type){//this doesnot work and always returns true
                    if(!w.pollEvent(event1)){
                        break;
                    }
                    if(clk.getElapsedTime().asMilliseconds()>=Time_BufsPerInput){
                        //clk.restart();
                        break;
                    }
                }
            }
            else{
                yesEvent=0;
            }
            if(yesEvent){
                //g.eventHandle(event);
            }
            g.playerskeyUpdate(deltaTime);
        }


        g.ballUpdate(deltaTime);
        g.refresh(&w);
        while(clk.getElapsedTime().asMilliseconds()<=CheckPeriodms);
        clk.restart();
        deltaTime = frameClock.restart();
        //cout << "\n"<<deltaTime.asSeconds();
    }

return 0;
}




