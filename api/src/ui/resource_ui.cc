//
// Created by forna on 12.07.2025.
//
#include "ui/resource_ui.h"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Sensor.hpp>

#include "ressources/ressource.h"

void api::ui::Ressource_UI::SetText(std::string string, sf::Vector2f pos) {

	resource_text->setString(string);
	resource_text->setPosition(pos);
	//text_wood.setStyle(sf::Text::Bold);

}
void api::ui::Ressource_UI::Setup(sf::Font& font) {
resource_text=sf::Text(font);
	resource_text->setFillColor(sf::Color::Black);

}


void api::ui::Ressource_UI::Draw(sf::RenderWindow& window) {
	SetText("Wood : " + std::to_string(woods), {50,100});
	window.draw(*resource_text);
	SetText("Stone : " + std::to_string(stones), {50,150});
	window.draw(*resource_text);
	SetText("Food : " + std::to_string(foods), {50,200});
	window.draw(*resource_text);
}