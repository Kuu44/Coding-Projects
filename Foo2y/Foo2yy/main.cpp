//camera zoom mode
#include<iostream>
#include<SFML\graphics.hpp>
#include<fstream>
#include "game.h"
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
const int char_sz_1=fieldScale*3/13*.8;

sf::Vector2i FieldCenter(winLen/2,winWid/2-(winWid-fieldScale*3)*.5f);

enum formation {attack,defense,hold};


int main()
{
    Menu m;
    sf::RenderWindow w(sf::VideoMode(winLen,winWid),"Main Menu",Style::Default);
    int i=0;
    i=m.mainmenu(w);
    if(i!=0){
        w.close();
        return 0;
    }
    w.setTitle("Formations");
    i=m.teamselect(w,i);
    if(i!=0){
        w.close();
        return 0;
    }
    w.setTitle("Foo2Y");
    Clock frameClock;
    w.clear();
    sf::Event event;
    game g;
    Clock clk;
    int jhanda;
    sf::Font font;
    if(!font.loadFromFile("Fonts\\Arial.TTF")){
        cout<<"Failed to load font";
    }
    sf::Text txt1;
    txt1.setFont(font);
    txt1.setString("\t\t  W\n\t  A\t   D\n\t\t  S\n\tE to pass\n\t\tQ to\nChange Player");
    txt1.setOrigin(txt1.getLocalBounds().width*.5*float(char_sz_1)/30,0);//txt1.getLocalBounds().height*.5*float(char_sz_1)/30);
    txt1.setPosition((winLen-fieldScale*4.65)*.25f,winWid*.05);
    txt1.setCharacterSize(char_sz_1);
    txt1.setFillColor(Color::Blue);
    sf::Text txt2;
    txt2.setFont(font);
    txt2.setString("\t\t   I\n\t  J\t    L\n\t\t  K\n\tO to pass\n\t\tU to\nChange Player");
    txt2.setFillColor(Color::Red);
    txt2.setOrigin(txt2.getLocalBounds().width*.5*float(char_sz_1)/30,0);//txt2.getLocalBounds().height*.5*float(char_sz_1)/30);
    txt2.setPosition(winLen-(winLen-fieldScale*4.65)*.25f,winWid*.05);//FieldCenter.y*);
    txt2.setCharacterSize(char_sz_1);
    sf::Text txt3;
    txt3.setFont(font);
    txt3.setCharacterSize(char_sz_1*.5);
    txt3.setString("\t\t\t\tIf your team\n\tdoes not possess the ball,\n\t  move towards a player,\nand you can control that player\nif you change player(press Q).\n\n\t  Move in the direction \n  in which you want to pass,\n\t\t   and press E\n   to pass in that direction.");
    txt3.setOrigin(txt3.getLocalBounds().width*.5*float(char_sz_1*.5)/30,0);//txt3.getLocalBounds().height*.5*float(char_sz_1)/30);
    txt3.setPosition((winLen-fieldScale*4.65)*.215f,txt1.getPosition().y-txt1.getOrigin().y+txt1.getGlobalBounds().height+winWid*.05);//FieldCenter.y+txt1.getGlobalBounds().height+txt3.getOrigin().y/2.5);
    txt3.setFillColor(Color::Magenta);
    sf::Text txt4;
    txt4.setFont(font);
    txt4.setCharacterSize(char_sz_1*.5);
    txt4.setString("\t\t\t\tIf your team\n\tdoes not possess the ball,\n\t   Move towards a player,\nand you can control that player\n if you change player(press U).\n\n\t\tMove in the direction \n\tin which you want to pass,\n\t\t\t and press O\n\t to pass in that direction.");
    txt4.setOrigin(txt3.getLocalBounds().width*.5*float(char_sz_1*.5)/30,0);//txt3.getLocalBounds().height*.5*float(char_sz_1)/30);
    txt4.setPosition(winLen-(winLen-fieldScale*4.65)*.29f,txt1.getPosition().y-txt1.getOrigin().y+txt1.getGlobalBounds().height+winWid*.05);//FieldCenter.y+txt1.getGlobalBounds().height+txt3.getOrigin().y/2.5);
    txt4.setFillColor(Color(255,100,100,255));
    sf::Texture cm_B_T;
    sf::Sprite cm_B_S;
    cm_B_T.loadFromFile("img\\commentator_1.jpg");
    cm_B_S.setTexture(cm_B_T);
    cm_B_S.setScale(float(1)/300*(winLen-fieldScale*4.65)*.5f,float(1)/168*(winLen-fieldScale*4.65)*.5f/1.8);
    cm_B_S.setOrigin(cm_B_T.getSize().x,0);
    cm_B_S.setPosition(winLen,0);
    cm_B_S.setColor(Color(255,255,255,200));
    sf::Texture cm_A_T;
    sf::Sprite cm_A_S;
    cm_A_T.loadFromFile("img\\commentator_3.jpg");
    cm_A_S.setTexture(cm_A_T);
    cm_A_S.setScale(float(1)/270*(winLen-fieldScale*4.65)*.5f,float(1)/183*(winLen-fieldScale*4.65)*.5f/1.5/1.2);
    cm_A_S.setPosition(0,0);
    cm_A_S.setColor(Color(255,255,255,200));
    while(w.isOpen()){
        while(frameClock.getElapsedTime().asMilliseconds()<deltaTime){
            if(w.pollEvent(event)){
                if(event.type==Event::Closed)
                    w.close();
            }
        }
        jhanda=g.run(.001*deltaTime,&w);
        if(jhanda==7||jhanda==-7||jhanda==1){
                break;
        }
        w.draw(cm_A_S);
        w.draw(cm_B_S);
        w.draw(txt1);
        w.draw(txt2);
        w.draw(txt3);
        w.draw(txt4);
        w.display();
        while(clk.getElapsedTime().asMilliseconds()<=CheckPeriodms);
        clk.restart();
        frameClock.restart();
    }
    Texture text;
    if(jhanda==7){
        if(!text.loadFromFile("img\\TeamA.png"))
            cout<<"teamA image failed";
        }
    else if(jhanda==-7){
            if(!text.loadFromFile("img\\TeamB.png"))
                cout<<"teamB image failed";
    }
    else if(jhanda==1){
        if(!text.loadFromFile("img\\draw.png"))
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
    //system("cls");
return 0;
}
