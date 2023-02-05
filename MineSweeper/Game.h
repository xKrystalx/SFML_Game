#pragma once
#pragma message ("Game Defined")
#include "Objects.h"
#include "Sprites.h"
#include "Health.h"

#define MAX_HEALTH 4

class Game
{
private:
	std::vector<Objects*> objects;
	std::vector<Health*> health;
	Objects * player;
	int speed, bg_speed;

	float x, y;
	
	int score;

	bool isAnimated;
	bool isPaused;

	SpeedType difficulty;
	sf::Vector2f spr_scale;

public:
	friend class Objects;
	friend class Sprites;

	Game(sf::RenderWindow &, Sprites *);

	void setHealth(int, sf::Texture &);
	void drawHealth(sf::RenderWindow &);
	size_t getHealth();

	void createPlayer(sf::Texture &);
	void createObject(BoxType, sf::Texture &, Game *);

	void displayMisc(sf::RenderWindow &, Sprites *);
	void displayBackground(sf::Time, sf::RenderWindow &, Sprites *);
	Option displayMenu(sf::RenderWindow &, Sprites *);
	Option displayPauseMenu(sf::RenderWindow &, Sprites *);
	Option displayGameOver(sf::RenderWindow &, Sprites *);

	void pauseGame();
	bool getPauseStatus();

	bool checkKeyPress(sf::RenderWindow &, Sprites *);
	bool checkEsc();
	Score checkPosition(Sprites *);

	void setBackgroundAlpha(int, Sprites *);

	void updatePosition(sf::Time, sf::RenderWindow &);

	void increaseSpeed(sf::Time &, int, Sprites *);

	sf::Text updateScore(Score, Sprites *);

	Objects * getPlayer();
	SpeedType getDifficulty();
	sf::Text getDifficultyText(Sprites *);
	int getScore();

	void restartGame();

	~Game();
};

