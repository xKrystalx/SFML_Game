#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>

#include <vector>

#include "Game.h"
#include "Objects.h"
#include "Sprites.h"



Sprites::Sprites()
{
	scale = sf::Vector2f(0.1f, 0.1f); //sprite scale
}

/*
Initializing textures
@return loading result
*/

bool Sprites::initSprites()
{
	if (
		!box.loadFromFile("images/box_visible.png") ||
		!boxBlue.loadFromFile("images/box_visible_blue.png") ||
		!boxYellow.loadFromFile("images/box_visible_yellow.png") ||
		!boxGreen.loadFromFile("images/box_visible_green.png") ||
		!boxRed.loadFromFile("images/box_visible_red.png")
		)
	{
		return false;
	}

	if (!keyBlue.loadFromFile("images/key_blue.png") || 
		!keyGreen.loadFromFile("images/key_green.png") || 
		!keyYellow.loadFromFile("images/key_yellow.png") || 
		!keyRed.loadFromFile("images/key_red.png")
		)
	{
		return false;
	}

	if (
		!bgBlue.loadFromFile("images/bg_b.png") ||
		!bgGreen.loadFromFile("images/bg_g.png") ||
		!bgRed.loadFromFile("images/bg_r.png") ||
		!bgYellow.loadFromFile("images/bg_y.png")
		)
	{
		return false;
	}

	if (
		!startT.loadFromFile("images/start.png") ||
		!quitT.loadFromFile("images/quit.png") ||
		!resumeT.loadFromFile("images/resume.png") ||
		!pauseT.loadFromFile("images/pause.png")
		)
	{
		return false;
	}

	if (
		!scoreT.loadFromFile("images/bottom_line.png") ||
		!healthT.loadFromFile("images/hp.png")
		)
	{
		return false;
	}
	return true;
}

/*
Initializing fonts
*/

bool Sprites::initFonts()
{
	if (!font.loadFromFile("fonts/northern_lights.ttf"))
	{
		return false;
	}
	return true;
}

/*
Initializing transformations
*/

void Sprites::initTransformations(Objects * obj)
{
	transform_90.rotate(90, obj->sprite.getPosition()); //90 degree rotation
	transform_180.rotate(180, obj->sprite.getPosition());
	transform_270.rotate(270, obj->sprite.getPosition());
}

