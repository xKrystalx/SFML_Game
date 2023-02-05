#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>


#include "Health.h"
#include "Game.h"
#include "Objects.h"
#include "Sprites.h"
#include "Types.h"


/*
Initializing health sprite
*/

Health::Health(sf::Texture & t)
{
	sprite.setTexture(t);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	sprite.setScale(0.0625f, 0.0625f);
}


Health::~Health()
{
}
