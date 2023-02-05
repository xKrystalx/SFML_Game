#pragma once

#define FPS_SAMPLES 60
#define MAX_SPAWN_TIME 1500
#define MAX_EFFECT_TIME 100
#define MAX_ROUND_TIME 90
#define MAX_SPEED_TIME 100
#define MAX_KEY_DELAY_TIME 400

class Timers
{
public:
	sf::Clock clock, frameTime, difficultyTime, effectTime, fpsTime, roundTime, pauseTime, cooldownTime;
	sf::Time delta, total_rendering_time, pausedtime, last_frame;
	sf::Time spawntimer, speedtimer, effecttimer, roundtimer, keytime;


	Timers();

	void restartTime();

	~Timers();
};

