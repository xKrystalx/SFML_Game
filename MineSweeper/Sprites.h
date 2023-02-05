#pragma once
class Sprites
{
public:
	sf::Texture keyBlue, keyGreen, keyYellow, keyRed;
	sf::Texture bgBlue, bgRed, bgYellow, bgGreen;
	sf::Texture startT, quitT, scoreT, resumeT, pauseT, healthT;
	sf::Texture box, boxBlue, boxGreen, boxYellow, boxRed;

	sf::Font font;

	sf::Sprite keyB, keyG, keyY, keyR;
	sf::Sprite bgB, bgG, bgY, bgR;
	sf::Sprite scoreS, diffS, startS, quitS, resumeS, pauseS, healthS;

	sf::Text scoreText, diff, addScore, finalscoreText;
	sf::Text fpsCounter, timeRemaining;

	sf::Transform transform_90, transform_180, transform_270;

	sf::Vector2f scale;

	Sprites();

	bool initSprites();
	bool initFonts();
	void initTransformations(Objects *);
	void initSpriteSettings(sf::RenderWindow &, Objects *);

	void centerOrigin(sf::Sprite &);

	~Sprites();
};

