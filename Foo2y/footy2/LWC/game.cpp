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
        //A.check(&football);
        //return 0;
    }
    /*int eventHandle(Event event){
    switch(event.type){
    case Event::KeyPressed:
        switch(event.key.code){
    //For team A
        case Keyboard::Numpad4:
            A.move(-1,0,&B);
            break;
        case Keyboard::Numpad6:
            A.move(1,0,&B);
            break;
        case Keyboard::Numpad8:
            A.move(0,-1,&B);
            break;
        case Keyboard::Numpad5:
            A.move(0,1,&B);
            break;
        case Keyboard::Add://Change active player

            break;
    //For team B
        case Keyboard::A:
            B.move(-1,0,&A);
            break;
        case Keyboard::D:
            B.move(1,0,&A);
            break;
        case Keyboard::W:
            B.move(0,-1,&A);
            break;
        case Keyboard::S:
            B.move(0,1,&A);
            break;
        case Keyboard::Tab://Change active player

            break;
        default:
            ;
        }
        break;
    case Event::KeyReleased:
        break;
    default:
        ;
    }
    return 0;
}*/
private:
    team A;
    team B;
    ball football;
    team* tmp_team;
    Field field;
    float time;
    sf::Vector2i ps;
};

