#pragma once
class ImageManager
{
public:
	ImageManager();
	~ImageManager();
	const sf::Texture&    GetImage(const std::string& filename);
	void                DeleteImage(const sf::Texture& image);
	void                DeleteImage(const std::string& filename);
	void                AddResourceDirectoy(const std::string& directory);
	void                RemoveResourceDirectory(const std::string& directory);

private:
	ImageManager(const ImageManager&);
	ImageManager& operator =(const ImageManager&);
	std::map< std::string, sf::Texture> _textures;
	std::vector< std::string > _resourcesDirectories;

};

