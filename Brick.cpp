#include <string>
#include <iostream>
#include <cstdlib>
#include "Brick.hpp"

Brick::Brick(sf::Vector2f pos)
{
	int which = std::rand() % 5;

	textures[0].loadFromFile("Assets/Bricks/brick_" + std::to_string(which) + ".png");
	textures[1].loadFromFile("Assets/Bricks/brick_" + std::to_string(which) + "c.png");

	brick.setTexture(&textures[0]);
	brick.setSize({ 70.0f, 40.0f });
	brick.setPosition(pos);

	hit_count = 0;
}

Brick::~Brick()
{
}

void Brick::update(const Ball& ball)
{
	if (ball.getBall().getPosition().y + 25.0f == brick.getPosition().y + brick.getGlobalBounds().height &&
		ball.getBall().getPosition().x >= brick.getPosition().x &&
		ball.getBall().getPosition().x <= brick.getPosition().x + brick.getGlobalBounds().width)
		hit_count++;

	if (ball.getBall().getPosition().y + 3.0f == brick.getPosition().y &&
		ball.getBall().getPosition().x >= brick.getPosition().x &&
		ball.getBall().getPosition().x + 8.0f <= brick.getPosition().x + brick.getGlobalBounds().width)
		hit_count++;

	if (hit_count == 1)
		brick.setTexture(&textures[1]);
}

void Brick::draw(sf::RenderWindow& window) const
{
	window.draw(brick);
}

int Brick::total_hits() const
{
	return hit_count;
}

sf::RectangleShape Brick::getBrick() const
{
	return brick;
}
