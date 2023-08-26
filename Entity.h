#pragma once
#include <SFML/Graphics.hpp>
class Entity
{
private:
public:
	Entity();
	virtual ~Entity();

	virtual void move(const float& dt, const float x, const float y);

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

