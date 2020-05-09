#include<iostream>
#include<SFML\graphics.hpp>
/*#ifndef ballCPP
    #define ballCPP
    #include"ball.cpp"
#endif // ballCPP*/

using namespace std;
using namespace sf;
namespace plSp{
    const float playerFieldWidR=.02;
    const float playerSize=playerFieldWidR*3;
    const float playerOtlnSzR=.2;//outline size ratio
    const float posIncUnit=playerSize*.05;
    const float drag=.01;
    const float vibrtn=.005;
}
extern const float fieldScale;
extern sf::Vector2i FieldCenter;

class player{
public:
    //Sprite jerseyS;
    player():v_posInField(sf::Vector2f(7,7)),v_posInWin(sf::Vector2f(7,7)){
        MaxSpeed=10.0f;
        velocity=sf::Vector2f(0,0);
        Cir.setPointCount(20);
        Cir.setRadius(plSp::playerSize);
        Cir.setOrigin(plSp::playerSize*(1-plSp::playerOtlnSzR),plSp::playerSize*(1-plSp::playerOtlnSzR));
        Cir.setFillColor(Color(255,0,0,100));
        Cir.setOutlineThickness(plSp::playerSize*plSp::playerOtlnSzR);
        Cir.setOutlineColor(Color(0,255,0,100));
        Cir.scale(fieldScale,fieldScale);
        Scale=sf::Vector2f((2-plSp::playerSize)*fieldScale,(1.5-plSp::playerSize)*fieldScale);
        //(fieldScale*2-plSp::playerSize-playerOutline,fieldScale*1.5-plSp::playerSize-playerOutline);
    }
    void setName(string naam){
        name=naam;
    }
    void setNum(short int anka){
        num=anka;
    }
    void setPosition(){
        setPosition(v_posInField);
    }
    void setPosition(sf::Vector2f v){
        v_posInField=v;
        setPositionI();
    }
    void incPosition(float x=1,float y=1,int virt=0){
        if(x==0&&y==0)
            v_posInWin=posInWin;
        else
        {
            incPositionLow(virt,x,y);
        }

    }
    /*void incSpeed(float x,float y){
        velocity.x+=x;
        velocity.y+=y;
        setSpeed();
    }*/
    void incSpeed(Vector2f inputSpeed){
        inputSpeed.x*=.1;inputSpeed.y*=.1;
        velocity += inputSpeed;
        velocity-=velocity*plSp::drag;
        if(velocity.x>-1*plSp::vibrtn&&velocity.x<plSp::vibrtn){
            velocity.x=0;
        }
        if(velocity.y>-1*plSp::vibrtn&&velocity.y<plSp::vibrtn){
            velocity.y=0;
        }
        setSpeed();
    }
    void setSpeed(float x,float y){
        velocity.x=x;
        velocity.y=y;
        setSpeed();
    }
    void setSpeed(Vector2f inputSpeed){
        velocity=inputSpeed;
        setSpeed();
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
    sf::Vector2f operator-(player p){
        return (sf::Vector2f(v_posInWin.x-p.v_posInWin.x,v_posInWin.y-p.v_posInWin.y));
    }
    sf::Vector2f getSpeed() { return velocity; }

private:
    void incPositionLow(int virt, float x=0,float y=0){                      //(int x=1,int y=1){
        v_posInField=posInField;
        v_posInField.x+=x*plSp::posIncUnit*velocity.x;
        v_posInField.y+=y*plSp::posIncUnit*velocity.y;
        setPositionI(virt);
        //cout << " Move: (" << x << " , " << y << ")\n";
    }
    inline void update_posInWin(){
        posInWin=sf::Vector2f(FieldCenter.x+posInField.x*Scale.x,FieldCenter.y+posInField.y*Scale.y);
    }
    inline void update_vposInWin(){
        v_posInWin=sf::Vector2f(FieldCenter.x+v_posInField.x*Scale.x,FieldCenter.y+v_posInField.y*Scale.y);
    }
    void setPositionI(int virt=0){
        int change=1;
        if(v_posInField.x<-1||v_posInField.x>1){
            change=0;//posInField.x=(posInField.x>1)?1:-1;
        }
        if(v_posInField.y<-1||v_posInField.y>1){
            change=0;//posInField.y=(posInField.y>1)?1:-1;
        }
        if(change){
            if(!virt){
                posInField=v_posInField;
                update_posInWin();

                Cir.setPosition(posInWin);
            }
            else
                update_vposInWin();
        }
    }
    void setSpeed(){
        velocity.x=(velocity.x<-1*MaxSpeed)?-1*MaxSpeed:velocity.x;
        velocity.x=(velocity.x>MaxSpeed)?MaxSpeed:velocity.x;
        velocity.y=(velocity.y<-1*MaxSpeed)?-1*MaxSpeed:velocity.y;
        velocity.y=(velocity.y>MaxSpeed)?MaxSpeed:velocity.y;
    }

    string name;
    short int num;
    //Texture jerseyT;
    sf::Vector2f posInField;
    sf::Vector2f posInWin;
    sf::Vector2f v_posInField;
    sf::Vector2f v_posInWin;
    CircleShape Cir;
    float MaxSpeed;
    sf::Vector2f velocity;
    sf::Vector2f Scale;
    //friend sf::Vector2f teamoperator-(player a,player b);
};

