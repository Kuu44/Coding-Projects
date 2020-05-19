//
// Created by maverick on 12/2/19.
//
#include <sstream>
#include <iostream>
#include "Game.h"
Game::Game(unsigned viewWidth, unsigned viewHeight,std::string Ip,bool isPlayer1)
	:window(sf::VideoMode(viewWidth, viewHeight), "Kurukshetra"),
	 textures(Textures::textureNumber),
	 fonts(GameFonts::fontNumber),
	 server(isPlayer1?11000:10000),
	 client(Ip,isPlayer1?10000:11000),
	 viewWidth(viewWidth),
	 viewHeight(viewHeight),
	 baseHeight(1900),
	 leftExtremePoint(1500),
	 rightExtremePoint(5500)
{
	window.setVerticalSyncEnabled(true);

	minimapView.setSize(sf::Vector2f(200.f, 200.f));
	minimapView.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));


	textures.load(Textures::skyTexture, "../Media/Textures/kurukshetra.png");
	textures.load(Textures::groundTexture, "../Media/Textures/stoneTile.png");
	textures.load(Textures::wallTexture, "../Media/Textures/stoneTile.png");
	textures.load(Textures::rockTexture, "../Media/Textures/rockPlatform.png");
	textures.load(Textures::playerTexture, "../Media/Textures/player.png");
	textures.load(Textures::enemyTexture, "../Media/Textures/enemy.png");
	textures.load(Textures::bulletTexture, "../Media/Textures/bullet.png");

	textures.get(Textures::skyTexture).setRepeated(true);
	textures.get(Textures::playerTexture).setSmooth(true);
	textures.get(Textures::bulletTexture).setSmooth(true);
	textures.get(Textures::grassTexture).setSmooth(true);

	sky.setPosition(sf::Vector2f(0, 0));
	sky.setSize(sf::Vector2f(7000, 2500));
	sky.setTexture(&textures.get(Textures::skyTexture));
	sky.setFillColor(sf::Color(255, 164, 134, 200));

	player.SetData(&textures.get(Textures::playerTexture), sf::Vector2u(4, 4), 0.3f, 150.0f, isPlayer1?sf::Vector2f(rightExtremePoint, baseHeight):sf::Vector2f(leftExtremePoint+player.GetSize().x, baseHeight));
	enemy.SetData(&textures.get(Textures::enemyTexture), sf::Vector2u(4, 4), 0.3f);


    gameView.SetSize(sf::Vector2f(viewWidth, viewHeight));
    gameView.SetViewPort(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    gameView.Update(player.GetBody(), window, sky);


    fonts.load(GameFonts::info, "../Media/Fonts/DejaVuSans.ttf");
	for (auto &text : info)
		text.setFont(fonts.get(GameFonts::info));

	for (int i=0; i<2; i++)
	{
		info[i].setPosition(viewWidth, viewHeight/1.5f * (i+1));
		info[i].setFillColor(sf::Color::Red);
	}

	deadInfo.setFont(fonts.get(GameFonts::info));
    deadInfo.setCharacterSize(50);
	deadInfo.setFillColor(sf::Color::Red);

	ground.SetData(&textures.get(Textures::groundTexture), sf::Vector2f(4300, 200), sf::Vector2f(leftExtremePoint - 150, baseHeight));
	ground.SetTextureRect(sf::IntRect(0, 0, 4000, 200));
    textures.get(Textures::groundTexture).setRepeated(true);

    setWalls();

	rock.setPosition(sf::Vector2f(300, baseHeight));
	rock.setSize(sf::Vector2f(300, 50));
	rock.setTexture(&textures.get(Textures::rockTexture));

	playerAnimation.SetData(&textures.get(Textures::playerTexture), sf::Vector2u(3,9), 0.3f);
	enemyAnimation.SetData(&textures.get(Textures::enemyTexture), sf::Vector2u(3,9), 0.3f);
}

