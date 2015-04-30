#include "stdafx.h"
#include "ImageManager.h"
#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>

ImageManager::ImageManager() 
{
}


ImageManager::~ImageManager()
{
	_textures.clear();
	_resourcesDirectories.clear();
}


const sf::Texture& ImageManager::GetImage(const std::string& filename)
{
	// Check, whether the image already exists
	for (std::map<std::string, sf::Texture>::const_iterator it = _textures.begin();
		it != _textures.end();
		++it)
	{
		if (filename == it->first)
		{
			std::cout << "DEBUG_MESSAGE: " << filename << " using existing image.\n";
			return it->second;
		}
	}

	// The image doesen't exists. Create it and save it.
	sf::Texture texture;

	// Search project's main directory
	if (texture.loadFromFile(filename))
	{
		_textures[filename] = texture;
		std::cout << "DEBUG_MESSAGE: " << filename << " loading image.\n";
		return _textures[filename];
	}

	// If the image has still not been found, search all registered directories
	for (std::vector< std::string >::iterator it = _resourcesDirectories.begin();
		it != _resourcesDirectories.end();
		++it)
	{
		if (texture.loadFromFile((*it) + filename))
		{
			_textures[filename] = texture;
			std::cout << "DEBUG_MESSAGE: " << filename << " loading image.\n";
			return _textures[filename];
		}

	}

	std::cout << "GAME_ERROR: Image was not found. It is filled with an empty image.\n";
	_textures[filename] = texture;
	return _textures[filename];
}

void ImageManager::DeleteImage(const sf::Texture& texture)
{
	for (std::map<std::string, sf::Texture>::const_iterator it = _textures.begin();
		it != _textures.end();
		++it)
	{
		if (&texture == &it->second)
		{
			_textures.erase(it);
			return;
		}
	}
}

void ImageManager::DeleteImage(const std::string& filename)
{
	std::map<std::string, sf::Texture>::const_iterator it = _textures.find(filename);
	if (it != _textures.end())
		_textures.erase(it);
}

void ImageManager::AddResourceDirectoy(const std::string& directory)
{
	// Check whether the path already exists
	for (std::vector<std::string>::const_iterator it = _resourcesDirectories.begin();
		it != _resourcesDirectories.end();
		++it)
	{
		// The path exists. So it isn't necessary to add id once more.
		if (directory == (*it))
			return;
	}

	// insert the directory
	_resourcesDirectories.push_back(directory);
}

void ImageManager::RemoveResourceDirectory(const std::string& directory)
{
	for (std::vector<std::string>::iterator it = _resourcesDirectories.begin();
		it != _resourcesDirectories.end();)
	{
		// The path exists. So it isn't necessary to add id once more.
		if (directory == (*it))
			it = _resourcesDirectories.erase(it);
		else
			++it;
	}
}