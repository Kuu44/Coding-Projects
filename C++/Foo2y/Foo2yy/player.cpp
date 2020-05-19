#include"player.h"
//public
    player::player():v_posInField(sf::Vector2f(7,7)),v_posInWin(sf::Vector2f(7,7)),pass_flag(false),passSpeed(600.0f),
                        alpha_velocity(0,0),alphaScale(232)
    {
        MaxSpeed=90.0f;
        velocity=sf::Vector2f(0,0);
        Cir.setPointCount(20);
        Cir.setRadius(playerSize);
        Cir.setOrigin(playerSize*(1-playerOtlnSzR),playerSize*(1-playerOtlnSzR));
        Cir.setFillColor(Color(255,0,0,100));
        Cir.setOutlineThickness(playerSize*playerOtlnSzR);
        Cir.setOutlineColor(Color(0,255,0,100));
        Cir.scale(fieldScale,fieldScale);
        Scale=sf::Vector2f((2.32-playerSize)*fieldScale,(1.5-playerSize)*fieldScale);
        set_bounceFac(1);
        input_speed_store=Vector2f(0,0);
        directions[0]=und; directions[1]=und;
        //(fieldScale*2-playerSize-playerOutline,fieldScale*1.5-playerSize-playerOutline);
        font.loadFromFile("Fonts\\arial.ttf");
        num.setFont(font);
        num.setCharacterSize(20);
    }

    void player::draw(RenderWindow* tar) const{
        tar->draw(Cir);
        num.setPosition(posInWin);
        tar->draw(num);
    }

    void player::equalise_alpha(){
        alpha_posInField=posInField;
        update_alpha_pos_Win();
        update_alpha_velocity();
    }

    float player::get_bounceFac(){
        return bounceFac;
    }

    sf::Vector2f player::getFieldPosition()
    {
        return posInField;
    }

    bool player::getFlag(int i){
        switch(i){
            case pass:
                return pass_flag;
            default:
                return pass_flag;
        };
    }

    string player::getNum(){
        return num.getString();
    }

    int player::get_passSpeed(){
        return passSpeed;
    };

    sf::Vector2f player::get_posInWin(){
        return posInWin;
    }

    sf::Vector2f player::getSpeed() { return velocity; }
    void player::set_bounceFac(float f){
        if(f>=0&&f<=1){
                bounceFac=f;
        }
    }

    void player::inc_alpha_pos(float x,float y){
        sf::Vector2f tmp(alpha_posInField.x+x,alpha_posInField.x+y);
        if(tmp.x>=-1&&tmp.x<=1){
            if(tmp.y>=-1&&tmp.y<=1){
                alpha_posInField=tmp;
                update_alpha_pos_Win();
                update_alpha_velocity();
            }
        }
    }

    void player::incPosition(float x,float y,int virt){
        if(x==0&&y==0)
            v_posInWin=posInWin;
        else
        {
            incPositionLow(virt,x,y);
        }

    }

    void player::incSpeed(Vector2f inputSpeed){
        inputSpeed.x*=speedScale;inputSpeed.y*=speedScale;
        int tmp=1;
        if(inputSpeed.x<0)
            tmp=-1;
        if(input_speed_store.x<tmp*inputSpeed.x)
            input_speed_store.x=tmp*inputSpeed.x;
        tmp=1;
        if(inputSpeed.y<0)
            tmp=-1;
        if(input_speed_store.y<tmp*inputSpeed.y)
            input_speed_store.y=tmp*inputSpeed.y;
        //tmp=pow(velocity.x*velocity.x+velocity.y*velocity.y,.5);
        velocity += inputSpeed;
        velocity-=Vector2f(velocity.x*input_speed_store.x/MaxSpeed,velocity.y*input_speed_store.y/MaxSpeed);
        if(velocity.x>-1*vibrtn&&velocity.x<vibrtn){
            velocity.x=0;
        }
        if(velocity.y>-1*vibrtn&&velocity.y<vibrtn){
            velocity.y=0;
        }
        setSpeed();
    }

    bool player::is_direction(Direction d){
        bool flag=false;
        if(d==dayan||d==bayan){
            if(d==directions[0])
                flag=true;
        }
        else if(d==mathi||d==muni){
            if(d==directions[1])
                flag=true;
        }
        else{
            if(d==und)
                flag=true;
        }
        return flag;
    }

    void player::set_ALPHA_MODE(bool a){
        ALPHA_MODE=a;
    }

    void player::set_aplha_pos(sf::Vector2f v)
    {
        set_alpha_pos(v.x,v.y);
    }

    void player::set_alpha_pos(player pl){
        set_alpha_pos(posInField.x,posInField.y);
    }

    void player::set_alpha_pos(float x,float y){
        if(x>=-1&&x<=1){
            if(y>=-1&&y<=1){
                alpha_posInField.x=x;
                alpha_posInField.y=y;
                update_alpha_pos_Win();
                update_alpha_velocity();
            }
        }
    }

    void set_bounceFac(float f);

    void player::set_directions(Direction d){
        if(d==dayan||d==bayan){
            directions[0]=d;
        }
        else if(d==mathi||d==muni){
            directions[1]=d;
        }
        else{
            directions[0]=und;
            directions[1]=und;
        }
    }

    void player::setFlag(bool flag,int i){
        switch(i){
            case pass:
                pass_flag=flag;
            default:
                ;
        };
    }

    void player::setIcolor(Color Ic){
        Cir.setFillColor(Ic);
    }

    void player::setName(string naam){
        name=naam;
    }
    void player::setNum(short int anka){
        char tmp[3];
        tmp[0]='0'+anka%10;
        anka/=10;
        tmp[1]=(anka%10==0)?'\0':('0'+anka%10);
        tmp[2]='\0';
        num.setString(tmp);
        num.setOrigin(num.getLocalBounds().width*.5f,num.getLocalBounds().height*.5f);
    }

    void player::setOcolor(Color Oc){
        Cir.setOutlineColor(Oc);
    }

    void player::setPosition(){
        setPosition(v_posInField);
    }

    void player::setPosition(sf::Vector2f v){
        v_posInField=v;
        setPositionI(0);
    }

    void player::setSpeed(Vector2f inputSpeed){
        velocity=inputSpeed;
        setSpeed();
    }

    void player::setSpeed(float x,float y){
        velocity.x=x;
        velocity.y=y;
        setSpeed();
    }

    sf::Vector2f player::operator-(player p){
        return (sf::Vector2f(v_posInWin.x-p.v_posInWin.x,v_posInWin.y-p.v_posInWin.y));
    }

