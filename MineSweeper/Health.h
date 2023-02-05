#pragma once
class Health
{
private:
	sf::Sprite sprite;
public:
	Health(sf::Texture &);

	friend class Game;

	~Health();
};

