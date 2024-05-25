#pragma once
#include "Button.h"

class GravityButton : public Button
{
private:
	int progress = 0;
	sf::RectangleShape progressRect;
public:
	GravityButton(const sf::Text& text = sf::Text());
	~GravityButton();
	void setPosition(const sf::Vector2f& position) override;
	void setProgressFillColor(const sf::Color& color);
	void setProgress(int progress);
	void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const;
};

