#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
#include <filesystem>


bool mouseInBox(sf::RenderWindow& window, int x, int y, int width, int height);
bool posInBox(int posX, int posY, int x, int y, int width, int height);
bool mouseInCircle(sf::RenderWindow& window, int x, int y, int r);
void createButton(sf::RenderWindow& window, sf::Text& text,  sf::Color textColor, int fontSize, sf::Color boxColor, std::string textString, int width, int height, int x, int y);
std::string getPaddingString(std::string const& str, int n, char paddedChar = ' ', bool isPaddingRight = true);
std::string getRank(int score, int threshold);
std::string getTimeFormat(int timeInMiliseconds);

#endif

