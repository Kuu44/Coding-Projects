#include<iostream>
#include<SFML\graphics.hpp>
#include<cmath>
#ifndef ballCPP
    #define ballCPP
    #include"ball.cpp"
#endif // ballCPP

#ifndef playerCPP
    #define playerCPP
    #include"player.cpp"
#endif // playerCPP

using namespace std;
using namespace sf;

const int TeamSize=7;
extern const float posIncUnit;
extern const float playerSize;
extern const float fieldScale;
const int ch_aktv_count_M=777*.7*.7*.7;

class team{
public:
    
    team(string naam,int s):name(naam),side(s),ch_aktv_flag(1){
        formationToSet = 2;
        side=(side>=0)?-1:1;
        for(int i=0;i<TeamSize;i++){
            //passSpeed=25.0f;
            
            players[i].setName(string(1,'A'+i));
            players[i].setNum(i+1);
           
            players[i].set_ALPHA_MODE(true);

            players[i].setIcolor((side==1)?Color(255,0,0,100):Color(0,0,255,100));

            players[i].setPosition(formationsDef[formationToSet][i]);
            players[i].set_alpha_pos(formationsDef[formationToSet][i]);
            
        }
        aktv=0;
    }
    void set_name(string naam){
        name=naam;
    }
    void move(float x,float y,team* an_team,ball* football){
        for(int i=0;i<TeamSize;i++){
            if(noCollisionAfter(x,y,an_team,i)){
                players[i].setPosition();
            }
        }
        /*else
        {
           // players[aktv].setSpeed(-players[aktv].getSpeed());
        }*/
    }
    void giveInput(Keyboard::Key left,Keyboard::Key right,Keyboard::Key up,Keyboard::Key down,Keyboard::Key changeKey,Keyboard::Key passKey,team* an_team,ball* football,float deltaTime,team* T)
    {
        Vector2f input(0,0);
        for(int i=0;i<TeamSize;i++){
            if(i!=aktv) players[i].set_directions(und);
        }
        if(Keyboard::isKeyPressed(left)){
            input.x=-1;
            players[aktv].set_directions(dayan);
        }
        //else{players[aktv].set_directions(und);}
        if(Keyboard::isKeyPressed(right)){
            input.x=1;
            players[aktv].set_directions(bayan);
        }
        //else{players[aktv].set_directions(und);}
        if(Keyboard::isKeyPressed(up)){
            input.y=-1;
            players[aktv].set_directions(mathi);
        }
        //else{players[aktv].set_directions(und);}
        if(Keyboard::isKeyPressed(down)){
            input.y=1;
            players[aktv].set_directions(muni);
        }
        //else{players[aktv].set_directions(und);}
        if(Keyboard::isKeyPressed(passKey)){
            players[aktv].setFlag(!(players[aktv].getFlag(pass)),pass);
            Vector2f direction = football->getPosInWin()- players[aktv].get_posInWin();
           
        }
        //Attack Mode
        if (football->getCurrentSide() == (side+1)) 
        {
            int n1 = 0, n2 = 0;
            float distances[TeamSize];
            for (int i = 0; i < TeamSize; i++)
            {
                for (int j = 0; j < TeamSize; j++) {
                    distances[j] = magnitude(players[i].getFieldPosition() - T->players[j].getFieldPosition());
                }

                for (int j = 0; j < TeamSize; j++)
                {
                    if (distances[n1] > distances[j]) n1 = j;
                }
                for (int j = 0; j < TeamSize; j++)
                {
                    if (j == n1) break;
                    if (distances[n2] > distances[j]) n1 = j;
                }

                sf::Vector2f newTargetPosition,v1,v2;
                v1 = T->players[n1].getFieldPosition() - football->getFieldPosition();
                v2 = T->players[n2].getFieldPosition() - football->getFieldPosition();
                newTargetPosition = football->getFieldPosition()+ v1 + v2;

                if (playerType[formationToSet][i]==2) 
                {
                    players[i].set_alpha_pos((side*0.1*-1), players[i].getFieldPosition().y); cout << "Side: " << side << " Defender: P" << i <<endl;
                }
                else if (playerType[formationToSet][i] == 3) 
                { 
                    players[i].set_alpha_pos((formationsDef[formationToSet][i])); cout << "Side: " << side << " GK: P" << i << endl;
                }
                else 
                {
                    players[i].set_alpha_pos(newTargetPosition); cout << "Attacker: " << i << endl; 
                }
                //cout << "AttackerSide: "<<side<<"Current P:" << i << "Pos: (" << players[i].getFieldPosition().x << " , " << players[i].getFieldPosition().y <<")"<< endl;
            }
            //system("pause");
        }
        
        //Defensive mode
        else {
            for (int i = 0; i < TeamSize; i++) {
                float range = 0.1f;
                if (
                    (football->getFieldPosition().x < (players[i].getFieldPosition().x + range)
                        && football->getFieldPosition().x >(players[i].getFieldPosition().x - range))
                    && (football->getFieldPosition().y<(players[i].getFieldPosition().y + range)
                        && football->getFieldPosition().y >(players[i].getFieldPosition().y - range))
                    &&
                    (
                    (players[i].getFieldPosition().x < (formationsDef[formationToSet][i].x + (range * 3))
                        && players[i].getFieldPosition().x >(formationsDef[formationToSet][i].x - (range * 3)))
                        && (players[i].getFieldPosition().y<(formationsDef[formationToSet][i].y + (range * 3))
                            && players[i].getFieldPosition().y >(formationsDef[formationToSet][i].y - (range * 3)))
                        ))
                {
                    players[i].set_alpha_pos(football->getFieldPosition());
                }
                else
                {
                    players[i].set_alpha_pos(formationsDef[formationToSet][i]);
                }
            }
        }
        //testing done

        if(Keyboard::isKeyPressed(changeKey)){
            if(ch_aktv_flag){
                inc_aktv();
                ch_aktv_flag=0;
            }
        }
        else{
            ch_aktv_flag=1;
        }
        for(int i=0;i<TeamSize;i++){
            int tmp=0;
            if(i==aktv)
                tmp=1;
            players[i].incSpeed(input*(deltaTime*tmp));
        }
        //Vector2f currentMove = players[aktv].getSpeed() * deltaTime.asSeconds();
        move(deltaTime,deltaTime,an_team,football);

        /*if(input.x==0 && input.y==0)
        {
            cout << "noPress\n";
        }*/

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
    void check(ball* football)
    {
        for(int i=0;i<TeamSize;i++){
            //football->withBall(players+i);
                //return 1;
        }
    }
    

private:
    static sf::Vector2f makeUnitVector(Vector2f v)
    {
        float mag = magnitude(v);
        return Vector2f(v.x / mag, v.y / mag);
    }
    static float magnitude(sf::Vector2f v)
    {
        return sqrt((v.x * v.x) + (v.y * v.y));
    }
    int noCollisionAfter(float x,float y,team* an_team,int this_pl_N=-1) {
        if(!(this_pl_N>=0&&this_pl_N<TeamSize))
            this_pl_N=aktv;
        int i=0;
        int j=0;
        player* P[2]={players,an_team->players};
        players[this_pl_N].incPosition(x,y,1); //1 for affecting v_*** variables only >< default value is 0
        while(i<TeamSize)
        {
            if(j==0&&i==this_pl_N)
            {
                i++;
                continue;
            }
            P[j][i].incPosition(0,0); //this must always be called before wCollide to initialise the v_*** variables of required player to the desired value
            if(wCollide(players[this_pl_N],P[j][i])){
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
        sf::Vector2f tmp(0,0);
        sf::Vector2f tmpVel_a=a.getSpeed();
        float pS=playerSize*fieldScale;
        if(just.x<=2*pS&&just.x>=-2*pS){                   //Ignore-->//If we replace either of the ps in this line with playerSize, we get an exception
            if(just.y<=2*pS&&just.y>=-2*pS){
                if(just.x>0)
                    tmp.x=(tmpVel_a.x<0)?0:tmpVel_a.x;
                else if(just.x<0)
                    tmp.x=(tmpVel_a.x>0)?0:tmpVel_a.x;
                if(just.y>0)
                    tmp.y=(tmpVel_a.y<0)?0:tmpVel_a.y;
                else if(just.y<0)
                    tmp.y=(tmpVel_a.y>0)?0:tmpVel_a.y;
                a.setSpeed(tmp);
                //cout<<just.x<<"\t"<<tmp.x<<" , "<<a.getSpeed().y<<"\n";
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
    bool ch_aktv_flag;
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
    //bool passFlag[TeamSize];
    //bool shootFlag[TeamSize];
    //float passSpeed;
};
