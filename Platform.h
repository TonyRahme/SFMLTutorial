#pragma once
#include "Collider.h"
#include <SFML\Graphics.hpp>
class Platform
{
public:
	Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Platform(void);

	void Draw(sf::RenderWindow& window);
	Collider GetCollider() {return Collider(body);}
private:
	sf::RectangleShape body;
};

