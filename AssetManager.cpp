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
	this->textureFiles[name] = filename;
}

sf::Texture& AssetManager::getTexture(std::string name)
{
	if (this->textures.find(name) == this->textures.end())
	{
		sf::Texture texture;
		if (texture.loadFromFile(this->textureFiles.at(name)))
		{
			this->textures[name] = texture;
		}
	}
	return this->textures.at(name);
}

void AssetManager::loadFont(std::string name, std::string filename)
{
	this->fontFiles[name] = filename;
}

sf::Font& AssetManager::getFont(std::string name)
{
	if (this->fonts.find(name) == this->fonts.end())
	{
		sf::Font font;
		if (font.loadFromFile(this->fontFiles.at(name)))
		{
			this->fonts[name] = font;
		}
	}
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
