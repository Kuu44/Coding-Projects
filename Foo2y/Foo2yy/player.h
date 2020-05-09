#include<iostream>
#include<SFML\graphics.hpp>
#include<cmath>


using namespace std;
using namespace sf;

enum CurrentTeam { TeamA, None,TeamB};
enum Flags{pass,shoot};
enum Direction{und,dayan,bayan,mathi,muni};
const float playerFieldWidR=.015;
const float playerSize=playerFieldWidR*3;
const float playerOtlnSzR=.2;//outline size ratio
const float posIncUnit=playerSize*.05;
//const float drag=.05;
const float vibrtn=.00084;
const int speedScale=100;//acceleration=speedScale pixels/sec^2 and speed=velocity pixels/sec
extern const float fieldScale;
extern sf::Vector2i FieldCenter;

class player{
public:
    player();

    void draw(RenderWindow* tar) const;

    void equalise_alpha();

    float get_bounceFac();

    sf::Vector2f getFieldPosition();

    bool getFlag(int i=pass);

    string getNum();

    int get_passSpeed();

    sf::Vector2f get_posInWin();

    sf::Vector2f getSpeed();

    void inc_alpha_pos(float x,float y);

    void incPosition(float x=1,float y=1,int virt=0);

    void incSpeed(Vector2f inputSpeed);

    bool is_direction(Direction d);

    void set_ALPHA_MODE(bool a);

    void set_aplha_pos(sf::Vector2f v);

    void set_alpha_pos(player pl);

    void set_alpha_pos(float x,float y);

    void set_bounceFac(float f);

    void set_directions(Direction d);

    void setFlag(bool flag,int i=pass);

    void setIcolor(Color Ic);

    void setName(string naam);

    void setNum(short int anka);

    void setOcolor(Color Oc);

    void setPosition();

    void setPosition(sf::Vector2f v);

    void setSpeed(Vector2f inputSpeed);

    void setSpeed(float x,float y);

    sf::Vector2f operator-(player p);


private:
    void incPositionLow(int virt, float x=0,float y=0);

    void setPositionI(int virt=0);

    void setSpeed();

    void update_alpha_velocity();

    void update_alpha_pos_Win();

    inline void update_posInWin();

    inline void update_vposInWin();

    static sf::Vector2f makeUnitVector(Vector2f v);

    static float magnitude(sf::Vector2f v);


    bool ALPHA_MODE;
    bool pass_flag;

    int alphaScale;
    int passSpeed;

    float bounceFac;//0 means perfect control
    float MaxSpeed;

    string name;

    sf::Vector2f alpha_velocity;
    sf::Vector2f alpha_posInWin;
    sf::Vector2f alpha_posInField;
    sf::Vector2f input_speed_store;
    sf::Vector2f velocity;
    sf::Vector2f v_posInField;
    sf::Vector2f v_posInWin;
    sf::Vector2f posInField;
    sf::Vector2f posInWin;
    sf::Vector2f Scale;

    Direction directions[2];

    CircleShape Cir;

    sf::Font font;
    mutable sf::Text num;

};


