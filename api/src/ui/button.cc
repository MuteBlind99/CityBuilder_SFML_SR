//
// Created by sebas on 25/06/2025.
//

#include "ui/button.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

namespace api::ui {

Button::Button(sf::Vector2f pos, std::string_view label, const sf::Texture &t,
const sf::Texture &hover_t, const sf::Font &font): Clickable(),
spriteButton_(t),
hoverSprite_(hover_t),
label_(font),
spriteCost_(t),
labelCost_(font) {
	sf::Vector2i int_size = {
		static_cast<int>(spriteButton_.getTexture().getSize().x),
		static_cast<int>(spriteButton_.getTexture().getSize().y*2)};
	sf::Vector2i int_pos = {static_cast<int>(pos.x), static_cast<int>(pos.y)};
	spriteButton_.setPosition(pos);
	spriteButton_.setScale(sf::Vector2f(3.f, 3.f));
	spriteCost_.setPosition({pos.x + spriteButton_.getTexture().getSize().x / 2.f,
						pos.y + spriteButton_.getTexture().getSize().y / 2.f});
	spriteCost_.setScale(sf::Vector2f(2.f, 2.f));
	spriteCost_.setColor(sf::Color(0,0,0,0));
	hoverSprite_.setPosition(pos);

	label_.setCharacterSize(20);
	label_.setString(std::string(label));
	sf::FloatRect textRect = label_.getLocalBounds();
	label_.setOrigin(label_.getLocalBounds().getCenter());
	label_.setPosition({pos.x + hoverSprite_.getTexture().getSize().x / 2.f,
						pos.y + hoverSprite_.getTexture().getSize().y / 2.f});

	Button::SetZone(sf::IntRect(int_pos, int_size));
	OnHoverEnter = [this]() {

		onButton = true;
		spriteButton_.setScale(sf::Vector2f(3.f, 3.f));
		spriteButton_.setColor(sf::Color(0, 0, 0, 0));
		hoverSprite_.setScale(sf::Vector2f(3.f, 3.f));
		hoverSprite_.setColor(sf::Color(100, 255, 100, 255));
		label_.setFillColor(sf::Color::Black);
	};
	OnHoverExit = [this]() {
		onButton = false;
		spriteButton_.setScale(sf::Vector2f(3.f, 3.f));
		spriteButton_.setColor(sf::Color(100, 255, 255, 255));
		hoverSprite_.setScale(sf::Vector2f(2.f, 2.f));
		hoverSprite_.setColor(sf::Color(0, 0, 0, 0));
		label_.setFillColor(sf::Color::White);
	};

	spriteButton_.setColor(sf::Color(255, 255, 255, 255));
	hoverSprite_.setColor(sf::Color(0, 0, 0, 0));
}

Button::Button(const sf::Vector2f pos, std::string_view label,
			   const sf::Texture &t1,const sf::Texture &t2, const sf::Texture &hover_t,
			   const sf::Font &font)
	: Clickable(),
	  spriteButton_(t1),
	  hoverSprite_(hover_t),
	  label_(font),
	  spriteCost_(t2),
	  labelCost_(font) {
	sf::Vector2i int_size = {
		static_cast<int>(spriteButton_.getTexture().getSize().x),
		static_cast<int>(spriteButton_.getTexture().getSize().y*2)};
	sf::Vector2i int_pos = {static_cast<int>(pos.x), static_cast<int>(pos.y)};

	std::cout << "Texture size : " << int_size.x << ":" << int_size.y << "\n";

	spriteButton_.setPosition(pos);
	spriteButton_.setScale(sf::Vector2f(1.f, 2.f));
	spriteCost_.setPosition({pos.x + spriteButton_.getTexture().getSize().x / 2.f-40,
						pos.y + spriteButton_.getTexture().getSize().y / 2.f});
	spriteCost_.setScale(sf::Vector2f(4.f, 4.f));
	hoverSprite_.setPosition(pos);

	label_.setCharacterSize(20);
	label_.setString(std::string(label));
	sf::FloatRect textRect = label_.getLocalBounds();
	//label_.setOrigin(label_.getLocalBounds().getCenter());
	label_.setPosition({pos.x + hoverSprite_.getTexture().getSize().x / 2.f,
						pos.y + hoverSprite_.getTexture().getSize().y / 2.f});

	Button::SetZone(sf::IntRect(int_pos, int_size));

	OnHoverEnter = [this]() {
		onButton = true;
		spriteButton_.setScale(sf::Vector2f(2.f, 2.f));
		spriteButton_.setColor(sf::Color(0, 0, 0, 0));
		hoverSprite_.setScale(sf::Vector2f(3.f, 3.f));
		hoverSprite_.setColor(sf::Color(100, 255, 100, 255));
		label_.setFillColor(sf::Color::Black);
	};
	OnHoverExit = [this]() {
		onButton = false;
		spriteButton_.setScale(sf::Vector2f(1.f, 2.f));
		spriteButton_.setColor(sf::Color(255, 100, 255, 255));
		hoverSprite_.setScale(sf::Vector2f(2.f, 2.f));
		hoverSprite_.setColor(sf::Color(0, 0, 0, 0));
		label_.setFillColor(sf::Color::White);
	};

	spriteButton_.setColor(sf::Color(255, 255, 255, 255));
	hoverSprite_.setColor(sf::Color(0, 0, 0, 0));
}

void Button::Draw(sf::RenderWindow &window) const {



	if (onButton) {
		window.draw(hoverSprite_);
		window.draw(label_);
	} else {
		window.draw(spriteButton_);
		window.draw(spriteCost_);
	}
}
}  // namespace api::ui
