#include "AssetManager.h"

AssetManager* AssetManager::assetManager;

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
}

AssetManager* AssetManager::getInstance()
{
	if (assetManager == nullptr)
	{
		assetManager = new AssetManager();
	}
	return assetManager;
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

void AssetManager::loadDrawable(std::string name, std::unique_ptr<sf::Drawable> drawable)
{
	this->drawables[name] = std::move(drawable);
}

sf::Drawable& AssetManager::getDrawable(std::string name)
{
	return *this->drawables.at(name);
}
