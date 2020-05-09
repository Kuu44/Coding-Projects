#include<iostream>
#include<SFML\graphics.hpp>
class Mainmenu
{
public:
    static int mainmenu(sf::RenderWindow& window)
    {
        std::cout<<"yo";
//        sf::RenderWindow window(w_h);
//        sf::RenderWindow window=*w;
        sf::Texture background;
        sf::Sprite backgroundImage;
        if (!background.loadFromFile("menu.jpg"))
            std::cout << "Error" << std::endl;
        backgroundImage.setTexture(background);
        sf::Texture play;
        sf::Sprite playbutton;
        if (!play.loadFromFile("play.png"))
            std::cout << "Can't find the image" << std::endl;
        playbutton.setTexture(play);
        sf::RectangleShape rect(sf::Vector2f(450, 100));
        rect.setPosition(sf::Vector2f(1319, 803));
        rect.setFillColor(sf::Color::White);
        while (window.isOpen())
        {
            bool break_flag=false;
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    //window.close();
                    break_flag=true;
                    std::cout<<"yo";
                }
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        if (rect.getGlobalBounds().contains(window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
                        {
                            return 0;
                        }
                    }

                }
                window.clear();
                window.draw(backgroundImage);
                window.draw(rect);
                window.draw(playbutton);
                window.display();
            }
            if(break_flag){
                    window.setVisible(false);
                    window.clear();
                    return 1;
            }
        }
        return 0;
    }
};

