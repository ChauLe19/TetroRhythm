#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>
#include <filesystem>
using namespace sf;
using namespace std;


bool mouseInBox(RenderWindow& window, int x, int y, int width, int height);
bool mouseInCircle(RenderWindow& window, int x, int y, int r);
void createButton(RenderWindow& window, Text& text,  Color textColor, int fontSize, Color boxColor, string textString, int width, int height, int x, int y);
std::string getLeftPaddingString(std::string const& str, int n, char paddedChar = ' ');

#endif

