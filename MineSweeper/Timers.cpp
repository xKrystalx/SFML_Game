#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>

#include "Timers.h"

Timers::Timers()
{
	restartTime(); //initialize timers and clocks
}

void Timers::restartTime() //part of restarting the game / Reset the values and clocks
{
	delta = sf::milliseconds(0);
	total_rendering_time = sf::milliseconds(0);
	pausedtime = sf::milliseconds(0);
	last_frame = sf::milliseconds(0);

	spawntimer = sf::milliseconds(MAX_SPAWN_TIME);
	speedtimer = sf::milliseconds(MAX_SPEED_TIME);
	effecttimer = sf::milliseconds(MAX_EFFECT_TIME);
	roundtimer = sf::seconds(MAX_ROUND_TIME);
	keytime = sf::milliseconds(MAX_KEY_DELAY_TIME);

	clock.restart();
	frameTime.restart();
	difficultyTime.restart();
	effectTime.restart();
	fpsTime.restart();
	roundTime.restart();
	pauseTime.restart();
	cooldownTime.restart();
}


Timers::~Timers()
{
}
