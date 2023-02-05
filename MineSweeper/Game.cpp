#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>

#include <vector>
#include <iostream>
#include <string>

#include "Game.h"
#include "Objects.h"
#include "Sprites.h"
#include "Types.h"
#include "Health.h"

/*
Constructor
*/

Game::Game(sf::RenderWindow & window, Sprites * spr)
{
	spr_scale = spr->scale;
	isAnimated = true;
	isPaused = false;
	//player_scale = sf::Vector2f(0.125, 0.125);

	difficulty = SpeedType::Easy;

	speed = (int)SpeedType::Easy;
	bg_speed = 500;

	x = (float)window.getSize().x;
	y = (float)window.getSize().y;
}

/*
**************************************************
Create health sprites and hold them in a container
**************************************************
*/

void Game::setHealth(int hp, sf::Texture & t)
{
	for (int i = 0; i < hp; ++i)
	{
		health.push_back(new Health(t));
		health[i]->sprite.setPosition(30 + (health[i]->sprite.getGlobalBounds().width + 5) * i, y - 30);
	}
}
/*
Draw health sprites to the screen
*/

void Game::drawHealth(sf::RenderWindow & window)
{
	if (health.empty())
	{
		return;
	}
	for (std::vector<Health*>::iterator it = health.begin(); it != health.end(); ++it)
	{
		window.draw((*it)->sprite);
	}
}

size_t Game::getHealth()
{
	return health.size();
}

/*
*******************************************
Create our player
*******************************************
*/

void Game::createPlayer(sf::Texture & t)
{
	player = new Objects(BoxType::White, t, this, true);
}

/*
*******************************************
Creating boxes outside of the view
*******************************************
*/

void Game::createObject(BoxType type, sf::Texture & t, Game * game)
{
	switch (type)
	{
	case BoxType::Red:
		objects.push_back(new Objects(BoxType::Red, t, game));
		return;
	case BoxType::Blue:
		objects.push_back(new Objects(BoxType::Blue, t, game));
		return;
	case BoxType::Green:
		objects.push_back(new Objects(BoxType::Green, t, game));
		return;
	case BoxType::Yellow:
		objects.push_back(new Objects(BoxType::Yellow, t, game));
		return;
	case BoxType::White:
		objects.push_back(new Objects(BoxType::White, t, game));
		return;
	}
}

void Game::displayMisc(sf::RenderWindow & window, Sprites * spr)
{
	window.draw(spr->scoreS);
	window.draw(spr->diffS);
}

/*
*******************************************
Display background
*******************************************
*/

void Game::displayBackground(sf::Time time, sf::RenderWindow & window, Sprites * spr)
{
	float offset = bg_speed * time.asSeconds();
	if (isAnimated)
	{
		if (spr->bgB.getPosition().y > player->sprite.getPosition().y)
		{
			spr->bgB.move(0, -offset);
		}
		else
		{
			spr->bgB.setPosition(player->sprite.getPosition());
			isAnimated = false;
		}

		if (spr->bgG.getPosition().y < player->sprite.getPosition().y)
		{
			spr->bgG.move(0, offset);
		}
		else
		{
			spr->bgG.setPosition(player->sprite.getPosition());
			isAnimated = false;
		}

		if (spr->bgY.getPosition().x < player->sprite.getPosition().x)
		{
			spr->bgY.move(offset, 0);
		}
		else
		{
			spr->bgY.setPosition(player->sprite.getPosition());
			isAnimated = false;
		}

		if (spr->bgR.getPosition().x > player->sprite.getPosition().x)
		{
			spr->bgR.move(-offset, 0);
		}
		else
		{
			spr->bgR.setPosition(player->sprite.getPosition());
			isAnimated = false;
		}
	}
	window.draw(spr->bgB);
	window.draw(spr->bgG);
	window.draw(spr->bgY);
	window.draw(spr->bgR);
}

/*
*******************************************
Display menu
*******************************************
*/

Option Game::displayMenu(sf::RenderWindow & window, Sprites * spr)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos(sf::Mouse::getPosition(window));
		if (spr->startS.getGlobalBounds().contains(mousePos))
		{
			return Option::Start;
		}

		if (spr->quitS.getGlobalBounds().contains(mousePos))
		{
			return Option::Quit;
		}
	}
	window.draw(spr->startS);
	window.draw(spr->quitS);
	return Option::None;
}

