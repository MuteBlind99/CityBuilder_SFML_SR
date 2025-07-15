//
// Created by forna on 11.07.2025.
//

#ifndef BUILDING_H
#define BUILDING_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
namespace api::gameplay {
class Building {
	std::optional<sf::Sprite> sprite_;
	sf::Vector2f pos_;

   public:
	Building(sf::Vector2f pos, sf::Texture &texture);
	void Draw(sf::RenderWindow &window) const;

};
}  // namespace api::gameplay

#endif	// BUILDING_H
