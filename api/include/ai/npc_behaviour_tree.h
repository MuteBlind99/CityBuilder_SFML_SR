//
// Created by sebas on 19/06/2025.
//

#ifndef NPC_BEHAVIOUR_TREE_H
#define NPC_BEHAVIOUR_TREE_H

#include <memory>

#include "ai/bt_node.h"
#include "graphics/tilemap.h"
#include "motion/motor.h"
#include "motion/path.h"
#include "ressources/ressource.h"
#include "ui/resource_ui.h"

namespace api::ai {
class NpcBehaviourTree {
	// Behaviour tree
	std::unique_ptr<core::ai::behaviour_tree::Node> bt_root_;

	// Env informations ----------------------
	TileMap* tilemap_ = nullptr;
	// Ways of action
	motion::Motor* npc_motor_ = nullptr;
	motion::Path* path_ = nullptr;

	void SetDestination(const sf::Vector2f& destination) const;
	// Actions
	[[nodiscard]] core::ai::behaviour_tree::Status CheckHunger() const;
	[[nodiscard]] core::ai::behaviour_tree::Status Move() const;
	[[nodiscard]] core::ai::behaviour_tree::Status Eat();
	[[nodiscard]] core::ai::behaviour_tree::Status PickRessource();
	[[nodiscard]] core::ai::behaviour_tree::Status GetRessource();
	[[nodiscard]] core::ai::behaviour_tree::Status Idle();

	// Behaviour Constants
	static constexpr float kHungerRate = 2.f;
	static constexpr float kExploitRate = 2.f;

	// Behaviours
	float hunger_ = 0.0f;
	bool resourceAvailable_ = true;
	float tick_dt = 0;

	sf::Vector2f start_position_;
	std::vector<resource::Resource> ressources_;
	resource::Resource current_ressource_;
	ui::Ressource_UI ressource_ui;

   public:
	void SetStartPos(const sf::Vector2f& position) {
		start_position_ = position;
	}

	void SetupBehaviourTree(motion::Motor* npc_motor, motion::Path* path,
							TileMap* tilemap, std::string color,
							std::vector<resource::Resource> resources);
	void Update(float dt);
	bool isEating = false;
};
}  // namespace api::ai

#endif	// NPC_BEHAVIOUR_TREE_H
