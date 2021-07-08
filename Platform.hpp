#pragma once

#include <SFML/Graphics.hpp>
#include "Map.hpp"

class Platform
{
private:
	sf::Texture textures[5];
	sf::RectangleShape platform;
public:
	Platform(sf::Vector2f pos);
	~Platform();
	void move(float speed, const Map& map);
	void draw(sf::RenderWindow& window) const;
	sf::RectangleShape getPlatform() const;
private:
	int collision_which(const Map& map) const;
};