/*
*******************************************
Display pause menu
*******************************************
*/


Option Game::displayPauseMenu(sf::RenderWindow & window, Sprites * spr)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos(sf::Mouse::getPosition(window));
		if (spr->resumeS.getGlobalBounds().contains(mousePos))
		{
			return Option::Resume;
		}

		if (spr->quitS.getGlobalBounds().contains(mousePos))
		{
			return Option::Quit;
		}
	}
	window.draw(spr->resumeS);
	window.draw(spr->quitS);
	window.draw(spr->pauseS);
	return Option::None;
}

/*
*******************************************
Display ending screen
*******************************************
*/


Option Game::displayGameOver(sf::RenderWindow & window, Sprites * spr)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f mousePos(sf::Mouse::getPosition(window));
		if (spr->resumeS.getGlobalBounds().contains(mousePos))
		{
			return Option::Start;
		}

		if (spr->quitS.getGlobalBounds().contains(mousePos))
		{
			return Option::Quit;
		}
	}

	window.draw(spr->startS);
	window.draw(spr->quitS);
	window.draw(spr->finalscoreText);
	return Option::None;
}

/*
*******************************************
Toggle pause state
*******************************************
*/


void Game::pauseGame()
{
	isPaused = !isPaused;
}

/*
Get Pause State
*/

bool Game::getPauseStatus()
{
	return isPaused;
}

/*
*******************************************
Key highlighting
*******************************************
*/

bool Game::checkKeyPress(sf::RenderWindow & window, Sprites * spr)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		window.draw(spr->keyY, spr->transform_90);
		return true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		window.draw(spr->keyR, spr->transform_270);
		return true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		window.draw(spr->keyG, spr->transform_180);
		return true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		window.draw(spr->keyB);
		return true;
	}
	return false;
}

/*
*******************************************
Pause / Unpause
*******************************************
*/

bool Game::checkEsc()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		if (isPaused)
		{
			pauseGame();
			return true;
		}
		pauseGame();
		return true;
	}
	return false;
}

/*
*******************************************
Hit animation
*******************************************
*/

void Game::setBackgroundAlpha(int val, Sprites * spr)
{
	spr->bgB.setColor(sf::Color(255, 255, 255, val));
	spr->bgY.setColor(sf::Color(255, 255, 255, val));
	spr->bgR.setColor(sf::Color(255, 255, 255, val));
	spr->bgG.setColor(sf::Color(255, 255, 255, val));
}

/*
*******************************************
Animate the sprites
*******************************************
*/

void Game::updatePosition(sf::Time time, sf::RenderWindow & window)
{
	float offset;
	if (objects.empty())
	{
		return;
	}
	for (std::vector<Objects*>::iterator it = objects.begin(); it != objects.end(); ++it)
	{
		offset = speed * time.asSeconds();
		switch((*it)->box_type)
		{		
		case BoxType::Red:
			//move from right
			(*it)->sprite.move(-offset, 0);
			break;
		case BoxType::Yellow:
			//move from left
			(*it)->sprite.move(offset, 0);
			break;
		case BoxType::Green:
			 //move from top
			(*it)->sprite.move(0, offset);
			break;
		case BoxType::Blue:
			 //move from bottom
			(*it)->sprite.move(0, -offset);
			break;
		case BoxType::White:
			 //move from bottom
			(*it)->sprite.move(0, -offset);
			break;
		}
		window.draw((*it)->sprite);
	}
}

/*
**********************************************************************************
Check if incoming boxes reached the player and if the player got a successful hit
**********************************************************************************
*/

