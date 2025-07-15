//
// Created by forna on 10.07.2025.
//

#ifndef RESOURCE_UI_H
#define RESOURCE_UI_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "ressources/ressource.h"
namespace api::ui {
class Ressource_UI {
public:

	void Draw(sf::RenderWindow& window);
	void Setup(sf::Font& font);


	int woods = 10;
	int stones = 12;
	int foods = 5;
private:
	std::optional<sf::Text>resource_text;

	void SetText(std::string, sf::Vector2f);


	// Text(const sf::Font &font, sf::String string = "",
	// 	 unsigned int characterSize = 30) {
	// 	// Open a font
	//
	// }
};
}
#endif	// RESOURCE_UI_H
