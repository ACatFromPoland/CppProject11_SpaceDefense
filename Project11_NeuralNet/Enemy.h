#pragma once
#include <SFML/Graphics.hpp>
#include "Vectors.h"
#include "Bullet.h"
#include "Turret.h"

#define getrandom(min, max) ((rand()%(int)(((max) + 1) - (min)))+ (min))

class Enemy;
typedef std::vector<Enemy> EnemyVector;
class Enemy {
public:
	Vector2 position = Vector2(0.f, 0.f);
	Vector2 velocity = Vector2(0.f, 0.f);

	sf::CircleShape rect;
	float radius = 6.f;
	Enemy() {
		rect.setRadius(radius);
		rect.setOrigin(sf::Vector2f(radius / 2, 0.f));
	}
	void Init(float winX, float winY) {
		position.x = getrandom(-500.f, winX + 500.f);
		position.y = getrandom(-500.f, -100.f);
	}
	
	bool died = false;
	float maxSpeed = 200.f;
	void update(BulletVector &bullets, Vector2 playercords, float deltatime) {
		if (bullets.size() > 0) {
			for (int i = 0; i < bullets.size(); i++) {
				Bullet &blt = bullets[i];
				if (position.distanceTo(blt.position) < radius) {
					rect.setFillColor(sf::Color::Red);
					died = true;
				}
			}
		}

		Vector2 direction = playercords - position;
		direction.normalized();
		Vector2 velocity = direction * maxSpeed;

		position = position + (velocity * deltatime);
	}

	void draw(sf::RenderWindow &window) {
		rect.setPosition(position.asSF());
		window.draw(rect);
	}
};