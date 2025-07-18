#include "game.h"

#include "SFML/Graphics.hpp"
#include "ai/npc_manager.h"
#include "audio/audio_manager.h"
#include "gameplay/building_manager.h"
#include "graphics/tilemap.h"
#include "ressources/ressource_manager.h"
#include "ui/button.h"
#include "ui/button_factory.h"
#include "ui/clickable.h"
#include "ui/resource_ui.h"

namespace game {
namespace {
sf::Clock clock;
sf::RenderWindow window_;
api::ui::Ressource_UI ressource_ui;

auto tilemap_ptr_ = std::make_unique<TileMap>();
api::ai::NpcManager npc_manager_;

api::gameplay::BuildingManger building_manger;

// UI Elements
api::ui::ButtonFactory btn_factory;

std::unique_ptr<api::ui::Button> btnBlue;
std::unique_ptr<api::ui::Button> btnRed;
std::unique_ptr<api::ui::Button> btnGreen;
std::unique_ptr<api::ui::Button> btnExit;

api::ai::NpcType npc_adding_type = api::ai::NpcType::kNone;

ResourceManager ressource_manager_;

sf::Font font("_assets/fonts/Pixel Digivolve.otf");
sf::Music music_main("_assets/musics/La marche des gendarmes.wav");
sf::Music music_game_over("_assets/musics/Spanish Flea.wav");

// Create a text
sf::Text text(font, "Snap Regulation");
sf::Text text_game_over(font, "Starvation \n Game Over");


void ChopEvent(int index, float quantity) {
	std::cout << "chop event : " << index << "," << quantity << "\n";
	if (quantity <= 0) {
		const auto type = tilemap_ptr_->GetTile(index);
		tilemap_ptr_->SetTile(index, TileMap::Tile::kBg);
		switch (type) {
			case TileMap::Tile::kEmpty:
				std::cout << "Error not a resource" << std::endl;
				break;
			case TileMap::Tile::kTree:
				ressource_ui.woods += 5;
				break;
			case TileMap::Tile::kRock:
				ressource_ui.stones += 3;
				break;
			case TileMap::Tile::kFood:
				ressource_ui.foods += 2;
				break;
			default:
				std::cout << "Null" << std::endl;
		}
	}
}

void Setup() {
	// Create the main window
	window_.create(sf::VideoMode({1280, 800}), "SFML window");
	window_.setFramerateLimit(60);
	text.setCharacterSize(50);
	text_game_over.setCharacterSize(50);
	// text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Red);
	text_game_over.setFillColor(sf::Color::Red);
	text_game_over.setPosition(sf::Vector2f(500, 400));
	music_game_over.setLooping(true);
	music_game_over.setVolume(25);
	music_main.setLooping(true);
	music_main.setVolume(25);
	music_main.play();

	// text_ui=ressource_ui.TextWood(font,"Wood");
	ressource_ui.Setup(font);
	// text.setPosition();
	tilemap_ptr_->Setup();
	tilemap_ptr_->OnReleasedLeft = []() {
		std::cout << "Clicked tilemap" << "\n";
		//
		switch (npc_adding_type) {
			case api::ai::NpcType::kNone:
				break;
			case api::ai::NpcType::kBlueWood:
				//Need amount of wood
				if (ressource_ui.woods >= 10) {
					ressource_ui.woods-=10;
					//Woodcutter creation
					npc_manager_.Add(
						npc_adding_type,
						TileMap::TilePos(sf::Mouse::getPosition(window_)),
						tilemap_ptr_.get(), "", ressource_manager_, &ressource_ui);
					//Woodcut Buiding creation
					building_manger.CreateBuilding(
						TileMap::TilePos(sf::Mouse::getPosition(window_)),
						api::gameplay::BuildingManger::BuildingSprite::
							kWoodCut);
				}
				break;
			case api::ai::NpcType::kRedRock:
				//Need amount of stone
				if (ressource_ui.stones >= 10) {
					//Miner creation
					ressource_ui.stones-=10;
					npc_manager_.Add(
						npc_adding_type,
						TileMap::TilePos(sf::Mouse::getPosition(window_)),
						tilemap_ptr_.get(), "", ressource_manager_, &ressource_ui);

					building_manger.CreateBuilding(
						TileMap::TilePos(sf::Mouse::getPosition(window_)),
						api::gameplay::BuildingManger::BuildingSprite::
							kMinners);
				}
				break;
			case api::ai::NpcType::kGreenFood:
				//Need amount of food
				if (ressource_ui.woods >= 5 && ressource_ui.stones>=5) {
					ressource_ui.woods-=5;
					ressource_ui.stones-=5;
					//Havester creation
					npc_manager_.Add(
						npc_adding_type,
						TileMap::TilePos(sf::Mouse::getPosition(window_)),
						tilemap_ptr_.get(), "", ressource_manager_, &ressource_ui);
					building_manger.CreateBuilding(
						TileMap::TilePos(sf::Mouse::getPosition(window_)),
						api::gameplay::BuildingManger::BuildingSprite::
							kHarvest);
				}
				break;
		}
		npc_adding_type = api::ai::NpcType::kNone;
	};

	btnBlue = btn_factory.CreateButton(
		sf::Vector2f(100.f, window_.getSize().y - 100.f), "Woodcut: 10x Woods");
	btnBlue->OnReleasedLeft = []() {
		npc_adding_type = api::ai::NpcType::kBlueWood;
	};

	btnRed = btn_factory.CreateButton(
		sf::Vector2f(400.f, window_.getSize().y - 100.f), "Minners: 10x Stones");
	btnRed->OnReleasedLeft = []() {
		npc_adding_type = api::ai::NpcType::kRedRock;
	};

	btnGreen = btn_factory.CreateButton(
		sf::Vector2f(700.f, window_.getSize().y - 100.f), "Harvest: 5x Woods \n   5x Stones ");
	btnGreen->OnReleasedLeft = []() {
		npc_adding_type = api::ai::NpcType::kGreenFood;
	};

	btnExit = btn_factory.CreateButton(
		sf::Vector2f(window_.getSize().x - 100.f, 50.f), "Exit");
	btnExit->OnReleasedLeft = []() { window_.close(); };

	ressource_manager_.LoadResources(
		Resource::Type::kWood,
		tilemap_ptr_->GetCollectibles(TileMap::Tile::kTree), ChopEvent);

	ressource_manager_.LoadResources(
		Resource::Type::kFood,
		tilemap_ptr_->GetCollectibles(TileMap::Tile::kFood), ChopEvent);

	ressource_manager_.LoadResources(
		Resource::Type::kStone,
		tilemap_ptr_->GetCollectibles(TileMap::Tile::kRock), ChopEvent);
}
}  // namespace

void Loop() {
	Setup();

	// Start the game loop
	while (window_.isOpen()) {
		auto dt = clock.restart().asSeconds();

		// Process events = Input frame
		while (const std::optional event = window_.pollEvent()) {
			// Close window: exit
			if (event->is<sf::Event::Closed>()) {
				window_.close();
			}

			bool buttonsWasClicked = false;
			btnBlue->HandleEvent(event, buttonsWasClicked);
			btnRed->HandleEvent(event, buttonsWasClicked);
			btnGreen->HandleEvent(event, buttonsWasClicked);
			btnExit->HandleEvent(event, buttonsWasClicked);

			tilemap_ptr_->HandleEvent(event, buttonsWasClicked);
		}

		//Game Over no food
		if (ressource_ui.foods<=0) {
			// Graphic frame
			window_.clear();
			btnExit->Draw(window_);
			//building_manger.Draw(window_);
			ressource_ui.Draw(window_);
			window_.draw(text_game_over);

			if (music_game_over.getStatus() != sf::SoundSource::Status::Playing) {
				music_main.stop();
				music_game_over.play();
			}

			window_.display();

			//sound_.sound_buffer_.loadFromFile("La marche des gendarmes.wav");
			//sound_.SetSound(sound_.sound_buffer_);
			//sound_.PlaySound(sound_.sound_buffer_);
		}
		else {
			// GamePlay, physic frame
			npc_manager_.Update(dt);

			// Graphic frame
			window_.clear();

			tilemap_ptr_->Draw(window_);
			building_manger.Draw(window_);
			npc_manager_.Draw(window_);

			btnBlue->Draw(window_);
			btnRed->Draw(window_);
			btnGreen->Draw(window_);
			btnExit->Draw(window_);
			window_.draw(text);
			ressource_ui.Draw(window_);

			window_.display();
		}
	}
}
}  // namespace game
