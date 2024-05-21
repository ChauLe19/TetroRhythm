#pragma once
#include <SFML/Graphics.hpp>
class ProgressBar : public sf::Drawable
{
private:
public:
	ProgressBar(int min, int max, sf::Vector2f position, sf::Vector2f size);

	// Inherited via Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

