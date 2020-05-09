#include<iostream>
#include<SFML\graphics.hpp>
#include"team.cpp"
#include"field.cpp"

using namespace sf;

class game{
public:
    game():A("A",1),B("B",-1){
        football.setIcolor(Color::White);
        football.setPosition(Vector2f(0,0));
    }
    void play();
    void pause();
    void refresh(RenderWindow* w){
        w->clear();
        field.draw(w);
        A.draw(w);
        B.draw(w);
        football.draw(w);
        w->display();
    }
    void playerskeyUpdate(Time deltaTime)
    {
        B.giveInput(Keyboard::Left, Keyboard::Right, Keyboard::Up, Keyboard::Down, Keyboard::M, &A, &football, deltaTime);
        A.giveInput(Keyboard::A,    Keyboard::D,     Keyboard::W,  Keyboard::S,    Keyboard::C, &B, &football, deltaTime);
    }

    void ballUpdate(Time deltaTime){
        football.updatePosition(deltaTime.asSeconds());
        A.check(&football);
        B.check(&football);
    }
private:
    team A;
    team B;
    ball football;
    team* tmp_team;
    Field field;
    float time;
    sf::Vector2i ps;
};

