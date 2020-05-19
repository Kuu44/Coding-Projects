#include<iostream>
#include<SFML\graphics.hpp>
#include"ball.cpp"
#include"player.cpp"

using namespace std;
using namespace sf;

const int TeamSize=7;
extern const float posIncUnit;
extern const float playerSize;
extern const float fieldScale;

class team{
public:
    team(string naam,int s):name(naam),side(s){
        side=(side>=0)?1:-1;
        for(int i=0;i<TeamSize;i++){
            players[i].setName(string(1,'A'+i));
            players[i].setNum(i+1);

            players[i].setIcolor((side==1)?Color(255,0,0,100):Color(0,0,255,100));

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
            case 5:
                players[i].setPosition(Vector2f(side*.7,-.7));
                break;
            case 6:
                players[i].setPosition(Vector2f(side*.9,0));
                break;
            }
        }
        aktv=0;
    }
    void set_name(string naam){
        name=naam;
    }
    void move(float x,float y,team* an_team,ball* football){
        if(noCollisionAfter(x,y,an_team)){
            players[aktv].setPosition();
        }
        else
        {
           // players[aktv].setSpeed(-players[aktv].getSpeed());
        }
    }
    void giveInput(Keyboard::Key left,Keyboard::Key right,Keyboard::Key up,Keyboard::Key down,Keyboard::Key changeKey,team* an_team,ball* football,Time deltaTime)
    {
        Vector2f input(0,0);
        float speed=0.5f;
        if(Keyboard::isKeyPressed(left)){
            input.x=-speed;
        }
        if(Keyboard::isKeyPressed(right)){
            input.x=speed;
        }
        if(Keyboard::isKeyPressed(up)){
            input.y=-speed;
        }
        if(Keyboard::isKeyPressed(down)){
            input.y=speed;
        }
        if(Keyboard::isKeyPressed(changeKey)){
            inc_aktv();
        }

        players[aktv].incSpeed(input);
        Vector2f currentMove = players[aktv].getSpeed() * deltaTime.asSeconds();;
        move(currentMove.x,currentMove.y,an_team,football);

        if(input.x==0 && input.y==0)
        {
            cout << "noPress\n";
        }

       // cout << " Move: (" << currentMove.x << " , " << currentMove.y << ")\n";
        //move(input.x,input.y,an_team,football);

        //return players;
    }
    void update(){
        for(int i=0;i<TeamSize;i++){
            players[i].incPosition();
        }
    }
    void draw(RenderWindow* tar){
        for(int i=0;i<TeamSize;i++)
            players[i].draw(tar);
    }
    void inc_aktv(){
        aktv=(aktv==TeamSize-1)?0:(aktv+1);
    }
    player* check()
    {
        return 0;
    }

private:
    int noCollisionAfter(float x,float y,team* an_team) {
        int i=0;
        int j=0;
        player* P[2]={players,an_team->players};
        players[aktv].incPosition(x,y,1); //1 for affecting v_*** variables only >< default value is 0
        
        
        while(i<TeamSize)
        {
            if(j==0&&i==aktv)
            {
                i++;
                continue;
            }
            P[j][i].incPosition(0,0); //this must always be called before wCollide to initialise the v_*** variables of required player to the desired value
            if(wCollide(players[aktv],P[j][i])){
                return 0;
            }
            i++;
            if(j==0&&i==TeamSize)
            {
                i=0;
                j++;
            }
        }
    return 1;
    }
    int wCollide(player& a,player& b){
        sf::Vector2f just=a-b;
        float pS=playerSize*fieldScale;
        if(just.x<=2*pS&&just.x>=-2*pS){
            if(just.y<=2*pS&&just.y>=-2*pS){                    //Ignore-->//If we replace either of the ps in this line with playerSize, we get an exception
                return 1;
            }
        }
    return 0;
    }
    string name;
    int formation;
    int side;
    player players[TeamSize];//field1.jpg","img//field1.jpg",};
    int aktv;
};
