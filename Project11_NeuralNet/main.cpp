#include <string>

#include <SFML/Graphics.hpp>
#include "Vectors.h"
#include "buttonInput.h"
#include "Turret.h"
#include "Enemy.h"
#include "Bullet.h"

#define WINDOWX 800
#define WINDOWY 800

#define getrandom(min, max) ((rand()%(int)(((max) + 1) - (min)))+ (min))

bool outOfBounds(Vector2 position) {
	bool out = false;
	if (position.x < 0)
		out = true;
	if (position.x > WINDOWX)
		out = true;
	if (position.y < 0)
		out = true;
	if (position.y > WINDOWY)
		out = true;
	return out;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOWX, WINDOWY), "Asteroid? Maybe?", sf::Style::Close);
	sf::Clock clock;

	// player stuff
	Turret player = Turret(WINDOWX, WINDOWY);
	newPressKey shoot = sf::Keyboard::Key::Space;
	newToggleKey fullAuto = sf::Keyboard::Key::LAlt;

	sf::Font MyFont;
	if (!MyFont.loadFromFile("aerial.ttf"))
	{
		// Error...
	}

	sf::Text text;
	text.setFont(MyFont);
	text.setCharacterSize(20);
	text.setPosition(5.f, 5.f);
	int score = 0;
	std::string scoredisp = "Score: " + std::to_string(score);
	text.setString(scoredisp);

	// world
	int level = 1;
	int enemies = 2;
	EnemyVector enemyVector(enemies);
	for (int i = 0; i < enemyVector.size(); i++) {
		enemyVector[i].Init(WINDOWX, WINDOWY);
	}

	// Game over
	sf::Text gameOverText;
	gameOverText.setFont(MyFont);
	gameOverText.setCharacterSize(40);
	gameOverText.setPosition(WINDOWX / 2, WINDOWY / 2);
	gameOverText.setOrigin(sf::Vector2f(WINDOWX/4, 0.f));
	gameOverText.setString(std::string("GAME OVER!"));
	//gameOverText.setColor(sf::Color::Red);
	bool gameOver = false;


	BulletVector bulletVector(0);


	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		float deltatime = clock.restart().asSeconds();
		window.clear(sf::Color::Black);
		//
		if (!gameOver) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
			{
				if (player.cannon.angle > 90)
					player.cannon.angle += -100.f * deltatime;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
			{
				if (player.cannon.angle < 270)
					player.cannon.angle += 100.f * deltatime;
			}

			if (fullAuto.isToggled()) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
					player.shoot(bulletVector);
			}
			else {
				if (shoot.isPressed())
					player.shoot(bulletVector);
			}

			// Update Bullets
			for (int i = 0; i < bulletVector.size(); i++) {
				if (outOfBounds(bulletVector[i].position)) { // If out of bounds
					bulletVector.erase(bulletVector.begin() + i);
				}
				else { // If not then update
					bulletVector[i].update(deltatime);
				}
			}

			// Update enemies
			for (int i = 0; i < enemyVector.size(); i++) {
				if (enemyVector[i].died) {
					enemyVector.erase(enemyVector.begin() + i);
					enemies--;
					score += 10;
				}
				else {
					enemyVector[i].update(bulletVector, player.position, deltatime);
					if (player.position.distanceTo(enemyVector[i].position) < enemyVector[i].radius) {
						player.rect.setFillColor(sf::Color::Red);
						gameOver = true;
					}
				}
			}
		}
		else {
			text.setPosition(WINDOWX / 2, WINDOWY / 2 + 50.f);
			text.setOrigin(100.f,0.f);
			window.draw(gameOverText);
			window.draw(text);
		}
		// Render everything
		for (int i = 0; i < enemyVector.size(); i++) {
			enemyVector[i].draw(window);
		}
		for (int i = 0; i < bulletVector.size(); i++) {
			bulletVector[i].draw(window);
		}
		player.draw(window);

		text.setString("Score: " + std::to_string(score));
		window.draw(text);
		//

		window.display();

		// Reset enemies
		if (enemies <= 0) {
			level++;
			enemies = 2 * level;
			enemyVector.resize(enemies);
			for (int i = 0; i < enemyVector.size(); i++) {
				enemyVector[i].Init(WINDOWX, WINDOWY);
			}
		}

	}
	return 0;
}