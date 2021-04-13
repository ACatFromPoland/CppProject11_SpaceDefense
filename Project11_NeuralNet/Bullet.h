#pragma once
#include <SFML/Graphics.hpp>
#include "Vectors.h"

class Bullet;
typedef std::vector<Bullet> BulletVector;
class Bullet {
public:
	Vector2 position = Vector2(0.f, 0.f);
	Vector2 velocity = Vector2(0.f, 0.f);

	Vector2 dim = Vector2(2.f, 2.f);
	sf::RectangleShape rect;
	Bullet() {
		rect.setSize(dim.asSF());
	}

	void update(float deltatime) {
		position = position + (velocity * deltatime);
	}

	void draw(sf::RenderWindow &window) {
		rect.setPosition(position.asSF());
		window.draw(rect);
	}
};
