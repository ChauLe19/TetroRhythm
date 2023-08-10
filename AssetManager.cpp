#include "AssetManager.h"

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
}

void AssetManager::loadTexture(std::string name, std::string filename)
{
	sf::Texture texture;

	if (texture.loadFromFile(filename))
	{
		this->textures[name] = texture;
	}
}

sf::Texture& AssetManager::getTexture(std::string name)
{
	return this->textures.at(name);
}

void AssetManager::loadFont(std::string name, std::string filename)
{
	sf::Font font;

	if (font.loadFromFile(filename))
	{
		this->fonts[name] = font;
	}
}

sf::Font& AssetManager::getFont(std::string name)
{
	return this->fonts.at(name);
}