//private
    void player::incPositionLow(int virt, float x,float y){                      //(int x=1,int y=1){
        v_posInField=posInField;
        if(ALPHA_MODE){
            v_posInField.x+=x*posIncUnit*(velocity.x+alpha_velocity.x);
            v_posInField.y+=y*posIncUnit*(velocity.y+alpha_velocity.y);
        }
        else{
            v_posInField.x+=x*posIncUnit*velocity.x;
            v_posInField.y+=y*posIncUnit*velocity.y;
        }
        setPositionI(virt);
        //cout << " Move: (" << x << " , " << y << ")\n";
    }

    void player::setPositionI(int virt){
        int change=1;
        if(v_posInField.x<-1||v_posInField.x>1){
            change=0;//posInField.x=(posInField.x>1)?1:-1;
        }
        if(v_posInField.y<-1||v_posInField.y>1){
            change=0;//posInField.y=(posInField.y>1)?1:-1;
        }
        if(change){
            if(!virt){
                posInField=v_posInField;
                update_posInWin();

                Cir.setPosition(posInWin);
            }
            else
                update_vposInWin();
        }
        if(ALPHA_MODE){
            update_alpha_velocity();
        }
    }

    void player::setSpeed(){
        velocity.x=(velocity.x<-1*MaxSpeed)?-1*MaxSpeed:velocity.x;
        velocity.x=(velocity.x>MaxSpeed)?MaxSpeed:velocity.x;
        velocity.y=(velocity.y<-1*MaxSpeed)?-1*MaxSpeed:velocity.y;
        velocity.y=(velocity.y>MaxSpeed)?MaxSpeed:velocity.y;

        //tagert direction

        if(posInField.x<=-.996)
            velocity.x=(velocity.x<0)?0:velocity.x;
        else if(posInField.x>=.996)
            velocity.x=(velocity.x>0)?0:velocity.x;
        if(posInField.y<=-.998)
            velocity.y=(velocity.y<0)?0:velocity.y;
        else if(posInField.y>=.998)
            velocity.y=(velocity.y>0)?0:velocity.y;
    }

    void player::update_alpha_velocity(){
        Vector2f tmp=alpha_posInWin-posInWin;
        if(magnitude(tmp)>7){
            tmp=makeUnitVector(tmp);
            alpha_velocity=tmp*float(alphaScale);
        }
        else{
            alpha_velocity=sf::Vector2f(0,0);
        }
    }

    void player::update_alpha_pos_Win()
    {
        alpha_posInWin=sf::Vector2f(FieldCenter.x+alpha_posInField.x*Scale.x,FieldCenter.y+alpha_posInField.y*Scale.y);
    }

    inline void player::update_posInWin(){
        posInWin=sf::Vector2f(FieldCenter.x+posInField.x*Scale.x,FieldCenter.y+posInField.y*Scale.y);
    }

    inline void player::update_vposInWin(){
        v_posInWin=sf::Vector2f(FieldCenter.x+v_posInField.x*Scale.x,FieldCenter.y+v_posInField.y*Scale.y);
    }

    float player::magnitude(sf::Vector2f v)
    {
        return sqrt((v.x * v.x) + (v.y * v.y));
    }

    sf::Vector2f player::makeUnitVector(Vector2f v)
    {
        float mag = magnitude(v);
        return Vector2f(v.x / mag, v.y / mag);
    }


