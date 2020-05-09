class player{
public:
    player();
    void setName(string naam);
    void setNum(short int anka);
    void setPosition();
    void setPosition(sf::Vector2f v);
    void incPosition(float x=1,float y=1,int virt=0);
    void incSpeed(Vector2f inputSpeed);
    void setSpeed(float x,float y);
    void setSpeed(Vector2f inputSpeed);
    void setOcolor(Color Oc);
    void setIcolor(Color Ic);
    void draw(RenderWindow* tar) const;
    sf::Vector2f operator-(player p);
    sf::Vector2f getSpeed();
private:
    void incPositionLow(int virt, float x=0,float y=0){                      //(int x=1,int y=1){
        v_posInField=posInField;
        v_posInField.x+=x*posIncUnit*velocity.x;
        v_posInField.y+=y*posIncUnit*velocity.y;
        setPositionI(virt);
        //cout << " Move: (" << x << " , " << y << ")\n";
    }
    inline void update_posInWin(){
        posInWin=sf::Vector2f(FieldCenter.x+posInField.x*Scale.x,FieldCenter.y+posInField.y*Scale.y);
    }
    inline void update_vposInWin();
    void setPositionI(int virt=0);
    void setSpeed();

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
};
