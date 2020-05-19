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
    int wh_gm_set(){

    }
    void pause();
    void refresh(RenderWindow* w){
        w->clear();
        field.draw(w);
        A.draw(w);
        B.draw(w);
        football.draw(w);
        w->display();
    }
    void playerskeyUpdate(float deltaTime)
    {
        B.giveInput(Keyboard::Left, Keyboard::Right, Keyboard::Up, Keyboard::Down, Keyboard::M, Keyboard::P, &A, &football, deltaTime,&A);
        A.giveInput(Keyboard::A,    Keyboard::D,     Keyboard::W,  Keyboard::S,    Keyboard::C, Keyboard::Z, &B, &football, deltaTime,&B);
    }

    void ballUpdate(float deltaTime){
        football.updatePosition(deltaTime);

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

