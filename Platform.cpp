#include <string>
#include <cstdlib>
#include <iostream>
#include "Platform.hpp"

Platform::Platform(sf::Vector2f pos)
{
	textures[0].loadFromFile(std::string("Assets/Bats/bat_black.png"));
	textures[1].loadFromFile(std::string("Assets/Bats/bat_blue.png"));
	textures[2].loadFromFile(std::string("Assets/Bats/bat_orange.png"));
	textures[3].loadFromFile(std::string("Assets/Bats/bat_pink.png"));
	textures[4].loadFromFile(std::string("Assets/Bats/bat_yellow.png"));
	platform.setSize({ 100.0f, 50.0f });
	platform.setTexture(&textures[std::rand() % 5]);
	platform.setPosition(pos);
}

Platform::~Platform()
{
}

void Platform::move(float speed, const Map& map)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		if (collision_which(map) != 1)
			platform.move({ -speed, 0.0f });

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		if (collision_which(map) != 2)
			platform.move({ speed, 0.0f });

}

void Platform::draw(sf::RenderWindow& window) const
{
	window.draw(platform);
}

sf::RectangleShape Platform::getPlatform() const
{
	return platform;
}

int Platform::collision_which(const Map& map) const
{
	for (const auto& wall_left : map.left_walls())
		if (platform.getGlobalBounds().intersects(wall_left.getGlobalBounds()))
			return 1;

	for (const auto& wall_right : map.right_walls())
		if (platform.getGlobalBounds().intersects(wall_right.getGlobalBounds()))
			return 2;

	return 0;
}