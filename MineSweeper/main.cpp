#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>

#include <random>
#include <iostream>
#include <stdio.h>
#include <boost/format.hpp>
#include <fstream>
#include <string>
#include <sys/stat.h>

#include "Game.h"
#include "Objects.h"
#include "Sprites.h"
#include "Timers.h"
#include "Types.h"
#include "Health.h"

bool FileExists(char* filename)
{
	struct stat fileInfo;
	return stat(filename, &fileInfo) == 0;
}

bool is_empty(std::ifstream& pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}

int main()
{
	std::ofstream file;
	if (!FileExists("scoreboard/scoreboard.txt")) //create the scoreboard.txt if it doesnt exist
	{
		std::ofstream file("scoreboard/scoreboard.txt");
		if (!file)
		{
			std::cout << "\nFile could not be created.";
			return -1;
		}
	}
	std::ifstream file_in("scoreboard/scoreboard.txt");

	if (is_empty(file_in))
	{
		file.open("scoreboard/scoreboard.txt");
		file << "Scoreboard\n----------\n";
		file.close();
	}

	/*
	***************************************************************************
	Loading resources
	***************************************************************************
	*/

	sf::RenderWindow window(sf::VideoMode(800, 800, 32), "Beat the Box v1.1", sf::Style::Titlebar | sf::Style::Close); //Do not allow window resize
	window.setVerticalSyncEnabled(false);	//set Vsync
	window.setFramerateLimit(144);	//set max FPS

	Timers * TimeStorage = new Timers(); //create timer class that handles all of our sf::Time and sf::Clock

	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uniBox(0, 3); // guaranteed unbiased
	std::uniform_int_distribution<int> uniTime(-5, 5); //slight deviation of spawning time


	bool isGameOver = false;
	bool isInMenu = true;
	bool isPaused = false;
	bool isScoreUpdated = false;

	double time_val = TimeStorage->roundtimer.asSeconds(); //temporary storage for round time

	std::vector<int> fpsArray; //vector storing our frame times
	fpsArray.clear(); //clear the vector

	Sprites * SpriteStorage = new Sprites(); //create our sprite container and initialize all textures and sprites used in the game

	if (!SpriteStorage->initSprites() || !SpriteStorage->initFonts()) //check if textures have loaded in
	{
		return -1;
	}


	Game * BeatTheBox = new Game(window, SpriteStorage); //create our game class that handles most of game's logic
	BeatTheBox->createPlayer(SpriteStorage->box); //create player
	sf::Sprite player = BeatTheBox->getPlayer()->getSprite(); //get player's sprite for easier draw calls

	SpriteStorage->initSpriteSettings(window, BeatTheBox->getPlayer()); //initialize sprite settings (scale, texture, position, origin etc.)
	SpriteStorage->initTransformations(BeatTheBox->getPlayer());	//initalize rotation transformations

	BeatTheBox->setHealth(MAX_HEALTH, SpriteStorage->healthT); //initialize HP

	/*
	***************************************************************************
	Resources loaded

	Starting main sequence
	***************************************************************************
	*/

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{

				delete BeatTheBox; //cleanup
				BeatTheBox = nullptr;
				delete SpriteStorage;
				SpriteStorage = nullptr;
				delete TimeStorage;
				TimeStorage = nullptr;

				window.close();
				return 0;
			}
		}


		TimeStorage->delta = TimeStorage->frameTime.getElapsedTime(); //Calculate the change in frame times to keep everything at a constant speed
		isPaused = BeatTheBox->getPauseStatus();
		/*
		**********************************************************************
		Calculating frames per second, based on average out of FPS_SAMPLES
		**********************************************************************
		*/

		if ((int)fpsArray.size() == FPS_SAMPLES)
		{
			TimeStorage->total_rendering_time = TimeStorage->fpsTime.getElapsedTime();
			int fps_val = (int)(FPS_SAMPLES / TimeStorage->total_rendering_time.asSeconds());
			std::string fps ="FPS:  " + std::to_string(fps_val);
			SpriteStorage->fpsCounter.setString(fps);
			fpsArray.clear();
			TimeStorage->fpsTime.restart();
		}
		fpsArray.push_back(TimeStorage->delta.asMilliseconds());
		TimeStorage->frameTime.restart();

		if (TimeStorage->roundtimer.asSeconds() - time_val > TimeStorage->roundtimer.asSeconds()) //time is up
		{
			isGameOver = true;
		}
		/*
		****************************************************************
		Creating our Round Timer
		****************************************************************
		*/

		boost::format timeFormat("Time: %.1f");
		if (!isPaused && !isInMenu && !isGameOver)
		{
			time_val = time_val - TimeStorage->delta.asSeconds();
		}
		timeFormat % time_val; //format the string
		std::string timeleft = timeFormat.str();
		SpriteStorage->timeRemaining.setString(timeleft); //set the text contents


		/*
		****************************************************************
		Generating boxes coming at the player
		****************************************************************
		*/

		if (TimeStorage->clock.getElapsedTime().asMilliseconds() > TimeStorage->spawntimer.asMilliseconds() && !isGameOver && !isInMenu && !isPaused)
		{
			BoxType rnd_type = (BoxType)uniBox(rng); //randomize the block type
			//std::cout << (int)rnd_type;

			switch (rnd_type)
			{
			case BoxType::Red:
				BeatTheBox->createObject(rnd_type, SpriteStorage->boxRed, BeatTheBox); //create a Red block, with boxRed texture
				break;
			case BoxType::Blue:
				BeatTheBox->createObject(rnd_type, SpriteStorage->boxBlue, BeatTheBox);
				break;
			case BoxType::Green:
				BeatTheBox->createObject(rnd_type, SpriteStorage->boxGreen, BeatTheBox);
				break;
			case BoxType::Yellow:
				BeatTheBox->createObject(rnd_type, SpriteStorage->boxYellow, BeatTheBox);
				break;
			case BoxType::White:
				BeatTheBox->createObject(rnd_type, SpriteStorage->box, BeatTheBox);
				break;
			}

			TimeStorage->clock.restart();
		}

		/*
		****************************************************************
		Increasing difficulty
		****************************************************************
		*/

		if (TimeStorage->difficultyTime.getElapsedTime().asMilliseconds() > TimeStorage->speedtimer.asMilliseconds() && BeatTheBox->getDifficulty() < SpeedType::Impossible && !isGameOver && !isInMenu && !isPaused)
		{
			BeatTheBox->increaseSpeed(TimeStorage->spawntimer, uniTime(rng), SpriteStorage);
			//std::cout << "\nTime: " << spawntimer.asMilliseconds();
			TimeStorage->difficultyTime.restart();
		}
		

		if (isGameOver && isInMenu && isPaused) //keep restarting the clock
		{
			TimeStorage->clock.restart();
			TimeStorage->difficultyTime.restart();
		}

		/*
		********************************************************
		Drawing and displaying block
		********************************************************
		*/

		window.clear(sf::Color::Black);
		Score isHit = Score::None;

		BeatTheBox->displayBackground(TimeStorage->delta, window, SpriteStorage); //display background
		window.draw(SpriteStorage->fpsCounter); //display FPS counter


		/*
		Game is paused
		*/

		if (isPaused)
		{
			TimeStorage->pausedtime = TimeStorage->pauseTime.getElapsedTime(); //calculate the time, the game has been paused for to stop the round timer from decreasing
			//window.display();
			if (TimeStorage->cooldownTime.getElapsedTime() > TimeStorage->keytime) //delay ESC detection
			{
				if (BeatTheBox->checkEsc())  //check if we should unpause
				{
					TimeStorage->cooldownTime.restart();
				}
			}
			Option result = BeatTheBox->displayPauseMenu(window, SpriteStorage);
			switch (result)
			{
			case Option::Resume:
				BeatTheBox->pauseGame();
				break;
			case Option::Quit:
				window.close();
			case Option::None:
				break;
			}
			window.display();
			continue;
		}
		TimeStorage->pausedtime = sf::milliseconds(0);
		TimeStorage->pauseTime.restart();

		/*
		Starting menu
		*/

		if (isInMenu)
		{
			Option result = BeatTheBox->displayMenu(window, SpriteStorage); //player is in the menu, prioritize displaying the menu content
			switch (result)
			{
			case Option::Start:
				isInMenu = false; //start the game
				break;
			case Option::Quit:
				window.close();  //quit button has been pressed
			case Option::None:
				window.display(); //keep displaying the menu
				continue;
			}
		}

		/*
		Game over check
		*/

		if (!isGameOver)
		{
			window.draw(SpriteStorage->timeRemaining); //display remaining time

			isHit = BeatTheBox->checkPosition(SpriteStorage); //check if player should get points or not

			if (isHit == Score::Fail && (int)BeatTheBox->getHealth() == 0)
			{
				isGameOver = true; //no more HP left, so end the game
				window.display(); //render what's left to render and move on to the next frame
				continue;
			}
			else if (isHit == Score::None && TimeStorage->effectTime.getElapsedTime() > TimeStorage->effecttimer)
			{
				BeatTheBox->setBackgroundAlpha(127, SpriteStorage);  //revert background alpha change due to hit or miss
				TimeStorage->effectTime.restart();
			}
			else if (isHit != Score::None)
			{
				TimeStorage->effectTime.restart();  //restart animation timer
			}
			BeatTheBox->updatePosition(TimeStorage->delta, window);	//draw other incoming objects
			if (TimeStorage->cooldownTime.getElapsedTime() > TimeStorage->keytime) //apply a delay to ESC detection
			{
				if (BeatTheBox->checkEsc())
				{
					TimeStorage->cooldownTime.restart();
				}
			}
			BeatTheBox->checkKeyPress(window, SpriteStorage); //check if an arrow key has been pressed
		}
		else
		{
			if (!isScoreUpdated) //store the score in the .txt file
			{
				std::cout << "writing";
				file.open("scoreboard/scoreboard.txt", std::ios::app);
				boost::format scoreFormat("\n|: %i  ### Time Remaining: %.1f  ### Lives: %i");
				scoreFormat % BeatTheBox->getScore() % time_val % (int)BeatTheBox->getHealth();  //formatting score and time since the start of the round
				std::string finalscore = scoreFormat.str();
				file << finalscore;
				file.close();

				isScoreUpdated = true;
			}
			Option result = BeatTheBox->displayGameOver(window, SpriteStorage);
			switch (result)
			{
			case Option::Start: //Restart Game
				isGameOver = false;
				isScoreUpdated = false;
				TimeStorage->restartTime();
				BeatTheBox->restartGame();
				time_val = TimeStorage->roundtimer.asSeconds(); //reset round time
				BeatTheBox->setHealth(MAX_HEALTH, SpriteStorage->healthT); //reset HP
				window.display();
				continue;
			case Option::Quit:
				break;
			case Option::None:
				window.display();
				continue;
			}
			delete BeatTheBox;	//cleanup
			delete SpriteStorage;
			delete TimeStorage;
			BeatTheBox = nullptr;
			SpriteStorage = nullptr;
			TimeStorage = nullptr;
			window.close();
			return 0;
		}
		window.draw(player);	//draw player

		BeatTheBox->drawHealth(window); //display health
		BeatTheBox->displayMisc(window, SpriteStorage); //display visual-only sprites
		window.draw(BeatTheBox->updateScore(isHit, SpriteStorage)); //update score
		window.draw(BeatTheBox->getDifficultyText(SpriteStorage));	//display speed

		window.display();
	}

	return 0;
}