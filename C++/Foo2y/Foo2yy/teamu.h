#pragma once
#include<iostream>
#include<SFML\graphics.hpp>
#include<cmath>
#include<cstdlib>
#ifndef ballH
	#define ballH
	#include"ball.h"
#endif // ballCPP

#ifndef playerCPP
#define playerCPP
#include"player.cpp"
#endif // playerCPP

const int TeamSize = 7;
extern const float posIncUnit;
extern const float playerSize;
extern const float fieldScale;
const int ch_aktv_count_M = 777 * .7 * .7 * .7;

class team {
public:
    team(string, int);

    int check(ball*);
    void draw(RenderWindow*);
    void giveInput(Keyboard::Key, Keyboard::Key, Keyboard::Key, Keyboard::Key, 
        Keyboard::Key, Keyboard::Key, team*, ball*, float, team*);
    void inc_aktv();
    void move(float, float, team*, ball*);
    void set_name(string);
    void update();

private:
    static float dot(sf::Vector2f, sf::Vector2f);
    static float getAngle(sf::Vector2f, sf::Vector2f);
    static sf::Vector2f makeUnitVector(Vector2f);
    static float magnitude(sf::Vector2f);
    int noCollisionAfter(float, float, team*, int);
    int wCollide(player&, player&);

    string name;
    int formation;
    int side;
    player players[TeamSize];
    int aktv;
    bool ch_aktv_flag;
    //[0][]= Lolpool, [1][]= BanterLona, [2][]=ChewMentos
    int formationToSet;
    //0=Atk 1=Mid 2=Def 3=GK
    int playerType[3][TeamSize] = {
        //LolPool
        {0,0,0,1,2,2,3},
        //BanterLona
        {0,1,1,1,2,2,3},
        //ChewMentos
        {0,2,2,2,1,1,3}
    };
    //[0][]= Lolpool, [1][]= BanterLona, [2][]=ChewMentos
    sf::Vector2f formationsDef[3][TeamSize]
        = {
        //LolPool
        { Vector2f(side * .1,0),Vector2f(side * .2,-.7),Vector2f(side * .2,.7),Vector2f(side * .4, 0) , Vector2f(side * .7,-.4),Vector2f(side * .7,.4),Vector2f(side * .9,0) },
        //BanterLona
        { Vector2f(side * .1,0),Vector2f(side * .4,-.7),Vector2f(side * .4,.7),Vector2f(side * .4, 0),Vector2f(side * .7,.4),Vector2f(side * .7,-.4), Vector2f(side * .9,0) },
        //ChewMentos
        { Vector2f(side * .1,0),Vector2f(side * .7,.7) ,Vector2f(side * .7,0) ,Vector2f(side * .7,-.7),Vector2f(side * .4,.4),Vector2f(side * .4,-.4), Vector2f(side * .9,0) }
    };
};