void Sprites::initSpriteSettings(sf::RenderWindow & window, Objects * player)
{
	float x = (float)window.getSize().x;
	float y = (float)window.getSize().y;

	/*
	Initializing key highlights
	*/

	keyB.setTexture(keyBlue, true);
	keyG.setTexture(keyGreen, true);
	keyY.setTexture(keyYellow, true);
	keyR.setTexture(keyRed, true);

	keyB.setScale(scale);
	keyG.setScale(scale);
	keyY.setScale(scale);
	keyR.setScale(scale);

	centerOrigin(keyB);
	centerOrigin(keyG);
	centerOrigin(keyR);
	centerOrigin(keyY);

	keyB.setPosition(x / 2, player->sprite.getGlobalBounds().top + player->sprite.getGlobalBounds().height + keyB.getGlobalBounds().height / 2);
	keyG.setPosition(x / 2, player->sprite.getGlobalBounds().top + player->sprite.getGlobalBounds().height + keyG.getGlobalBounds().height / 2);
	keyY.setPosition(x / 2, player->sprite.getGlobalBounds().top + player->sprite.getGlobalBounds().height + keyY.getGlobalBounds().height / 2);
	keyR.setPosition(x / 2, player->sprite.getGlobalBounds().top + player->sprite.getGlobalBounds().height + keyR.getGlobalBounds().height / 2);

	/*
	Initializing background
	*/
	bgB.setTexture(bgBlue);
	bgG.setTexture(bgGreen);
	bgY.setTexture(bgYellow);
	bgR.setTexture(bgRed);

	bgB.setColor(sf::Color(255, 255, 255, 127));
	bgG.setColor(sf::Color(255, 255, 255, 127));
	bgY.setColor(sf::Color(255, 255, 255, 127));
	bgR.setColor(sf::Color(255, 255, 255, 127));

	centerOrigin(bgB);
	centerOrigin(bgG);
	centerOrigin(bgR);
	centerOrigin(bgY);

	bgB.setPosition(x / 2, y);
	bgG.setPosition(x / 2, 0);
	bgY.setPosition(0, y / 2);
	bgR.setPosition(x, y / 2);


	/*
	Initializing menu sprites
	*/

	startS.setTexture(startT);
	quitS.setTexture(quitT);
	resumeS.setTexture(resumeT);
	pauseS.setTexture(pauseT);

	centerOrigin(startS);
	centerOrigin(quitS);
	centerOrigin(resumeS);
	centerOrigin(pauseS);

	startS.setPosition(x / 2 - 10, y / 2 - 50);
	quitS.setPosition(x / 2 - 10, y / 2 + 50);
	resumeS.setPosition(x / 2 - 10, y / 2 - 50);
	pauseS.setPosition(x / 2, y / 2 - 200);

	pauseS.setScale(0.4f, 0.4f);


	/*
	Initializing score and speed sprites/text
	*/

	scoreS.setTexture(scoreT);
	diffS.setTexture(scoreT);

	centerOrigin(scoreS);
	centerOrigin(diffS);

	scoreS.setPosition(160, 66);
	diffS.setPosition(160, 98);

	scoreS.setScale(0.4f, 0.4f);
	diffS.setScale(0.4f, 0.4f);

	scoreS.setColor(sf::Color(255, 255, 255, 191));
	diffS.setColor(sf::Color(255, 255, 255, 191));

	/*
	Initializing Text
	*/
	scoreText.setFont(font);
	scoreText.setCharacterSize(30);
	scoreText.setPosition(120, 40);
	scoreText.setStyle(sf::Text::Bold);
	scoreText.setOutlineColor(sf::Color::White);

	finalscoreText.setFont(font);
	finalscoreText.setCharacterSize(60);
	finalscoreText.setOrigin(finalscoreText.getGlobalBounds().width / 2, finalscoreText.getGlobalBounds().height / 2);
	finalscoreText.setPosition(x / 2 - 135, y / 2 - 300);
	finalscoreText.setStyle(sf::Text::Bold);
	finalscoreText.setOutlineColor(sf::Color::White);

	diff.setFont(font);
	diff.setCharacterSize(20);
	diff.setPosition(120, 80);
	diff.setStyle(sf::Text::Bold);
	diff.setFillColor(sf::Color::Green);
	diff.setOutlineColor(sf::Color::White);

	addScore.setFont(font);
	addScore.setCharacterSize(15);
	addScore.setPosition(scoreText.getGlobalBounds().width + 50, y / 10);
	addScore.setStyle(sf::Text::Bold);
	addScore.setOutlineColor(sf::Color::White);
	
	fpsCounter.setFont(font);
	fpsCounter.setCharacterSize(12);
	fpsCounter.setFillColor(sf::Color(255, 255, 255, 191));
	fpsCounter.setStyle(sf::Text::Bold);
	fpsCounter.setPosition(50, 10);

	timeRemaining.setFont(font);
	timeRemaining.setCharacterSize(20);
	timeRemaining.setFillColor(sf::Color(255, 255, 255, 255));
	timeRemaining.setStyle(sf::Text::Bold);
	timeRemaining.setPosition((float)window.getSize().x - 150, 10);
}

/*
Set sprite origin to it's center
*/

void Sprites::centerOrigin(sf::Sprite & spr)
{
	spr.setOrigin(spr.getLocalBounds().width / 2, spr.getLocalBounds().height / 2);
}

Sprites::~Sprites()
{
}
