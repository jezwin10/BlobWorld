#ifndef LEVEL_H
#define LEVEL_H

#include "globals.h"
#include "tile.h"

#include <vector>
#include <string>

class Graphics;
struct SDL_Texture;
struct SDL_Rect;
struct Tileset;

class Level {
public:
	Level();
	Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);
	~Level();

	void update(int elapsedTime);
	void draw(Graphics &graphics);
private:
	std::string _mapName;
	Vector2 _spawnPoint;

	Vector2 _size;
	Vector2 _tileSize;

	SDL_Texture* _backgroundTexture;

	std::vector<Tile> _tileList;
	std::vector<Tileset> _tilesets;

	void loadMap(std::string mapName, Graphics &graphics);

};

//Tileset structure; public by default
struct Tileset {
	SDL_Texture* Texture;
	int FirstGid;
	Tileset() {
		FirstGid = -1;
	}

	Tileset(SDL_Texture* texture, int firstGid) {
		Texture = texture;
		FirstGid = firstGid;
	}
};

#endif
