#include<iostream>
#include<SFML\graphics.hpp>

using namespace std;
using namespace sf;

const float ballFieldWidR=.02;
const float ballSize=ballFieldWidR*3;
const float ballOtlnSzR=.2;//outline size ratio
const float b_posIncUnit=ballSize*.05;
extern const float fieldScale;
extern sf::Vector2i FieldCenter;

class ball{
public:
    //Sprite jerseyS;
    ball():v_posInField(sf::Vector2f(7,7)),v_posInWin(sf::Vector2f(7,7)){
        MaxSpeed=100.0f;
        velocity=sf::Vector2f(0,0);
        Cir.setPointCount(20);
        Cir.setRadius(ballSize);
        Cir.setOrigin(ballSize*(1-ballOtlnSzR),ballSize*(1-ballOtlnSzR));
        Cir.setFillColor(Color(255,0,0,100));
        Cir.setOutlineThickness(ballSize*ballOtlnSzR);
        Cir.setOutlineColor(Color(0,255,0,100));
        Cir.scale(fieldScale,fieldScale);
        Scale=sf::Vector2f((2-ballSize)*fieldScale,(1.5-ballSize)*fieldScale);//(fieldScale*2-ballSize-ballOutline,fieldScale*1.5-ballSize-ballOutline);
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
        else{
            incPositionLow(virt,x,y);
           
        }
    }
    void incSpeed(float x,float y){
        velocity.x+=x;
        velocity.y+=y;
        //setSpeed();
    }
    void setSpeed(float x,float y){
        velocity.x=x;
        velocity.y=y;
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
    sf::Vector2f operator-(ball p){
        return (sf::Vector2f(v_posInWin.x-p.v_posInWin.x,v_posInWin.y-p.v_posInWin.y));
    }
    void updatePosition(float deltaTime)
    {
        move();
        increasePosition(velocity*deltaTime);
        applyDrag(deltaTime);
    }
    void applyDrag(float deltaTime) 
    {
        velocity -= (1.0f*deltaTime*velocity);
    }
    void move()
    {       
        Vector2f input(0,0);
        float speed = 10.0f;
        if (Keyboard::isKeyPressed(Keyboard::Key::J)) {
            input.x += -speed;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::L)) {
            input.x += speed;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::I)) {
            input.y += -speed;
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::K)) {
            input.y += speed;
        }       
        cout << "\nSpeed:(" << velocity.x << " ," << velocity.y << " )";
        incSpeed(input.x, input.y);
    }
    void increasePosition(sf::Vector2f changeV)
    {
        sf::Vector2f changedV(Cir.getPosition()+changeV);
        Cir.setPosition(changedV);
        cout << "\n X: " << changedV.x << " Y:" << changedV.y;
    }
private:
    void incPositionLow(int virt, float x=0,float y=0){                      //(int x=1,int y=1){
        v_posInField=posInField;
        v_posInField.x+=velocity.x*x*b_posIncUnit;
        v_posInField.y+=velocity.y*y*b_posIncUnit;
        setPositionI(virt);
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
    int MaxSpeed;
    sf::Vector2f velocity;
    sf::Vector2f Scale;
    //friend sf::Vector2f teamoperator-(ball a,ball b);
};