void Game::run() {
	while (window.isOpen())
	{
		processEvents();
		update();
		render();
	}
}

void Game::update() {
    gameView.SetView(window);
    float elapsedTime = clock.restart().asSeconds();
    if(server.getM_playersConnected()>0 && client.isConnected())
	{
		player.Update( &textures.get(Textures::bulletTexture),  elapsedTime, gameView, baseHeight, leftExtremePoint, rightExtremePoint, window, sky, info, server, enemy);
		enemy.Update( &textures.get(Textures::bulletTexture), elapsedTime, gameView, baseHeight, window,sky,info,client);
	}
    else
	    player.Update(&textures.get(Textures::bulletTexture), elapsedTime, gameView, baseHeight, leftExtremePoint, rightExtremePoint, window, sky, info);
   // enemy.Update( &textures.get(Textures::bulletTexture), elapsedTime,  gameView, baseHeight, window);

	std::ostringstream stream;
	stream<<player.health;
	info[0].setString("Your Health: " + stream.str());
	stream.str("");
	stream<<enemy.health;
	info[1].setString("Enemy Health: " + stream.str());
}

void Game::processEvents() {
	sf::Event event = {};
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				// update the view to the new size of the window
//            sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
//            mWindow.setView(sf::View(visibleArea));
				ResizedWindow(window, gameView);
				break;
		}
	}
}

void Game::render() {
	if (player.isDead())
	{
		sf::Clock waitClock;
		std::cout<<"You Lose!!"<<std::endl;
		deadAnimate("You Lose!!", waitClock);
	}
	else if (enemy.isDead())
	{
		sf::Clock waitClock;
		std::cout<<"You Win!!"<<std::endl;
		deadAnimate("You Win!!", waitClock);
	}
	else
	{
		window.clear();
		window.draw(sky);
		ground.Draw(window);
		for(auto& wall : walls)
			wall.Draw(window);
		player.Draw(window, gameView, enemy, baseHeight);
		if(server.getM_playersConnected()>0 && client.isConnected())
			enemy.Draw(window, gameView, player, baseHeight);
		for (const auto &text : info)
			window.draw(text);
		window.display();
	}
}

void Game::ResizedWindow(sf::RenderWindow &window, Camera &view) {
	float aspectratio = window.getSize().x / float(window.getSize().y);

	view.SetSize(sf::Vector2f(viewWidth * aspectratio, viewHeight));
}

void Game::setWalls() {
	walls[0] = Platform(&textures.get(Textures::wallTexture), sf::Vector2f(150, 250), sf::Vector2f(leftExtremePoint - 150, baseHeight - 250));
	walls[1] = Platform(&textures.get(Textures::wallTexture), sf::Vector2f(150, 250), sf::Vector2f(rightExtremePoint, baseHeight - 250));
}

void Game::gameOver() {
	deadInfo.setPosition(gameView.GetCenter().x - window.getSize().x / 2.f, gameView.GetCenter().y - window.getSize().y / 2.f);
	deadInfo.setStyle(sf::Text::Italic);
	window.draw(deadInfo);
	window.display();
}
void Game::deadAnimate(std::string info, sf::Clock& waitClock)
{
	while(waitClock.getElapsedTime().asSeconds()<0.2f);
	waitClock.restart();
	deadInfo.setString(info);
    unsigned int size = deadInfo.getCharacterSize();
    gameOver();
    while(waitClock.getElapsedTime().asSeconds()<3.f)
    {
        size += 1;
        deadInfo.setCharacterSize(size);
        deadInfo.setPosition(deadInfo.getPosition().x - 1, deadInfo.getPosition().y + 1);
        window.draw(deadInfo);
        window.display();
    }
    waitClock.restart();
    deadInfo.setOutlineThickness(2.f);
    deadInfo.setOutlineColor(sf::Color::Black);
    while(waitClock.getElapsedTime().asSeconds()<1.5f){
        window.draw(deadInfo);
        window.display();
    }
    window.close();
}