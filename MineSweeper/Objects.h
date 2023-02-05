#pragma once
#pragma message ("Objects Defined")
#include "Game.h"
#include "Types.h"
class Objects
{
private:
	sf::Sprite sprite;
	BoxType box_type;
	Score box_score;
public:
	friend class Game;
	friend class Sprites;
	Objects(BoxType, sf::Texture &, Game *, bool isPlayer = false);

	sf::Sprite getSprite();

	~Objects();
};

