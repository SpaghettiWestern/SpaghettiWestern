#ifndef GAMERESOURCES_H
#define GAMERESOURCES_H

#include "BlitHelper.h"
#include <memory>
#include <map>

class GameResources{
private:
	std::map<std::string, std::shared_ptr<SDL_Surface>> bmp_surfaces;


public:
	GameResources(std::vector<std::string> resource_directories);
	GameResources(std::string resource_directory);

	bool importImage(std::string filename);

	const std::unique_ptr<SDL_Texture>& getSurface(std::string surface_path) const;
};


#endif
