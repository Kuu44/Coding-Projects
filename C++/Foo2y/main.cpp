//camera zoom mode

#include<iostream>
#include<SFML\graphics.hpp>
#include<GL\glew.h>
#include "inc\LoadShaders.h"

using namespace std;
using namespace sf;

const int CheckPeriodms=20;
const int RefreshTimeMaxms=30;
const int Time_BufsPerInput=0;//this doesnot sem to affect performance but why??
const int ProcessTimeMaxms=CheckPeriodms-RefreshTimeMaxms;
const int max_toBdrawn=20;
const int TeamSize=7;
const int winLen=1920/2;
const int winWid=1080/2;
const int fieldScale=winWid/3*.95;
const float playerFieldWidR=.02;
const float playerSize=playerFieldWidR*3;
const float playerOtlnSzR=.1;//outline size ratio
const float posIncUnit=playerSize*.04;
sf::Vector2i FieldCenter(winLen/2,winWid/2);
sf::Vector2f Scale((2-playerSize)*fieldScale,(1.5-playerSize)*fieldScale);//(fieldScale*2-playerSize-playerOutline,fieldScale*1.5-playerSize-playerOutline);
//Drawable toBdrawn[];
enum formation {attack,defense,hold};



void init();
void display();
int gameEventHandle(Event event);

class player{
public:
    //Sprite jerseyS;
    player(){
        MaxSpeed=7;
        Speed=sf::Vector2i(3,3);
        Cir.setPointCount(20);
        Cir.setRadius(playerSize);
        Cir.setOrigin(playerSize*(1-playerOtlnSzR),playerSize*(1-playerOtlnSzR));
        Cir.setFillColor(Color(255,0,0,100));
        Cir.setOutlineThickness(playerSize*playerOtlnSzR);
        Cir.setOutlineColor(Color(0,255,0,100));
        Cir.scale(fieldScale,fieldScale);
    }
    void setName(string naam){
        name=naam;
    }
    void setNum(short int anka){
        num=anka;
    }
    void setPosition(sf::Vector2f v){
        posInField=v;
        setPosition();
    }
    void incPosition(int x=1,int y=1){
        posInField.x+=Speed.x*x*posIncUnit;
        posInField.y+=Speed.y*y*posIncUnit;
        setPosition();
    }
    void incSpeed(int x,int y){
        Speed.x+=(MaxSpeed>=(Speed.x+x)&&(Speed.x+x)>0)?x:0;
        Speed.y+=(MaxSpeed>=(Speed.y+y)&&(Speed.y+y)>0)?y:0;
    }
    void setOcolor(Color Oc){
        Cir.setOutlineColor(Oc);
    }
    void setIcolor(Color Ic){
        Cir.setFillColor(Ic);
    }
    void draw(RenderWindow* tar) const{
        tar->draw(Cir);
    }
private:
    inline void update_posInWin(){
        posInWin=sf::Vector2f(FieldCenter.x+posInField.x*Scale.x,FieldCenter.y+posInField.y*Scale.y);
    }
    void setPosition(){
        if(posInField.x<-1||posInField.x>1){
            posInField.x=(posInField.x>1)?1:-1;
        }
        if(posInField.y<-1||posInField.y>1){
            posInField.y=(posInField.y>1)?1:-1;
        }
        update_posInWin();
        Cir.setPosition(posInWin);
    }
    string name;
    short int num;
    //Texture jerseyT;
    sf::Vector2f posInField;
    sf::Vector2f posInWin;
    CircleShape Cir;
    int MaxSpeed;
    sf::Vector2i Speed;
};

class team{
public:
    team(string naam,int s):name(naam),side(s){
        side=(side>=0)?1:-1;
        for(int i=0;i<TeamSize;i++){
            players[i].setName(string(1,'A'+i));
            players[i].setNum(i+1);
            switch(i){
            case 0:
                players[i].setPosition(Vector2f(side*.1,0));
                break;
            case 1:
                players[i].setPosition(Vector2f(side*.4,.5));
                break;
            case 2:
                players[i].setPosition(Vector2f(side*.4,-.5));
                break;
            case 3:
                players[i].setPosition(Vector2f(side*.7,.7));
                break;
            case 4:
                players[i].setPosition(Vector2f(side*.7,0));
                break;
            case 5:players[i].setPosition(Vector2f(side*.7,-.7));
                break;
            case 6:players[i].setPosition(Vector2f(side*.9,0));
                break;
            }
        }
        aktv=0;
    }
    void set_name(string naam){
        name=naam;
    }
    void move(int x,int y){
        players[aktv].incPosition(x,y);
    }
    void draw(RenderWindow* tar){
        for(int i=0;i<TeamSize;i++)
            players[i].draw(tar);
    }
    void set_aktv(){}
private:
    int formation;
    int side;
    player players[TeamSize];//field1.jpg","img//field1.jpg",};
    int aktv;
    string name;

};
class Field{
public:
    Field(){
        set();
        FieldS.setTexture(FieldT);
        FieldS.setOrigin(1367/2,937/2);
        FieldS.scale(fieldScale*float(4)/1367,fieldScale*float(3)/937);//--(4) | (3)
        //FieldS.setOrigin(4*fieldScale,3*fieldScale);
        FieldS.setPosition(Vector2f(FieldCenter));
    }
    void draw(RenderTarget* tar){
        //FieldS.scale(fieldScale,fieldScale);
        //FieldS.scale(fieldScale,fieldScale);
        tar->draw(FieldS);
    }
    void set(){
        if(!FieldT.loadFromFile("img\\field1.jpg"))
            cout<<"err loading texture";
    }
private:
    Texture FieldT;
    Sprite FieldS;
};

