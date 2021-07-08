#pragma once

#include <SFML/Graphics.hpp>

class Map
{
private:
	sf::Texture wall_textures[4];
	sf::Sprite wall_sprites[4];
	std::vector<sf::Sprite> upper_edge;
	std::vector<sf::Sprite> lower_edge;
	std::vector<sf::Sprite> left_edge;
	std::vector<sf::Sprite> right_edge;
public:
	Map();
	~Map();
	void draw(sf::RenderWindow& window) const;
	std::vector<sf::Sprite> upper_walls() const;
	std::vector<sf::Sprite> lower_walls() const;
	std::vector<sf::Sprite> left_walls() const;
	std::vector<sf::Sprite> right_walls() const;
};