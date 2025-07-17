//
// Created by sebas on 19/06/2025.
//

#ifndef NPC_MANAGER_H
#define NPC_MANAGER_H

#include "ai/npc.h"
#include "ressources/ressource_manager.h"

namespace api::ai{

enum class NpcType {
	kNone,
	kBlueWood,
	kRedRock,
	kGreenFood
};

class NpcManager {
	std::vector<Npc> npcs_;

public:
	void Add(NpcType type, sf::Vector2f start_position, TileMap *tilemap,
		  std::string color, ResourceManager ressource_manager,
		  ui::Ressource_UI *ressource_ui);
	void Update(float dt);
	void Draw(sf::RenderWindow &window);
	//bool isCreated=false;

};

}



#endif //NPC_MANAGER_H