class game{
public:
    game():A("A",1),B("B",-1){
        //A.players[0].setPosition(Vector2f(0,0));
    }
    void play();
    void pause();
    void refresh(RenderWindow* w){
        w->clear();
        field.draw(w);
        A.draw(w);
        B.draw(w);
        w->display();
    }
    int eventHandle(Event);
private:
    team A;
    team B;
    Field field;
    float time;
};
int main()
{
    sf::RenderWindow w(sf::VideoMode(winLen,winWid),"Foo2Y",Style::Default);
    w.clear();
//initialise glew
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    //cout>>"Status: Using GLEW %s\n"<<glewGetString(GLEW_VERSION);
    //cout<<"Opengl version: "<<glGetString(GL_VERSION);
    sf::Event event,event1;
    game g;
    Clock clk;
    while(w.isOpen()){/*
        while(w.pollEvent(event)){
            if(event.type==Event::Closed)
                w.close();
            else
                g.eventHandle(event);
            if(clk.getElapsedTime().asMilliseconds()>=80){
                g.refresh(&w);
                clk.restart();
            }
        }
        if(clk.getElapsedTime().asMilliseconds()>=80){
                g.refresh(&w);
                clk.restart();
        }*/
        w.pollEvent(event);
        while(w.pollEvent(event1)&&event.type==(event=event1).type){
            if(clk.getElapsedTime().asMilliseconds()>=Time_BufsPerInput){
                //clk.restart();
                break;
            }
        }
        g.eventHandle(event);
        while(clk.getElapsedTime().asMilliseconds()<=ProcessTimeMaxms);
        g.refresh(&w);
        while(clk.getElapsedTime().asMilliseconds()<=CheckPeriodms);
        clk.restart();
    }
return 0;
}

int game::eventHandle(Event event){
    switch(event.type){
    case Event::KeyPressed:
        switch(event.key.code){
        case Keyboard::Left:
            A.move(-1,0);
            break;
        case Keyboard::Right:
            A.move(1,0);
            break;
        case Keyboard::Up:
            A.move(0,-1);
            break;
        case Keyboard::Down:
            A.move(0,1);
            break;
        default:
            ;
        }
    case Event::MouseButtonPressed:

    default:
        ;
    }
}
/*
    if(event.type==sf::Event::Closed){
        return 1;
    }
    else if(event.type==sf::Event::Resized){
        //w.setSize(w.getSize());
    }
    else if(event.type==sf::Event::MouseButtonPressed){

    }/*
    else if(event.type==Event::KeyPressed){
        if(event.key.code==Keyboard::A){
            sf::Vector2f pos=player.getPosition();
                player.setPosition(pos.x-10,pos.y);
        }
        else if(event.key.code==Keyboard::D){
            sf::Vector2f pos=player.getPosition();
                player.setPosition(pos.x+10,pos.y);
        }
        else if(event.key.code==Keyboard::S){
            sf::Vector2f pos=player.getPosition();
                player.setPosition(pos.x,pos.y+10);
        }
        else if(event.key.code==Keyboard::W){
            sf::Vector2f pos=player.getPosition();
                player.setPosition(pos.x,pos.y-10);
        }
        else if(event.key.code==Keyboard::R){
            if(event.key.shift)
                player.setRotation(player.getRotation()-10);
            else
                player.setRotation(player.getRotation()+10);
        }
        else if(event.key.code==Keyboard::Q){

        }*/

/*
int gameExecute(Window& w){
    Event event;
//Handle Events
    while(w.pollEvent(event)){
        if(event.type=Event::Closed)
            return -1;
        else if(event.type==Event::KeyPressed){
            if(event.key=='a'){}
            else if(event.key=='d'){player.}
            else if(event.key=='w'){}
            else if(event.key=='s'){}
        }
    }
//draw
return 0;
}
/*
CircleShape player(77,77);
player.setFillColor(Color::Red);
player.setPosition(200,300);
w.draw(player);
sf::VideoMode::getFullscreenModes
(

)
*/


