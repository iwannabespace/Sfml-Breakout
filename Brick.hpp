#pragma once

#include <SFML/Graphics.hpp>
#include "Ball.hpp"

class Ball;

class Brick
{
private:
	sf::Texture textures[2];
	sf::RectangleShape brick;
	int hit_count;
public:
	Brick(sf::Vector2f pos);
	~Brick();
	void update(const Ball& ball);
	void draw(sf::RenderWindow& window) const;
	int total_hits() const;
	sf::RectangleShape getBrick() const;
};