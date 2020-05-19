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
    //Sprite jerseyS;
    ball() :v_posInField(sf::Vector2f(7, 7)), v_posInWin(sf::Vector2f(7, 7)),
            ballFieldWidR(.01),ballSize(ballFieldWidR * 3),ballOtlnSzR(.2),b_posIncUnit(ballSize * .05),
            p_and_b((ballSize+playerSize)*fieldScale),ball_self_flag(true),smOne_has_flag(false)
     {
        velocity = sf::Vector2f(0, 0);
        Cir.setPointCount(20);
        Cir.setRadius(ballSize);
        Cir.setOrigin(ballSize * (1 - ballOtlnSzR), ballSize * (1 - ballOtlnSzR));
        Cir.setFillColor(Color::Green);//(100, 0, 100, 255));
        Cir.setOutlineThickness(ballSize * ballOtlnSzR);
        Cir.setOutlineColor(Color(0, 255, 0, 100));
        Cir.scale(fieldScale, fieldScale);
        MaxSpeed=200;
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
        if(!smOne_has_flag){
            move(deltaTime);//just changes velocity based on user's key press
            Vector2f tmpV(velocity * deltaTime);
            incPosition(tmpV.x, tmpV.y);
            //increasePosition(velocity*deltaTime);
            applyDrag(deltaTime);
        }
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
        if (Keyboard::isKeyPressed(Keyboard::Y)) {
            currentSide = TeamA;
        }
        if (Keyboard::isKeyPressed(Keyboard::U)) {
            currentSide = None;
        }
        //cout << "\nSpeed:(" << velocity.x << " ," << velocity.y << " )";
        incSpeed(input*(deltaTime*SpeedScale));
    }
    int withBall(player* pl,int side){
        if(side*(-1)*posInField.x>0.99f-ballSize)
            {
                if(posInField.y>-0.2f &&posInField.y<0.2f)
                {
                    return 7;
                }
            }
        sf::Vector2f tmp=posInWin-pl->get_posInWin();
        if(tmp.x>-1.5*p_and_b&&tmp.x<1.5*p_and_b){
            if(tmp.y>-1.5*p_and_b&&tmp.y<1.5*p_and_b){
                sf::Vector2f unit_dirN;
                unit_dirN=makeUnitVector(velocity);
                float tmpFloat=unit_dirN.x*pl->getSpeed().x+unit_dirN.y*pl->getSpeed().x;
                if(!(smOne_has_flag||clkTmp.getElapsedTime().asMilliseconds()<100)){
                        setSpeed(pl->getSpeed().x,pl->getSpeed().y);
                        stick_flag=true;
                }else stick_flag=false;
                if(! (magnitude(velocity)>1.03*magnitude(pl->getSpeed()))){
                    stick_flag=true;
                }else stick_flag=false;
                if(stick_flag)
                {
                    //cout<<(((unit_dirN.x*pl->getSpeed().x+unit_dirN.y*pl->getSpeed().x)<=0)?"truetrue":"\t\tfalsefalse")<<"\n";
                    smOne_has_flag=true;
                    unit_dirN=makeUnitVector(pl->getSpeed());//reuse of unit_dirN
                    if(magnitude(unit_dirN)==0){
                        unit_dirN=Vector2f(1,1);
                    }
                    sf::Vector2f playerVelDirN=unit_dirN*p_and_b;//makeUnitVector(tmp)*p_and_b;
                    prep_playerToBall(playerVelDirN,unit_dirN,pl);
                    sf::Vector2f newPosition=pl->get_posInWin()-Vector2f(FieldCenter)+playerVelDirN;
                    newPosition.x/=Scale.x;
                    newPosition.y/=Scale.y;
                    setPosition(newPosition);
                    setSpeed(pl->getSpeed().x,pl->getSpeed().y);
                    passBall(pl);
                }
                else if(!stick_flag)
                {
                        //cout<<"$$$$$$$$$$$$$$$$$"<<((magnitude(velocity)>1.03*magnitude(pl->getSpeed()))?"\tyes":"\tno");cout<<magnitude(velocity)<<"<-ball | player->"<<1.03*magnitude(pl->getSpeed())<<"\n";
                        smOne_has_flag=false;
                        clkTmp.restart();
                        //incSpeed(20,20);
                }
            }
        }
        if(tmp.x>-1*p_and_b&&tmp.x<1*p_and_b){
            if(tmp.y>-1*p_and_b&&tmp.y<1*p_and_b){
                *this<<pl;
                if(side==1) currentSide=TeamB;
                if(side==-1) currentSide=TeamA;
                return 1;

            }
        }
        if(smOne_has_flag)
            return 1;
        else
            return 0;
    }
    void passBall(player *p,sf::Vector2f v=sf::Vector2f(7,7)){
        if(v.x>1){
            v=p->get_posInWin();
        }
        sf::Vector2f tmpPos(posInWin-v);
        if(p->getFlag(pass)){//cout<<"hey"<<magnitude(tmpPos)<<playerSize/Scale.x<<"$\n";
            smOne_has_flag=false;
            clkTmp.restart();
            incPosition(.1,.1);//Vector2f(playerSize/Scale.x*10,playerSize/Scale.y*10);
            setPosition(posInField+Vector2f(playerSize*.1,playerSize*.1));//(playerSize/Scale.x*10,playerSize/Scale.y*10));
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
    int getCurrentSide()
    {
        return currentSide;
    }
    void setCurrentSide(CurrentTeam T)
    {
        currentSide = T;
    }
    sf::Vector2f getFieldPosition()
    {
        return posInField;
    }
private:
    void incPositionLow(int virt, float x = 0, float y = 0){                      //(int x=1,int y=1){
        v_posInField = posInField;
        v_posInField.x += x * b_posIncUnit;//velocity.x*x*b_posIncUnit; yaha pani velocity le multiply gareko cha so duui choti multiply bhairathyo
        v_posInField.y += y * b_posIncUnit;//velocity.y*y*b_posIncUnit;
        setPositionI(virt);
    }
    inline void update_posInWin() {
        posInWin = sf::Vector2f(FieldCenter.x + posInField.x * Scale.x, FieldCenter.y + posInField.y * Scale.y);
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
    bool ball_self_flag;
    bool smOne_has_flag;
    bool stick_flag;
    float ctrl_det;
    Clock clkTmp;
    //0=TeamA, 1=None, 2=TeamB
    CurrentTeam currentSide;
    //friend sf::Vector2f teamoperator-(ball a,ball b);

const float ballFieldWidR;
const float ballSize;
const float ballOtlnSzR;//outline size ratio
const float b_posIncUnit;
const float p_and_b;
};
