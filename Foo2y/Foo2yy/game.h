#include<iostream>
#include<SFML\graphics.hpp>
#include"team.h"
#include"field.h"

using namespace sf;

extern const int winLen;
extern const int winWid;
extern const float playerSize;
extern const float fieldScale;

class game{
public:
    game();
    int ballUpdate(float );
    string get_state();
    void playerskeyUpdate(float );
    void refresh(RenderWindow* );
    int run(float ,sf::RenderWindow *);
private:
    int A_goals;
    int B_goals;
    sf::Clock clk;
    sf::Vector2i ps;
    ball football;
    team A;
    team B;
    team* tmp_team;
    field field;
    sf::Font font;
    CircleShape A_pl;
    CircleShape B_pl;
    sf::Text A_aktv;
    sf::Text B_aktv;
    sf::Text timer;
    const int GAME_TIME;
};


