#include "GameResources.h"



GameResources::GameResources(std::vector<std::string> resource_directories){

}
GameResources::GameResources(std::string resource_directory){

}

bool GameResources::importImage(std::string filename){
	return true;
}

const std::unique_ptr<SDL_Texture>& GameResources::getSurface(std::string surface_path) const{


}

