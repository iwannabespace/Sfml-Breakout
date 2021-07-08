#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "Map.hpp"
#include "Platform.hpp"
#include "Brick.hpp"
#include "Ball.hpp"

int main()
{
	std::srand(static_cast<unsigned int>(std::time(0)));

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(325, 450), "Breakout", sf::Style::Default, settings);
	window.setFramerateLimit(120);

	Map map;
	Platform platform({ 100.0f, 350.0f });
	Ball ball({ 140.0f, 345.0f }, 1.0f);

	sf::Vector2f pos = { 55.0f, 50.0f };
	std::vector<Brick*> bricks;

	for (int i = 0; i < 5; i++)
	{
		bricks.push_back(new Brick(pos));
		pos.x += 32.0f;
	}

	pos = { 55.0f, 70.0f };

	for (int i = 0; i < 5; i++)
	{
		bricks.push_back(new Brick(pos));
		pos.x += 32.0f;
	}

	bool start = false;

	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		if (!start)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				start = true;
		}

		else
		{
			platform.move(1.0f, map);

			if (ball.update(map, platform, bricks))
				window.close();

			for (auto& brick : bricks)
				brick->update(ball);	

			for (int i = 0; i < bricks.size(); i++)
				if (bricks[i]->total_hits() >= 4)
				{
					delete bricks[i];
					bricks.erase(bricks.begin() + i);
				}
		}

		window.clear(sf::Color::Black);
		map.draw(window);
		platform.draw(window);
		for (int i = 0; i < bricks.size(); i++)
			bricks[i]->draw(window);
		ball.draw(window);
		window.display();
	}

	return 0;
}