#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <filesystem>

namespace fs = std::filesystem;

class AssetManager
{
private:
	static AssetManager* assetManager;
	std::map<std::string, std::string> textureFiles;
	std::map<std::string, std::string> fontFiles;
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Font> fonts;
	std::map<std::string, std::unique_ptr<sf::Drawable>> drawables;

	AssetManager();
	~AssetManager();

public:
	static AssetManager* getInstance();
	
	static fs::path getImageFilePathExtension(fs::path filePathWithNoExtention);
	static fs::path getAudioFilePathExtension(fs::path filePathWithNoExtention);

	void loadTexture(std::string name, std::string fileName);
	sf::Texture& getTexture(std::string name);

	void loadFont(std::string name, std::string fileName);
	sf::Font& getFont(std::string name);

	void loadDrawable(std::string name, std::unique_ptr<sf::Drawable> drawable);
	sf::Drawable& getDrawable(std::string name);
};

