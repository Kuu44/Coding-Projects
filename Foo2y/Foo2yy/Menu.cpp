#include "Menu.h"
int Menu::mainmenu(sf::RenderWindow& window)
{
    sf::Texture background;
    sf::Sprite backgroundImage;
    if (!background.loadFromFile("img\\menu.jpg"))
        std::cout << "Error" << std::endl;
    backgroundImage.setTexture(background);
    sf::Texture play;
    sf::Sprite playbutton;
    if (!play.loadFromFile("img\\play.png"))
        std::cout << "Can't find the image" << std::endl;
    playbutton.setTexture(play);
    sf::RectangleShape rect(sf::Vector2f(450, 100));
    rect.setPosition(sf::Vector2f(1319, 803));
    rect.setFillColor(sf::Color::White);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                return 1;
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
    }
    return 0;
}
int Menu::teamselect(sf::RenderWindow& window1, int i)
{
    //sf::RenderWindow window1(sf::VideoMode(1920, 1080), "Foo2y TeamSelection", sf::Style::Fullscreen);
    sf::Texture background1;
    sf::Sprite backgroundImage1;
    if (!background1.loadFromFile("img\\TeamSelect.jpg"))
        std::cout << "teamselect photo not found";
    backgroundImage1.setTexture(background1);
    sf::RectangleShape rectArr1(sf::Vector2f(50, 57.735));
    rectArr1.setPosition(sf::Vector2f(400, 988.132));
    rectArr1.setFillColor(sf::Color::Transparent);
    sf::RectangleShape rectArr2(sf::Vector2f(50, 57.735));
    rectArr2.setPosition(sf::Vector2f(550, 988.132));
    rectArr2.setFillColor(sf::Color::Transparent);
    sf::RectangleShape rectArr3(sf::Vector2f(50, 57.735));
    rectArr3.setPosition(sf::Vector2f(1320, 988.132));
    rectArr3.setFillColor(sf::Color::Transparent);
    sf::RectangleShape rectArr4(sf::Vector2f(50, 57.735));
    rectArr4.setPosition(sf::Vector2f(1470, 988.132));
    rectArr4.setFillColor(sf::Color::Transparent);
    int count1 = 0;
    int count2 = 0;
    while (window1.isOpen())
    {
        sf::Event event;
        while (window1.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                return 1;
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    if (rectArr1.getGlobalBounds().contains(window1.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
                    {
                        if (count1 == 0)
                            count1 = 2;
                        else
                            count1 -= 1;
                    }
                    if (rectArr2.getGlobalBounds().contains(window1.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
                    {
                        if (count1 == 2)
                            count1 = 0;
                        else
                            count1 += 1;
                    }
                    if (rectArr3.getGlobalBounds().contains(window1.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
                    {
                        if (count2 == 0)
                            count2 = 2;
                        else
                            count2 -= 1;
                    }
                    if (rectArr4.getGlobalBounds().contains(window1.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
                    {
                        if (count2 == 2)
                            count2 = 0;
                        else
                            count2 += 1;
                    }
                }

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                return 0;
            }
            ;

        }
        if (i == 1) {
            window1.setVisible(true);
            i = 0;
        }
        window1.clear();
        window1.draw(backgroundImage1);
        window1.draw(rectArr1);
        window1.draw(rectArr2);
        window1.draw(rectArr3);
        window1.draw(rectArr4);
        if (count1 == 0)
        {
            sf::Texture team0;
            sf::Sprite lolpool;
            if (!team0.loadFromFile("img\\team0.jpg"))
                std::cout << "Error" << std::endl;
            lolpool.setPosition(sf::Vector2f(200, 220));
            lolpool.setTexture(team0);
            window1.draw(lolpool);
            sf::Texture formation0;
            sf::Sprite form0;
            if (!formation0.loadFromFile("img\\formation0.jpg"))
                std::cout << "Error" << std::endl;
            form0.setPosition(sf::Vector2f(200, 348));
            form0.setTexture(formation0);
            window1.draw(form0);
        }
        if (count1 == 1)
        {
            sf::Texture team1;
            sf::Sprite banterlona;
            if (!team1.loadFromFile("img\\team1.jpg"))
                std::cout << "Error" << std::endl;
            banterlona.setPosition(sf::Vector2f(200, 220));
            banterlona.setTexture(team1);
            window1.draw(banterlona);
            sf::Texture formation1;
            sf::Sprite form1;
            if (!formation1.loadFromFile("img\\formation1.jpg"))
                std::cout << "Error" << std::endl;
            form1.setPosition(sf::Vector2f(200, 348));
            form1.setTexture(formation1);
            window1.draw(form1);
        }
        if (count1 == 2)
        {
            sf::Texture team2;
            sf::Sprite chewmentos;
            if (!team2.loadFromFile("img\\team2.jpg"))
                std::cout << "Error" << std::endl;
            chewmentos.setPosition(sf::Vector2f(200, 220));
            chewmentos.setTexture(team2);
            window1.draw(chewmentos);
            sf::Texture formation2;
            sf::Sprite form2;
            if (!formation2.loadFromFile("img\\formation2.jpg"))
                std::cout << "Error" << std::endl;
            form2.setPosition(sf::Vector2f(200, 348));
            form2.setTexture(formation2);
            window1.draw(form2);
        }
        if (count2 == 0)
        {
            sf::Texture team0;
            sf::Sprite lolpool;
            if (!team0.loadFromFile("img\\team0.jpg"))
                std::cout << "Error" << std::endl;
            lolpool.setPosition(sf::Vector2f(1121, 220));
            lolpool.setTexture(team0);
            window1.draw(lolpool);
            sf::Texture formation0;
            sf::Sprite form0;
            if (!formation0.loadFromFile("img\\formation0.jpg"))
                std::cout << "Error" << std::endl;
            form0.setPosition(sf::Vector2f(1120, 348));
            form0.setTexture(formation0);
            window1.draw(form0);
        }
        if (count2 == 1)
        {
            sf::Texture team1;
            sf::Sprite banterlona;
            if (!team1.loadFromFile("img\\team1.jpg"))
                std::cout << "Error" << std::endl;
            //std::cout << "no error" << std::endl;
            banterlona.setPosition(sf::Vector2f(1121, 220));
            banterlona.setTexture(team1);
            window1.draw(banterlona);
            sf::Texture formation1;
            sf::Sprite form1;
            if (!formation1.loadFromFile("img\\formation1.jpg"))
                std::cout << "Error" << std::endl;
            //std::cout << "no error" << std::endl;
            form1.setPosition(sf::Vector2f(1120, 348));
            form1.setTexture(formation1);
            window1.draw(form1);
        }
        if (count2 == 2)
        {
            sf::Texture team2;
            sf::Sprite chewmentos;
            if (!team2.loadFromFile("img\\team2.jpg"))
                std::cout << "Error" << std::endl;
            //std::cout << "no error" << std::endl;
            chewmentos.setPosition(sf::Vector2f(1121, 220));
            chewmentos.setTexture(team2);
            window1.draw(chewmentos);
            sf::Texture formation2;
            sf::Sprite form2;
            if (!formation2.loadFromFile("img\\formation2.jpg"))
                std::cout << "Error" << std::endl;
            //std::cout << "no error" << std::endl;
            form2.setPosition(sf::Vector2f(1120, 348));
            form2.setTexture(formation2);
            window1.draw(form2);
        }
        window1.display();
    }
    return 0;
}
