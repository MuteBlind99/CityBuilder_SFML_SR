//
// Created by sebas on 15/05/2025.
//
#include "graphics/tilemap.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <random>

#include "noise/FastNoiseLite.h"
#include "ressources/ressource.h"

static std::mt19937 gen{std::random_device{}()};
static std::uniform_real_distribution dist(0.f, 1.f);
auto tilemap_ptr_ = std::make_unique<TileMap>();



void TileMap::Setup(){
	textures_.Load(files_);
	walkables_.clear();
	FastNoiseLite fast_noise;
	fast_noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

	//Random (seed)
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(8.0f, 20.f);
	const int scale_x = uniform_dist(e1);
	std::default_random_engine e2(r());
	std::uniform_int_distribution<int> uniform_dist2(8.f, 20.f);
	const int scale_y = uniform_dist2(e2);

	int index = 0;
	std::vector<int>vec_index;


    // Remplir le tableau avec de l'herbe ou de l'eau de manière aléatoire
	for (int y = 0; y < kHeight / kPixelStep; y++) {
		for (int x = 0; x < kWidth / kPixelStep; x++) {
			const float noise_value = fast_noise.GetNoise(static_cast<float>(x * scale_x),
														  static_cast<float>(y * scale_y));
			const float noise_value_d = fast_noise.GetNoise(static_cast<float>(x * scale_x),
															static_cast<float>(y * scale_y));
			int last_raw_index = kPixelStep * y;

			if (noise_value > 0.2f) {
				if (noise_value > 0.45f) {
					if (noise_value > 0.5f) {
						tiles_[index] = Tile::kRock;
						walkables_.push_back(sf::Vector2f(x * kPixelStep, y * kPixelStep));
						//const auto stone_ressources=ressource_.GetRessources(Ressource::Type::kStone);
					} else {
						tiles_[index] = Tile::kTree;
						//const auto wood_ressources=ressource_.GetRessources(Ressource::Type::kWood);
						walkables_.push_back(sf::Vector2f(x * kPixelStep, y * kPixelStep));
					}
				} else {

					if (noise_value_d > 0.25f) {
						tiles_[index] = Tile::kTree;
						//const auto wood_ressources=ressource_.GetRessources(Ressource::Type::kWood);
						walkables_.push_back(sf::Vector2f(x * kPixelStep, y * kPixelStep));
					} else {
						tiles_[index] = Tile::kGrass;
						walkables_.push_back(sf::Vector2f(x * kPixelStep, y * kPixelStep));
					}

				}
			} else {
				if (noise_value > 0.1f) {
					if (noise_value_d>0.15f) {
						tiles_[index] = Tile::kFood;

						walkables_.push_back(sf::Vector2f(x * kPixelStep, y * kPixelStep));
					}
					else {
						tiles_[index] = Tile::kGrass;
						walkables_.push_back(sf::Vector2f(x * kPixelStep, y * kPixelStep));
					}
				} else {
					tiles_[index] = Tile::kBg;
					walkables_.push_back(sf::Vector2f(x * kPixelStep, y * kPixelStep));
				}
			}
			index++;
		}
	}


	SetZone(sf::IntRect
		({0, 0}
		 ,
		 sf::Vector2i(kWidth, kHeight)
		)
	);
}

void TileMap::Draw(sf::RenderWindow &window){
    int tileIndex = 0;

    sf::Sprite sprite(textures_.Get(Tile::kEmpty));

    sprite.setTextureRect(sf::IntRect({0, 0}, {kPixelStep, kPixelStep}));

    for (auto tile: tiles_) {
        sprite.setTexture(textures_.Get(tile));
        sprite.setPosition(ScreenPosition(tileIndex));
        window.draw(sprite);

        tileIndex++;
    }
}

void TileMap::SetTile(int idx, Tile tile) {
	if (idx > 0 && idx < tiles_.size()) {
		tiles_[idx] = tile;
	}
}

TileMap::Tile TileMap::GetTile(int idx) const {
	if (idx > 0 && idx < tiles_.size()) {
		return tiles_[idx];
	}
	return Tile::kEmpty;
}

std::vector<sf::Vector2f> &TileMap::GetWalkables(){ return walkables_; }

std::vector<int> TileMap::GetCollectibles(Tile search_tile){

    std::vector<int> collectibles;

    for (int tile_index = 0; tile_index < tiles_.size(); ++tile_index) {
        if (tiles_[tile_index] == search_tile) {
            collectibles.emplace_back(tile_index);
        }
    }

    return collectibles;

}

sf::Vector2f TileMap::ScreenPosition(const int index){
    float x = ceil((index % (kWidth / kPixelStep)) * kPixelStep);
    float y = ceil((index / (kWidth / kPixelStep)) * kPixelStep);

    // std::cout << "Calculated Screen Position : " << x << "." << y << "\n";

    return {x, y};
}

int TileMap::Index(const sf::Vector2f screenPosition){
    return static_cast<int>(ceil(screenPosition.y / kPixelStep * kWidth)) +
           static_cast<int>(ceil(screenPosition.x / kPixelStep));
}

sf::Vector2f TileMap::TilePos(sf::Vector2i pos){
    return {
        static_cast<float>(round(pos.x / kPixelStep) * kPixelStep),
        static_cast<float>(round(pos.y / kPixelStep) * kPixelStep)
    };
}
