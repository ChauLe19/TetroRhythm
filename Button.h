#pragma once
#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <functional>
#include "Utils.h"

class Button : public sf::Drawable
{
	enum ButtonState
	{
		Idle,
		Hover,
		Pressed,
		PressedOutside, // mouse pressing but moved outside of the button
		Selected,
		SelectedHover,
		SelectedPressed,
		SelectedPressedOutside // in a selected state with mouse pressed but moved outside
	};
protected:
	bool m_isSelectable;
	ButtonState state = Idle;
	sf::Color boxColor;
	sf::Color highlightColor;
	sf::Color baseColor;
	sf::Text text;
	std::function<void(void)> callback = std::function<void()>();

	sf::RectangleShape buttonRect;
	sf::Keyboard::Key key;
public:
	Button(sf::Text text = sf::Text());
	Button(sf::RectangleShape buttonRect, sf::Text text, sf::Color baseColor, sf::Color highlightColor);
	~Button();
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	void setSize(const sf::Vector2f& size);
	void setFont(const sf::Font& font);
	void setFontSize(unsigned int fontSize);
	void setTextString(std::string textString);
	void recomputePosition();
	void setHighlightColor(const sf::Color& color);
	void setBaseColor(const sf::Color& color);
	void setColor(const sf::Color& baseColor, const sf::Color& highlightColor);
	virtual void setPosition(const sf::Vector2f& position);
	void setFillColor(const sf::Color& color);
	void setShortcut(const sf::Keyboard::Key& key); // set keyboard equivalent/shortcut
	void setCallback(std::function<void(void)> callback); // set function to be executed on click
	bool isSelectable();
	void setSelectable(bool selectable);
	void setSelected(bool selected);
	bool keyEvent(sf::Keyboard::Key key);
	bool mouseInButton(sf::RenderWindow& window);
	bool posInButton(int x, int y);
	void mouseEvent(sf::RenderWindow& window, sf::Event event);


	// Inherited via Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

};
#endif