Score Game::checkPosition(Sprites * spr)
{
	Score hit = Score::None;
	if (objects.empty())
	{
		return hit;
	}
	for (std::vector<Objects*>::iterator it = objects.begin(); it != objects.end();)
	{
		if (player->sprite.getGlobalBounds().intersects((*it)->sprite.getGlobalBounds())) //do stuff if the block is touching the player
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (*it)->box_type == BoxType::Yellow)
			{
				hit = Score::Yellow;
				spr->bgY.setColor(sf::Color(255, 255, 255, 191));
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (*it)->box_type == BoxType::Red)
			{
				hit = Score::Red;
				spr->bgR.setColor(sf::Color(255, 255, 255, 191));
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (*it)->box_type == BoxType::Green)
			{
				hit = Score::Green;
				spr->bgG.setColor(sf::Color(255, 255, 255, 191));
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (*it)->box_type == BoxType::Blue)
			{
				hit = Score::Blue;
				spr->bgB.setColor(sf::Color(255, 255, 255, 191));
			}
			else
			{
				hit = Score::Fail;
				spr->bgB.setColor(sf::Color(255, 100, 100, 191));
				spr->bgY.setColor(sf::Color(255, 100, 100, 191));
				spr->bgR.setColor(sf::Color(255, 100, 100, 191));
				spr->bgG.setColor(sf::Color(255, 100, 100, 191));

				health.pop_back(); //subtract 1 HP on fail
			}

			delete (*it);		//cleanup
			(*it) = nullptr;
			it = objects.erase(it); //returns an incremented iterator
		}
		else
		{
			++it;
		}
	}
	return hit;
}

/*
************************************
Update score
************************************
*/

sf::Text Game::updateScore(Score type, Sprites * spr)
{
	score += (int)type;
	std::string text = std::to_string(score);
	std::string finaltext = "Score: " + text;
	spr->scoreText.setString(text);
	spr->finalscoreText.setString(finaltext);
	
	return spr->scoreText;
}

/*
************************************
Increase difficulty over time
************************************
*/

void Game::increaseSpeed(sf::Time &time, int delta, Sprites * spr)
{
	speed += 1;
	if (time > sf::milliseconds(130))
	{
		time = time - sf::microseconds(1900) - sf::milliseconds(delta);
	}

	if (speed < (int)SpeedType::Normal && speed > (int)SpeedType::Easy)
	{
		difficulty = SpeedType::Normal;
		spr->diff.setFillColor(sf::Color::Cyan);
	}
	else if (speed < (int)SpeedType::Hard)
	{
		difficulty = SpeedType::Hard;
		spr->diff.setFillColor(sf::Color::Magenta);
	}
	else if (speed < (int)SpeedType::Extreme)
	{
		difficulty = SpeedType::Extreme;
		spr->diff.setFillColor(sf::Color::Yellow);
	}
	else if (speed < (int)SpeedType::Impossible)
	{
		difficulty = SpeedType::Impossible;
		spr->diff.setFillColor(sf::Color::Red);
	}
	//std::cout << "\n[Info] Increasing difficulty.";
}

/*
****************************************************
Provide access to private members
****************************************************
*/

/*
Get player object
*/

Objects * Game::getPlayer()
{
	return player;
}

/*
Get difficulty type for coloring purposes
*/

SpeedType Game::getDifficulty()
{
	return difficulty;
}

/*
Get current speed
*/

sf::Text Game::getDifficultyText(Sprites * spr)
{
	std::string text = "Speed:  " + std::to_string(speed);
	spr->diff.setString(text);
	return spr->diff;
}

/*
Get player's score
*/


int Game::getScore()
{
	return score;
}

/*
*********************************************
Restart the game
*********************************************
*/

void Game::restartGame()
{
	score = 0;
	speed = (int)SpeedType::Easy;
	difficulty = SpeedType::Easy;
	if (!objects.empty())
	{
		for (std::vector<Objects*>::iterator it = objects.begin(); it != objects.end();)
		{
			delete (*it);
			it = objects.erase(it);
		}
	}
	objects.clear();

	if (!health.empty())
	{
		for (std::vector<Health*>::iterator it = health.begin(); it != health.end();)
		{
			delete (*it);
			it = health.erase(it); //this returns iterator to the next object no need to increment
		}
	}
	health.clear();
}

/*
*********************************************
Remove remaining objects
*********************************************
*/

Game::~Game()
{
	if (!health.empty())
	{
		for (std::vector<Health*>::iterator it = health.begin(); it != health.end();)
		{
			delete (*it);
			it = health.erase(it);
		}
	}

	if (!objects.empty())
	{
		for (std::vector<Objects*>::iterator it = objects.begin(); it != objects.end();)
		{
			delete (*it);
			it = objects.erase(it);
		}
	}
	delete player;
	player = nullptr;
}
