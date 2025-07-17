#include "ai/npc.h"

#include <iostream>
#include <random>

#include "motion/AStar.h"

using namespace api::motion;

namespace api::ai{

    void Npc::Setup(std::string_view name, std::string_view filename,
                    TileMap* tilemap,  std::string color,std::vector<resource::Resource> ressources, ui::Ressource_UI* ressource_ui) {
        name_ = std::string(name);


        if(!texture_.loadFromFile("_assets/sprites/" + std::string(filename))) {
            std::cout << "Error loading texture " << filename << std::endl;
            if (!texture_.loadFromFile("_assets/sprites/empty.png")) {
                std::cout << "Error loading texture empty.png" << std::endl;
            }
        }

        //std::cout << "Setup " << name_ << " -- -- -- -- -- -- -- -- -- -- -- -- -- " << std::endl;
    	std::string basePath = "_assets/sprites/";
    	if (!directionTextures_[Direction::Right].loadFromFile(basePath + "Farmer" + color + "Right.PNG")) {

    		std::cout << "Error loading right texture" << std::endl;
    	}
    	if (!directionTextures_[Direction::Left].loadFromFile(basePath + "Farmer" + color + "Left.PNG")) {
    		std::cout << "Error loading left texture" << std::endl;
    	}
    	if (!directionTextures_[Direction::Up].loadFromFile(basePath + "Farmer" + color + "Back.PNG")) {
    		std::cout << "Error loading up texture" << std::endl;
    	}
    	if (!directionTextures_[Direction::Down].loadFromFile(basePath + "Farmer" + color + ".PNG")) {
    		std::cout << "Error loading down texture" << std::endl;
    	}

    	currentDirection_ = Direction::Down; // Direction par défaut
        bt_tree_->SetupBehaviourTree(motor_.get(), path_.get(), tilemap, color,
									 ressources, ressource_ui);

        motor_->SetPosition({0, 0});
        motor_->SetSpeed(kMovingSpeed);

    }

    void Npc::Update(const float dt){

        // // Updating
        // std::cout << "\n";
        // std::cout << " -- -- -- -- -- -- -- -- -- -- -- -- -- \n";
        // std::cout << "Update " << name_ << "\n";
        // std::cout << " -- -- -- -- -- -- -- -- -- -- -- -- -- \n";

        // -------------------
        if (path_->IsValid()){
            motor_->Update(dt);
            if (!path_->IsDone() && motor_->RemainingDistance() <= 0.001f) {
            	SetDirection();
                motor_->SetDestination(path_->GetNextPoint());
            }
        }

        bt_tree_->Update(dt);

    }

    void Npc::Draw(sf::RenderWindow &window){
        sf::Sprite sprite(texture_);
        sprite.setPosition(motor_->GetPosition());
        window.draw(sprite);
    }
void Npc::SetDirection() {
    	if (!path_->IsValid()) return;

    	sf::Vector2f nextPoint = path_->GetNextPoint();
    	sf::Vector2f currentPos = motor_->GetPosition();
    	sf::Vector2f delta = nextPoint - currentPos;

    	// Détermine la direction principale (priorité horizontale)
    	if (std::abs(delta.x) > std::abs(delta.y)) {
    		currentDirection_ = (delta.x > 0) ? Direction::Right : Direction::Left;
    	} else {
    		currentDirection_ = (delta.y > 0) ? Direction::Down : Direction::Up;
    	}

    	// Change la texture en fonction de la direction
    	auto it = directionTextures_.find(currentDirection_);
    	if (it != directionTextures_.end()) {
    		texture_ = it->second; // Copie la texture (léger, car SFML gère les données internes)
    	}
    }
    // void Npc::SetPath(const Path& path){
    //     path_ = path;
    //     motor_.SetDestination(path_.StartPoint());
    // }

}
