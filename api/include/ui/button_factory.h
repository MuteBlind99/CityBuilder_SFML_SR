//
// Created by sebas on 25/06/2025.
//

#ifndef BUTTON_FACTORY_H
#define BUTTON_FACTORY_H

#include <SFML/Graphics/Font.hpp>
#include <array>
#include <string_view>

#include "assets/asset_manager.h"
#include "button.h"

namespace api::ui {
class ButtonFactory {
	enum class Sprite {
		kEmpty,
		kBgBtn,
		kHoverBtn,
		kWoodBtn,
		kMinerBtn,
		kHarvestBtn,
		kExitBtn,
		kLength
	};

	std::array<std::string_view, static_cast<size_t>(Sprite::kLength)> files_ =
		{"empty.png",	 "button_grey.png", "button_brown.png",
		 "Button_WoodCutter.png", "Button_Miner.png", "Button_Harvester.png","ExitBtn.PNG"};

	sf::Font font;
	core::experimental::AssetManager<sf::Texture, Sprite, "_assets/sprites">
		texturesButton_;
	core::experimental::AssetManager<sf::Texture, Sprite, "_assets/sprites">
		textures_;

   public:
	ButtonFactory() {
		texturesButton_.Load(files_);
		if (!font.openFromFile("_assets/fonts/Pixel Digivolve.otf")) {
			std::cout << "Failed to load font" << std::endl;
		}
		textures_.Load(files_);
	}

	std::unique_ptr<Button> CreateButton(sf::Vector2f pos,
										 std::string_view label) {
		if (label == "Woodcut: 10x Woods") {
			return std::move(std::make_unique<api::ui::Button>(
				pos, label,

				texturesButton_.Get(Sprite::kBgBtn),textures_.Get(Sprite::kWoodBtn),
				texturesButton_.Get(Sprite::kHoverBtn),font));
		} else if (label == "Minners: 10x Stones") {
			return std::move(std::make_unique<api::ui::Button>(
				pos, label,

				texturesButton_.Get(Sprite::kBgBtn),textures_.Get(Sprite::kMinerBtn),
				texturesButton_.Get(Sprite::kHoverBtn), font));
		} else if (label == "Harvest: 5x Woods \n   5x Stones ") {
			return std::move(std::make_unique<api::ui::Button>(
				pos, label,

				texturesButton_.Get(Sprite::kBgBtn),textures_.Get(Sprite::kHarvestBtn),
				texturesButton_.Get(Sprite::kHoverBtn), font));
		} else {
			return std::move(std::make_unique<api::ui::Button>(
				pos, label,

				texturesButton_.Get(Sprite::kExitBtn), textures_.Get(Sprite::kHoverBtn),
				font));
		}
		// return std::move(std::make_unique<api::ui::Button>(
		// 	pos, label,
		//
		// 	textures_.Get(Sprite::kBgBtn), textures_.Get(Sprite::kHoverBtn),
		// 	font));
	}
};
}  // namespace api::ui

#endif	// BUTTON_FACTORY_H
