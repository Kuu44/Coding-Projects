#include<iostream>
#include<SFML\graphics.hpp>

using namespace std;
using namespace sf;

extern const float fieldScale;
extern sf::Vector2i FieldCenter;

class field{
public:
    field();
    void draw(RenderTarget* );
    void set();
private:
    Texture FieldT;
    Sprite FieldS;
    int imLen;
    int imWid;
};

