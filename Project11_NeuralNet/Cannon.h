#pragma once
#include <SFML/Graphics.hpp>
#include "Vectors.h"
class Cannon {
public:
	Vector2 position = Vector2(0.f, 0.f);

	Vector2 dim = Vector2(3.f, 15.f);
	float angle = 0.f;

	sf::RectangleShape rect;
	Cannon() {
		rect.setSize(dim.asSF());
		rect.setOrigin(sf::Vector2f(dim.x / 2, 0.f));
	}
};