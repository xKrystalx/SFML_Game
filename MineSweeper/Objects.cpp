#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>

#include <iostream>

#include "Game.h"
#include "Objects.h"
#include "Sprites.h"
#include "Types.h"

Objects::Objects(BoxType type, sf::Texture & t, Game * game, bool isPlayer)
{
	sprite.setTexture(t, true);
	sprite.setScale(game->spr_scale);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	box_type = type;

	if (isPlayer) //set up player object
	{
		sprite.setScale(game->spr_scale);
		sprite.setPosition(game->x/2, game->y/2);
		return;
	}
	switch (type)
	{
	case BoxType::Red:
		sprite.setPosition(game->x + sprite.getGlobalBounds().width, game->y / 2); //Right
		box_score = Score::Red;
		//sprite.setPosition(150, 150);
		return;
	case BoxType::Yellow:
		sprite.setPosition(0 - sprite.getGlobalBounds().width, game->y / 2); //Left
		box_score = Score::Yellow;
		//sprite.setPosition(150, 150);
		return;
	case BoxType::Green:
		sprite.setPosition(game->x / 2, 0 - sprite.getGlobalBounds().height); //Top
		box_score = Score::Green;
		//sprite.setPosition(150, 150);
		return;
	case BoxType::Blue:
		sprite.setPosition(game->x / 2, game->y + sprite.getGlobalBounds().height); //Bottom
		box_score = Score::Blue;
		//sprite.setPosition(150, 150);
		return;
	case BoxType::White:
		sprite.setPosition(game->x / 2, game->y + sprite.getGlobalBounds().height); //Bottom
		box_score = Score::White;
		//sprite.setPosition(150, 150);
		return;
	default:
		//std::cout << "failed to create object";
		return;
	}
}

sf::Sprite Objects::getSprite() //return object's sprite
{
	return sprite;
}

Objects::~Objects()
{
}
