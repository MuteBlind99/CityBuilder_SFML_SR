#include "gameplay/building_manager.h"
//
// Created by forna on 11.07.2025.
//
void api::gameplay::BuildingManger::CreateBuilding(
	sf::Vector2f pos, BuildingSprite building_sprite) {
	std::string path = "_assets/sprites/";
	switch (building_sprite) {
		case BuildingSprite::kEmpty:
			break;
		case BuildingSprite::kWoodCut:
			if (!textureWood_.loadFromFile(path + "CyanHuts.PNG")) {
			}
			buildings_.emplace_back(pos, textureWood_);
			break;
		case BuildingSprite::kMinners:
			if(!textureRock_.loadFromFile(path + "RedBarracks.PNG")) {
			}
			buildings_.emplace_back(pos, textureRock_);
			break;
		case BuildingSprite::kHarvest:
			if (!textureFood_.loadFromFile(path + "LimeTaverns.PNG")) {
			}
			buildings_.emplace_back(pos, textureFood_);
			break;
		case BuildingSprite::kLength:
			break;
	}


}
void api::gameplay::BuildingManger::Draw(sf::RenderWindow& window) const {

	for (const auto& building : buildings_) {
		building.Draw(window);
	}

}
