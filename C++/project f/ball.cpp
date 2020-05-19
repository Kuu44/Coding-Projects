#include<iostream>
#include<SFML\graphics.hpp>
#ifndef playerCpp
        #define playerCPP
        #include "player.cpp"
#endif // playerCpp

using namespace std;
using namespace sf;
extern const float playerSize;
extern const float fieldScale;
extern sf::Vector2i FieldCenter;

class ball {
public:
    bool possesionTeamA;
    //Sprite jerseyS;
    ball() :v_posInField(sf::Vector2f(7, 7)), v_posInWin(sf::Vector2f(7, 7)),
            ballFieldWidR(.015),ballSize(ballFieldWidR * 3),ballOtlnSzR(.2),b_posIncUnit(ballSize * .05),
            p_and_b((ballSize+playerSize)*fieldScale)
     {
        velocity = sf::Vector2f(0, 0);
        Cir.setPointCount(20);
        Cir.setRadius(ballSize);
        Cir.setOrigin(ballSize * (1 - ballOtlnSzR), ballSize * (1 - ballOtlnSzR));
        Cir.setFillColor(Color(255, 0, 0, 100));
        Cir.setOutlineThickness(ballSize * ballOtlnSzR);
        Cir.setOutlineColor(Color(0, 255, 0, 100));
        Cir.scale(fieldScale, fieldScale);
        MaxSpeed=100;
        SpeedScale=MaxSpeed*.9;
        Scale = sf::Vector2f((2 - ballSize) * fieldScale, (1.5 - ballSize) * fieldScale);//(fieldScale*2-ballSize-ballOutline,fieldScale*1.5-ballSize-ballOutline);
        vibrtn=.0001;
    }
    void setName(string naam) {
        name = naam;
    }
    void setNum(short int anka) {
        num = anka;
    }
    void setPosition() {
        setPosition(v_posInField);
    }
    void setPosition(sf::Vector2f v) {
        v_posInField = v;
        setPositionI();
    }
    void incPosition(float x = 1, float y = 1, int virt = 0) {
        if (x == 0 && y == 0)
            v_posInWin = posInWin;
        else {
            incPositionLow(virt, x, y);
        }
    }
    void incSpeed(float x, float y) {
        velocity.x += x;
        velocity.y += y;
        setSpeed();
    }
    void incSpeed(sf::Vector2f v) {
        velocity += v;
        setSpeed();
    }
    void setSpeed(float x, float y) {
        velocity.x = x;
        velocity.y = y;
        setSpeed();
    }
    void setOcolor(Color Oc) {
        Cir.setOutlineColor(Oc);
    }
    void setIcolor(Color Ic) {
        Cir.setFillColor(Ic);
    }
    void draw(RenderWindow* tar) const {
        tar->draw(Cir);
    }
    sf::Vector2f operator-(ball p) {
        return (sf::Vector2f(v_posInWin.x - p.v_posInWin.x, v_posInWin.y - p.v_posInWin.y));
    }
    void updatePosition(float deltaTime)
    {
        move(deltaTime);
        Vector2f tmpV(velocity * deltaTime);
        incPosition(tmpV.x, tmpV.y);
        //increasePosition(velocity*deltaTime);
        applyDrag(deltaTime);
    }
    void applyDrag(float deltaTime)
    {
        velocity -= ((deltaTime*SpeedScale/MaxSpeed) * velocity);
    }
    void move(float deltaTime)
    {
        Vector2f input(0, 0);
        float speed = 1.0f;
        if (Keyboard::isKeyPressed(Keyboard::J)) {
            input.x += -speed;
        }
        if (Keyboard::isKeyPressed(Keyboard::L)) {
            input.x += speed;
        }
        if (Keyboard::isKeyPressed(Keyboard::I)) {
            input.y += -speed;
        }
        if (Keyboard::isKeyPressed(Keyboard::K)) {
            input.y += speed;
        }
        
        //cout << "\nSpeed:(" << velocity.x << " ," << velocity.y << " )";
        incSpeed(input*(deltaTime*SpeedScale));
    }
    void withBall(player* pl){
        sf::Vector2f tmp=posInWin-pl->get_posInWin();
        //Dribbling Check
                   
        //passBall(pl);
        sf::Vector2f unit_dirN;
        unit_dirN = makeUnitVector(pl->getSpeed());
        if (magnitude(unit_dirN) == 0) {
            unit_dirN = Vector2f(1, 1);
        }
        sf::Vector2f playerToBall = unit_dirN * p_and_b;//makeUnitVector(tmp)*p_and_b;
        prep_playerToBall(playerToBall, unit_dirN, pl);
        sf::Vector2f newPosition = pl->get_posInWin() - Vector2f(FieldCenter) + playerToBall;
        newPosition.x /= Scale.x;
        newPosition.y /= Scale.y;
        setPosition(newPosition);
        std::cout << "\nPos:(" << newPosition.x << " , " << newPosition.y << ")";
       
    }
    bool checkCollision(player* pl) {
        sf::Vector2f tmp = posInWin - pl->get_posInWin();
        if (tmp.x > -1.5 * p_and_b && tmp.x < 1.5 * p_and_b) {
            if (tmp.y > -1.5 * p_and_b && tmp.y < 1.5 * p_and_b) 
            {
                pl->setHasPossesion(true);
                return true;
            }
        }        
        return false;
    }
    void passBall(player *p){
        sf::Vector2f tmpPos(posInWin-p->get_posInWin());
        if(p->getFlag(pass)){
            incSpeed(makeUnitVector(tmpPos)*float(p->get_passSpeed()));
            p->setFlag(false,pass);
        }
    }
    void operator<<(player *p){
        sf::Vector2f tmpPos(posInWin-p->get_posInWin());
        sf::Vector2f tmpVel(p->getSpeed());
        //if(tmpPos>-1*p_and_b&&tmpPos<-p_and_b)

        //setSpeed(velocity.x*-1*(p->get_bounceFac()+tmpVel.x),velocity.y*-1*(p->get_bounceFac()+tmpVel.y));
        //incSpeed(tmpPos.x*.1,tmpPos.y*.1);

    }
    Vector2f getPosInWin()
    {
        return posInWin;
    }
    void setPossesion(bool t) 
    {
        inPossesion = t;
    }
    void linkPossesionTeamA(bool* t) 
    {
        possesionTeamA = t;
    }
private:
    void incPositionLow(int virt, float x = 0, float y = 0) {                      //(int x=1,int y=1){
        v_posInField = posInField;
        v_posInField.x += x * b_posIncUnit;//velocity.x*x*b_posIncUnit; yaha pani velocity le multiply gareko cha so duui choti multiply bhairathyo
        v_posInField.y += y * b_posIncUnit;//velocity.y*y*b_posIncUnit;
        setPositionI(virt);
    }
    inline void update_posInWin() {
        posInWin = sf::Vector2f(FieldCenter.x + posInField.x * Scale.x, FieldCenter.y 
            + posInField.y * Scale.y);
    }
    inline void update_vposInWin() {
        v_posInWin = sf::Vector2f(FieldCenter.x + v_posInField.x * Scale.x, FieldCenter.y + v_posInField.y * Scale.y);
    }
    void setPositionI(int virt = 0) {
        int change = 1;
        if (v_posInField.x < -1 || v_posInField.x>1) {
            change = 0;//posInField.x=(posInField.x>1)?1:-1;
        }
        if (v_posInField.y < -1 || v_posInField.y>1) {
            change = 0;//posInField.y=(posInField.y>1)?1:-1;
        }
        if (change) {
            if (!virt) {
                posInField = v_posInField;
                update_posInWin();
                Cir.setPosition(posInWin);

            }
            else
                update_vposInWin();
        }
    }
    void setSpeed() {
        velocity.x = (velocity.x < -1 * MaxSpeed) ? -1 * MaxSpeed : velocity.x;
        velocity.x = (velocity.x > MaxSpeed) ? MaxSpeed : velocity.x;
        velocity.y = (velocity.y < -1 * MaxSpeed) ? -1 * MaxSpeed : velocity.y;
        velocity.y = (velocity.y > MaxSpeed) ? MaxSpeed : velocity.y;
        if(velocity.x>-1*vibrtn&&velocity.x<vibrtn){
            velocity.x=0;
        }
        if(velocity.y>-1*vibrtn&&velocity.y<vibrtn){
            velocity.y=0;
        }
        //belows can be removed after ball out system is done
        if(posInField.x<=-.996)
            velocity.x=(velocity.x<0)?0:velocity.x;
        else if(posInField.x>=.996)
            velocity.x=(velocity.x>0)?0:velocity.x;
        if(posInField.y<=-.998)
            velocity.y=(velocity.y<0)?0:velocity.y;
        else if(posInField.y>=.998)
            velocity.y=(velocity.y>0)?0:velocity.y;
    }
    static sf::Vector2f makeUnitVector(Vector2f v)
    {
        float mag = magnitude(v);
        if(mag==0)
            mag=1;
        return Vector2f(v.x / mag, v.y / mag);
    }
    static float magnitude(sf::Vector2f v)
    {
        return sqrt((v.x * v.x) + (v.y * v.y));
    }
    void prep_playerToBall(sf::Vector2f& v1,sf::Vector2f v2,player *pl){
        if(pl->is_direction(dayan)){
            if(v2.x>0){v1.x*=-1;}
        }
        else if(pl->is_direction(bayan)){
            if(v2.x<0){v1.x*=-1;}
        }
        if(pl->is_direction(mathi)){
            if(v2.y>0){v1.y*=-1;}
        }
        else if(pl->is_direction(muni)){
            if(v2.y<0){v1.y*=-1;}
        }
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
    int SpeedScale;
    sf::Vector2f velocity;
    sf::Vector2f Scale;
    float vibrtn;
    bool inPossesion;
    
    //friend sf::Vector2f teamoperator-(ball a,ball b);

const float ballFieldWidR;
const float ballSize;
const float ballOtlnSzR;//outline size ratio
const float b_posIncUnit;
const float p_and_b;
};
