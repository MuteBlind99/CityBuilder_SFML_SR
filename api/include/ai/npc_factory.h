//
// Created by sebas on 19/06/2025.
//

#ifndef NPC_FACTORY_H
#define NPC_FACTORY_H
#include "npc_manager.h"
#include "ui/resource_ui.h"

namespace api::ai {

inline void ChopEvent(int index, float quantity, const NpcType type,
					  ui::Ressource_UI& ui) {
	auto tilemap_ptr_ = std::make_unique<TileMap>();
	;
	std::cout << "chop event : " << index << "," << quantity << "Cofe" << "\n";
	if (quantity <= 0) {
		tilemap_ptr_->SetTile(index, TileMap::Tile::kBg);

	}
}
inline void CreateNpc(std::vector<Npc>& npcs, const NpcType type,
					  sf::Vector2f start_position, TileMap* tilemap,
					  std::string& color, const ResourceManager& ressources) {
	std::vector<int> vec_index;

	std::cout << "Creating npc" << std::endl;
	switch (type) {
		case NpcType::kBlueWood:
			npcs.emplace_back();
			// ressources.LoadRessources(Ressource::Type::kWood,vec_index,ChopEvent);
			npcs.back().Setup("BLUE", "FarmerCyan.PNG", tilemap, "Cyan",
							  ressources.GetResources(resource::Resource::Type::kWood)
							  );

			break;
		case NpcType::kRedRock:
			npcs.emplace_back();
			// ressources.LoadRessources(Ressource::Type::kStone,vec_index,ChopEvent);
			npcs.back().Setup("RED", "FarmerRed.PNG", tilemap, "Red",
							  ressources.GetResources(resource::Resource::Type::kStone));
			break;
		case NpcType::kGreenFood:
			npcs.emplace_back();
			// ressources.LoadRessources(Ressource::Type::kFood,vec_index,ChopEvent);
			npcs.back().Setup("GREEN", "FarmerLime.PNG", tilemap, "Lime",
							  ressources.GetResources(resource::Resource::Type::kFood));
			break;
		default:
			std::cout << "Error: Npc type not found" << std::endl;
			break;
	}

	if (type == NpcType::kBlueWood || type == NpcType::kRedRock ||
		type == NpcType::kGreenFood) {
		npcs.back().SetPosition(start_position);
		npcs.back().SetStartPos(start_position);
	}
}
}  // namespace api::ai

#endif	// NPC_FACTORY_H
