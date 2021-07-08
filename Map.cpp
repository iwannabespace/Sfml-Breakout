#include <string>
#include <vector>
#include <cstdlib>
#include "Map.hpp"

Map::Map()
{
	wall_textures[0].loadFromFile(std::string("Assets/Walls/brick.png"));
	wall_textures[1].loadFromFile(std::string("Assets/Walls/brick_blue.png"));
	wall_textures[2].loadFromFile(std::string("Assets/Walls/brick_pink_side.png"));
	wall_textures[3].loadFromFile(std::string("Assets/Walls/brick_red.png"));

	for (int i = 0; i < 4; i++)
	{
		wall_sprites[i].setTexture(wall_textures[i]);
		wall_sprites[i].setScale({ 0.1f, 0.1f });
	}

	for (int i = 0; i < 18; i++)
	{
		upper_edge.push_back(wall_sprites[std::rand() % 4]);
		lower_edge.push_back(wall_sprites[std::rand() % 4]);
		upper_edge[i].setPosition({ 
			(i - 1) >= 0 ? upper_edge[i - 1].getPosition().x + (upper_edge[i].getGlobalBounds().width - 8.0f) : 0.0f , 0.0f });
		lower_edge[i].setPosition({
			(i - 1) >= 0 ? lower_edge[i - 1].getPosition().x + (lower_edge[i].getGlobalBounds().width - 8.0f) : 0.0f , 24 * (25.6f - 8) });
	}

	for (int i = 0; i < 23; i++)
	{
		left_edge.push_back(wall_sprites[std::rand() % 4]);
		right_edge.push_back(wall_sprites[std::rand() % 4]);
		left_edge[i].setPosition({
			 0.0f, (i - 1) >= 0 ? left_edge[i - 1].getPosition().y + (left_edge[i].getGlobalBounds().height - 8.0f) : 25.6f - 8 });
		right_edge[i].setPosition({
			 upper_edge[17].getPosition().x, (i - 1) >= 0 ? right_edge[i - 1].getPosition().y + (right_edge[i].getGlobalBounds().height - 8.0f) : 25.6f - 8 });
	}
}

Map::~Map()
{
}

void Map::draw(sf::RenderWindow& window) const
{
	for (int i = 0; i < 18; i++)
	{
		window.draw(upper_edge[i]);
		window.draw(lower_edge[i]);
	}

	for (int i = 0; i < 23; i++)
	{
		window.draw(left_edge[i]);
		window.draw(right_edge[i]);
	}
}

std::vector<sf::Sprite> Map::upper_walls() const
{
	return upper_edge;
}

std::vector<sf::Sprite> Map::lower_walls() const
{
	return lower_edge;
}

std::vector<sf::Sprite> Map::left_walls() const
{
	return left_edge;
}

std::vector<sf::Sprite> Map::right_walls() const
{
	return right_edge;
}