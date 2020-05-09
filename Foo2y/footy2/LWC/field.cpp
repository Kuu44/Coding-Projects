#include<iostream>
#include<SFML\graphics.hpp>

using namespace std;
using namespace sf;

extern const float fieldScale;
extern sf::Vector2i FieldCenter;

class Field{
public:
    Field(){
        set();
        FieldS.scale(float(4)/1367,float(3)/937);//--(4) | (3)
        FieldS.setOrigin(1367/2,937/2);
        FieldS.setPosition(Vector2f(FieldCenter));
        FieldS.scale(fieldScale,fieldScale);
    }
    void draw(RenderTarget* tar){
        tar->draw(FieldS);
    }
    void set(){
        if(!FieldT.loadFromFile("img\\field1.jpg"))
            cout<<"err loading texture";
        FieldS.setTexture(FieldT);
    }
private:
    Texture FieldT;
    Sprite FieldS;
};
