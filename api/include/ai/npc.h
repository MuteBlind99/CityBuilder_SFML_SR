#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>

#include "graphics/tilemap.h"
#include "motion/motor.h"
#include "motion/path.h"
#include "npc_behaviour_tree.h"
#include "ressources/ressource.h"

namespace api::ai {
enum class Direction {
	Up,
	Down,
	Left,
	Right
};
class Npc {
	sf::Texture texture_;

	//NpcType type_ = NpcType::kNone;
	// Decision
	std::unique_ptr<NpcBehaviourTree> bt_tree_ =
		std::make_unique<NpcBehaviourTree>();

	// Movement
	static constexpr float kMovingSpeed = 200.0f;
	std::unique_ptr<motion::Motor> motor_ = std::make_unique<motion::Motor>();
	std::unique_ptr<motion::Path> path_ = std::make_unique<motion::Path>();

	// name
	std::string name_;

	// World informations
	// Tilemap
	// const TileMap *tileMap_;

	std::unordered_map<Direction, sf::Texture> directionTextures_;
	Direction currentDirection_ = Direction::Down;

   public:
	void Setup(std::string_view name, std::string_view filename,
			   TileMap* tilemap, std::string color,
			   std::vector<resource::Resource> ressources);
	void Update(float dt);
	void Draw(sf::RenderWindow& window);
	void SetDirection();
	void SetPosition(const sf::Vector2f& position) {
		motor_->SetPosition(position);
	}
	void SetStartPos(const sf::Vector2f& position) {
		bt_tree_->SetStartPos(position);
	}

	// Motion
	// void SetPath(const motion::Path &path);
};
}  // namespace api::ai

#endif	// NPC_H
