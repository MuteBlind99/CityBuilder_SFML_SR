#include "gameplay/building.h"

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
//
// Created by forna on 11.07.2025.
//
api::gameplay::Building::Building(sf::Vector2f pos, sf::Texture& texture)
	: sprite_(texture) {
	pos_ = pos;
	sprite_->setPosition(pos_);

	// std::cout <<
}
void api::gameplay::Building::Draw(sf::RenderWindow& window) const {
	window.draw(*sprite_);
}