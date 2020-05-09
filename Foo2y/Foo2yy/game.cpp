#include"game.h"

//public
    game::game():A("A",1),B("B",-1),A_goals(0),B_goals(0),GAME_TIME(63)
    {
        football.setIcolor(Color::Magenta);
        football.setPosition(Vector2f(0,0));//float(.03)/(2-.03)*.5,0));
        A_pl.setPointCount(20);
        A_pl.setRadius(playerSize*fieldScale*3);
        A_pl.setOrigin(A_pl.getRadius()*2,0);
        A_pl.setFillColor(A.getColor()+Color(0,0,0,155));
        A_pl.setPosition(winLen-(winLen-fieldScale*4.65)*.5,fieldScale*3+winWid*playerSize);
        B_pl.setPointCount(20);
        B_pl.setRadius(playerSize*fieldScale*3);
        //B_pl.setOrigin(B_pl.getRadius(),B_pl.getRadius());
        B_pl.setFillColor(B.getColor()+Color(0,0,0,155));
        B_pl.setPosition((winLen-fieldScale*4.65)*.5,fieldScale*3+winWid*playerSize);
        font.loadFromFile("Fonts\\arial.ttf");
        B_aktv.setFont(font);
        B_aktv.setPosition(B_pl.getPosition()+sf::Vector2f(B_pl.getRadius(),0));
        //B_aktv.setCharacterSize();
        A_aktv.setFont(font);
        A_aktv.setPosition(A_pl.getPosition()-sf::Vector2f(A_pl.getRadius(),0));
        //A_aktv.setCharacterSize();
        timer.setFont(font);
        timer.setPosition(winLen*.5f,fieldScale*3+winWid*playerSize);
        clk.restart();
    }

    int game::ballUpdate(float deltaTime)
    {
        int jhanda;
        football.updatePosition(deltaTime);
        jhanda=A.check(&football);
        if(jhanda==7){
            return 7;
        }
        else if(jhanda==1){
            football.setCurrentSide(TeamA);
        }
        jhanda=B.check(&football);
        if(jhanda==7){
            return -7;
        }
        else if(jhanda==1){
            football.setCurrentSide(TeamB);
        }
        return 0;
    }

    string game::get_state(){
        string tmpS;
        char tmp[14];
        int sec= clk.getElapsedTime().asSeconds();
        tmp[0]='0'+(GAME_TIME-sec)/60;
        tmp[1]=tmp[3]=' ';
        tmp[2]=':';
        tmp[4]='0'+((GAME_TIME-sec)%60)/10;
        tmp[5]='0'+((GAME_TIME-sec)%60)%10;
        tmp[6]='\n';
        tmp[7]='0'+B_goals;
        tmp[8]=tmp[10]=' ';
        tmp[9]='-';
        tmp[11]='0'+A_goals;
        tmp[13]='\0';
        return tmp;
        //return (string(tmp[0])+" : "+string(tmp[4])+string(tmp[5]));
    }

    void game::playerskeyUpdate(float deltaTime)
    {
        A.giveInput(Keyboard::J,    Keyboard::L,     Keyboard::I,  Keyboard::K,    Keyboard::U, Keyboard::O,     &B, &football, deltaTime,&B);
        B.giveInput(Keyboard::A,    Keyboard::D,     Keyboard::W,  Keyboard::S,    Keyboard::Q, Keyboard::E,     &A, &football, deltaTime,&A);
    }

    void game::refresh(RenderWindow* w){
        w->clear();
        field.draw(w);
        A.draw(w);
        B.draw(w);
        football.draw(w);
        A_aktv.setString(A.get_aktv());
        A_aktv.setOrigin(A_aktv.getGlobalBounds().width*.5f,-A_pl.getRadius()*.5f);//A_aktv.getGlobalBounds().height*.5f);
        B_aktv.setString(B.get_aktv());
        B_aktv.setOrigin(B_aktv.getGlobalBounds().width*.5f,-B_pl.getRadius()*.5f);//B_aktv.getGlobalBounds().height*.5f);
        timer.setString(get_state());
        timer.setOrigin(timer.getGlobalBounds().width*.5f,timer.getGlobalBounds().height*.5f);
        w->draw(B_pl);
        w->draw(B_aktv);
        w->draw(A_pl);
        w->draw(A_aktv);
        w->draw(timer);
    }
    int game::run(float deltaTime,sf::RenderWindow *w){
        if(clk.getElapsedTime().asSeconds()>=GAME_TIME){
            if(A_goals>B_goals){
                return 7;
            }
            else if(B_goals>A_goals)
                return -7;
            else{
                return 1;
            }
        }
        int jhanda;
        playerskeyUpdate(deltaTime);
        jhanda=ballUpdate(deltaTime);
        if(jhanda==7){
            A_goals+=1;
            A.reconfig();
            B.reconfig();
            football.setPosition(sf::Vector2f(0,0));
        }
        if(jhanda==-7){
            B_goals+=1;
            A.reconfig();
            B.reconfig();
            football.setPosition(sf::Vector2f(0,0));
            football.setSpeed(0,0);
        }
        refresh(w);
        return 0;
    }

