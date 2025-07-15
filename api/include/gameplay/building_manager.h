//
// Created by forna on 11.07.2025.
//

#ifndef BUILDING_MANAGER_H
#define BUILDING_MANAGER_H
#include <SFML/Graphics/Texture.hpp>
#include <array>

#include "assets/asset_manager.h"
#include "building.h"
namespace api::gameplay {
class BuildingManger {
public:
	enum class BuildingSprite { kEmpty, kWoodCut, kMinners, kHarvest, kLength };
	void CreateBuilding(sf::Vector2f pos,BuildingSprite building_sprite);
	void Draw(sf::RenderWindow &window) const;

private:
	sf::Texture textureWood_;
	sf::Texture textureRock_;
	sf::Texture textureFood_;
	std::vector<Building> buildings_;


};


}


#endif //BUILDING_MANAGER_H
