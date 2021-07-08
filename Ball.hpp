#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Map.hpp"
#include "Brick.hpp"
#include "Platform.hpp"

class Brick;

class Ball
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f dir;
	float speed;
	bool conds[8];
public:
	Ball(sf::Vector2f pos, float speed);
	~Ball();
	bool update(const Map& map, const Platform& platform, const std::vector<Brick*>& bricks);
	void draw(sf::RenderWindow& window) const;
	sf::Sprite getBall() const;
private:
	int map_collision_which (const Map& map) const;
	int is_collided_with_brick(const std::vector<Brick*>& bricks) const;
	bool is_collided_with_platform(const Platform& platform) const;
};