#pragma once
#include <SFML/Graphics.hpp>
#include "Vectors.h"
#include "Cannon.h"
#include "Bullet.h"

class Turret {
public:
	Vector2 dim = Vector2(36.f, 10.f);
	//Vector2 position = Vector2(WINDOWY / 2, WINDOWX - dim.y);
	Vector2 position = Vector2(0.f, 0.f);

	sf::RectangleShape rect;
	Cannon cannon;

	Turret(float winX, float winY) {
		rect.setSize(dim.asSF());
		rect.setOrigin(sf::Vector2f(dim.x / 2, 0.f));
		position = Vector2(winX / 2, winY - dim.y);

		//cannon.position = position + Vector2(0.f, cannon.dim.y * -1);
		cannon.position = position;
		cannon.angle = 180.f;
	}

	void shoot(BulletVector &bullArray) {
		bullArray.resize(bullArray.size() + 1);
		Bullet &blt = bullArray[bullArray.size() - 1];
		double radions = (cannon.angle + 90) * 0.0174533;
		Vector2 direction = Vector2(cos(radions), sin(radions));
		blt.position = cannon.position + direction;
		blt.velocity = direction * 960.f;;
	}

	void draw(sf::RenderWindow &window) {
		rect.setPosition(position.asSF()); // Draw turret
		window.draw(rect);

		cannon.rect.setPosition(cannon.position.asSF());
		cannon.rect.setRotation(cannon.angle);
		window.draw(cannon.rect);
	}
};