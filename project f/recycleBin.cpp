/*int eventHandle(Event event) {
		switch (event.type) {
		case Event::KeyPressed:
			switch (event.key.code) {
			case Keyboard::Left:
				A.move(Vector2f(-1, 0));
				//ps=(-1,0);
				break;
			case Keyboard::Right:
				A.move(Vector2f(1, 0));
				//ps=(1,0);
				break;
			case Keyboard::Up:
				A.move(Vector2f(0, -1));
				//ps=(0,-1);
				break;
			case Keyboard::Down:
				A.move(Vector2f(0, 1));
				//ps=(0,1);
				break;
			case Keyboard::C:
				A.set_aktv();
				break;
			case Keyboard::A:
				B.move(Vector2f(-1, 0));
				//ps=(-1,0);
				break;
			case Keyboard::D:
				B.move(Vector2f(1, 0));
				//ps=(1,0);
				break;
			case Keyboard::W:
				B.move(Vector2f(0, -1));
				//ps=(0,-1);
				break;
			case Keyboard::S:
				B.move(Vector2f(0, 1));
				//ps=(0,1);
				break;
			case Keyboard::F:
				B.set_aktv();
				break;
			default:
				;
			}
		case Event::MouseButtonPressed:
		default:
			;
		}
		return 0;
	}
*/
/*
    if(event.type==sf::Event::Closed){
        return 1;
    }
    else if(event.type==sf::Event::Resized){
        //w.setSize(w.getSize());
    }
    else if(event.type==sf::Event::MouseButtonPressed){

    }/*
    else if(event.type==Event::KeyPressed){
        if(event.key.code==Keyboard::A){
            sf::Vector2f pos=player.getPosition();
                player.setPosition(pos.x-10,pos.y);
        }
        else if(event.key.code==Keyboard::D){
            sf::Vector2f pos=player.getPosition();
                player.setPosition(pos.x+10,pos.y);
        }
        else if(event.key.code==Keyboard::S){
            sf::Vector2f pos=player.getPosition();
                player.setPosition(pos.x,pos.y+10);
        }
        else if(event.key.code==Keyboard::W){
            sf::Vector2f pos=player.getPosition();
                player.setPosition(pos.x,pos.y-10);
        }
        else if(event.key.code==Keyboard::R){
            if(event.key.shift)
                player.setRotation(player.getRotation()-10);
            else
                player.setRotation(player.getRotation()+10);
        }
        else if(event.key.code==Keyboard::Q){

        }*/

/*
int gameExecute(Window& w){
    Event event;
//Handle Events
    while(w.pollEvent(event)){
        if(event.type=Event::Closed)
            return -1;
        else if(event.type==Event::KeyPressed){
            if(event.key=='a'){}
            else if(event.key=='d'){player.}
            else if(event.key=='w'){}
            else if(event.key=='s'){}
        }
    }
//draw
return 0;
}
/*
CircleShape player(77,77);
player.setFillColor(Color::Red);
player.setPosition(200,300);
w.draw(player);
sf::VideoMode::getFullscreenModes
(

)
*/
/*
        while(w.pollEvent(event)){
            if(event.type==Event::Closed)
                w.close();
            else
                g.eventHandle(event);
            if(clk.getElapsedTime().asMilliseconds()>=80){
                g.refresh(&w);
                clk.restart();
            }
        }
        if(clk.getElapsedTime().asMilliseconds()>=80){
                g.refresh(&w);
                clk.restart();
        }*/
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
/*
while(w.isOpen()){
        while(clk.getElapsedTime().asMilliseconds()<=ProcessTimeMaxms){
            int yesEvent=1;
            if(event.type!=event1.type){
                yesEvent=1;
                event=event1;
            }
            else if(w.pollEvent(event1)){
                event=event1;                                  //this is required
                yesEvent=1;
                while(event.type==event1.type){                //event.type==(event=event1).type){//this doesnot work and always returns true
                    if(!w.pollEvent(event1)){
                        break;
                    }
                    if(clk.getElapsedTime().asMilliseconds()>=Time_BufsPerInput){
                        //clk.restart();
                        break;
                    }
                }
            }
            else{
                yesEvent=0;
            }
            if(yesEvent){
                //g.eventHandle(event);
            }

        }
*/
