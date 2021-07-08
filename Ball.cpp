#include <string>
#include <cstdlib>
#include <iostream>
#include "Ball.hpp"

Ball::Ball(sf::Vector2f pos, float speed)
	: speed(speed)
{
	texture.loadFromFile(std::string("Assets/Balls/ball_" + std::to_string(std::rand() % 6) + ".png"));
	sprite.setTexture(texture);
	sprite.setPosition(pos);
	sprite.setScale({ 0.04f, 0.04f });

	dir = { this->speed, -this->speed };

	conds[0] = true;
	for (int i = 1; i < 8; i++)
		conds[i] = false;
}

Ball::~Ball()
{
}

bool Ball::update(const Map& map, const Platform& platform, const std::vector<Brick*>& bricks)
{
	if (map_collision_which(map) == 1)
	{
		conds[0] = false;
		conds[1] = true;
		conds[2] = false;
		conds[3] = false;
		conds[4] = false;
		conds[5] = false;
		conds[6] = false;
		conds[7] = false;
	}

	else if (map_collision_which(map) == 2)
	{
		conds[0] = false;
		conds[1] = false;
		conds[2] = true;
		conds[3] = false;
		conds[4] = false;
		conds[5] = false;
		conds[6] = false;
		conds[7] = false;
	}

	else if (map_collision_which(map) == 3)
	{
		conds[0] = false;
		conds[1] = false;
		conds[2] = false;
		conds[3] = true;
		conds[4] = false;
		conds[5] = false;
		conds[6] = false;
		conds[7] = false;
	}

	else if (map_collision_which(map) == 4)
	{
		conds[0] = false;
		conds[1] = false;
		conds[2] = false;
		conds[3] = false;
		conds[4] = true;
		conds[5] = false;
		conds[6] = false;
		conds[7] = false;
	}

	else if (is_collided_with_platform(platform))
	{
		conds[0] = false;
		conds[1] = false;
		conds[2] = false;
		conds[3] = false;
		conds[4] = false;
		conds[5] = true;
		conds[6] = false;
		conds[7] = false;
	}

	else if (is_collided_with_brick(bricks) == 1)
	{
		conds[0] = false;
		conds[1] = false;
		conds[2] = false;
		conds[3] = false;
		conds[4] = false;
		conds[5] = false;
		conds[6] = true;
		conds[7] = false;
	}

	else if (is_collided_with_brick(bricks) == 2)
	{
		conds[0] = false;
		conds[1] = false;
		conds[2] = false;
		conds[3] = false;
		conds[4] = false;
		conds[5] = false;
		conds[6] = false;
		conds[7] = true;
	}

	if (conds[0])
	{
		dir = { speed, -speed };
		sprite.move(dir);

		return false;
	}

	if (conds[1])
	{
		if (dir.y > 0)
			dir = { speed, speed };

		else if (dir.y < 0)
			dir = { speed, -speed };

		sprite.move(dir);

		return false;
	}

	if (conds[2])
	{
		if (dir.y > 0)
			dir = { -speed, speed };

		else if (dir.y < 0)
			dir = { -speed, -speed };

		sprite.move(dir);

		return false;
	}

	if (conds[3])
	{
		if (dir.x < 0)
			dir = { -speed, speed };

		else if (dir.x > 0)
			dir = { speed, speed };

		sprite.move(dir);

		return false;
	}

	if (conds[4])
	{
		return true;
	}

	if (conds[5])
	{
		if (dir.x < 0)
			dir = { -speed, -speed };

		else if (dir.x > 0)
			dir = { speed, -speed };

		sprite.move(dir);

		return false;
	}

	if (conds[6])
	{
		if (dir.x < 0)
			dir = { -speed, speed };

		else if (dir.x > 0)
			dir = { speed, speed };

		sprite.move(dir);

		return false;
	}

	if (conds[7])
	{
		if (dir.x < 0)
			dir = { -speed, -speed };

		else if (dir.x > 0)
			dir = { speed, -speed };

		sprite.move(dir);

		return false;
	}
}

void Ball::draw(sf::RenderWindow& window) const
{
	window.draw(sprite);
}

sf::Sprite Ball::getBall() const
{
	return sprite;
}

int Ball::map_collision_which(const Map& map) const
{
	for (const auto& wall_left : map.left_walls())
		if (sprite.getPosition().x >= wall_left.getPosition().x &&
			sprite.getPosition().x + 2.0f < wall_left.getPosition().x + sprite.getGlobalBounds().width)
			return 1;

	for (const auto& wall_right : map.right_walls())
		if (sprite.getPosition().x <= wall_right.getPosition().x &&
			sprite.getPosition().x - 7.0f > wall_right.getPosition().x - sprite.getGlobalBounds().width)
			return 2;

	for (const auto& wall_up : map.upper_walls())
		if (sprite.getPosition().y >= wall_up.getPosition().y &&
			sprite.getPosition().y + 6.0f < wall_up.getPosition().y + wall_up.getGlobalBounds().height)
			return 3;

	for (const auto& wall_down : map.lower_walls())
		if (sprite.getGlobalBounds().contains(wall_down.getPosition()))
			return 4;

	return 0;
}

int Ball::is_collided_with_brick(const std::vector<Brick*>& bricks) const
{
	for (const auto& brick : bricks)
		if (sprite.getPosition().y + 25.0f == brick->getBrick().getPosition().y + brick->getBrick().getGlobalBounds().height &&
			sprite.getPosition().x >= brick->getBrick().getPosition().x &&
			sprite.getPosition().x + 8.0f <= brick->getBrick().getPosition().x + brick->getBrick().getGlobalBounds().width)
			return 1;

	for (const auto& brick : bricks)
		if (sprite.getPosition().y + 3.0f == brick->getBrick().getPosition().y &&
			sprite.getPosition().x >= brick->getBrick().getPosition().x &&
			sprite.getPosition().x + 8.0f <= brick->getBrick().getPosition().x + brick->getBrick().getGlobalBounds().width)
			return 2;

	return 0;
}

bool Ball::is_collided_with_platform(const Platform& platform) const
{
	if ((sprite.getPosition().y == platform.getPlatform().getPosition().y ||
		sprite.getGlobalBounds().contains(platform.getPlatform().getPosition())) &&
		sprite.getPosition().x + 10 >= platform.getPlatform().getPosition().x &&
		sprite.getPosition().x <= platform.getPlatform().getPosition().x + platform.getPlatform().getGlobalBounds().width)
		return true;

	return false;
}