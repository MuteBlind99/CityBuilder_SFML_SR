
#ifndef API_GRAPHICS_TILEMAP_H
#define API_GRAPHICS_TILEMAP_H

#include <SFML/Graphics.hpp>

#include "assets/asset_manager.h"
#include "ressources/ressource.h"
#include "ressources/ressource_manager.h"
#include "ui/clickable.h"

constexpr int kWidth = 1280;
constexpr int kHeight = 800;
constexpr int kPixelStep = 16;


class TileMap : public api::ui::Clickable {

public:
	enum class Tile {
		kEmpty, kBg, kWater,
		kRock, kTree, kFood,
		kGrass,kLength
	};

private:
	std::array<std::string_view, static_cast<size_t>(TileMap::Tile::kLength)> files_ = {
		"empty.png", "Shore.png", "water.png",
		"Rocks_Shore.png", "Trees_bg.png","Cactus_Shore.png" ,"grass.png"
	};

    std::array<Tile, kWidth / kPixelStep * kHeight / kPixelStep> tiles_ = {};
    core::experimental::AssetManager<sf::Texture, Tile, "_assets/sprites"> textures_;

    std::vector<sf::Vector2f> walkables_;

    static int Index(sf::Vector2f screenPosition);
	ResourceManager ressource_;

public:
	static sf::Vector2f ScreenPosition(int index);
	static sf::Vector2f TilePos(sf::Vector2i);
	static int GetStep(){return kPixelStep;};

    void Setup();
    void Draw(sf::RenderWindow &window);
	void SetTile(int, Tile);
	Tile GetTile(int idx) const;

	std::vector<sf::Vector2f> &GetWalkables();
    std::vector<int> GetCollectibles(Tile);

};
#endif
