#include "level.h"
#include "graphics.h"
#include "globals.h"

#include "tinyxml2.h"

#include <SDL2/SDL.h>

#include <sstream>
#include <algorithm>
#include <cmath>

using namespace tinyxml2;

// Use for troubleshooting

#include <iostream>
using namespace std;


Level::Level() {

}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics) :
		_mapName(mapName),
		_spawnPoint(spawnPoint),
		_size(Vector2(0,0))
{
	loadMap(mapName, graphics);
}

Level::~Level() {

}

void Level::loadMap(std::string mapName, Graphics &graphics) {
	// Parse the .tmx file
	//This part finds and opens the map document
	XMLDocument doc;
	std::stringstream ss;
	ss << "maps/" << mapName << ".tmx"; // Pass in Map1, it returns maps/Map 1.tmx
	doc.LoadFile(ss.str().c_str()); // converting a string stream to a string then converting it into a c string
	// cout << mapName; returns Map 1

	//Parsing the file
	XMLElement* mapNode = doc.FirstChildElement("map"); // Getting the <map> element from Map1.tmx

	// Get the width and height of the whole map from the <map> element and store it in the _size variable
	int width, height;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	_size = Vector2(width, height);
	/*
	cout << width; returns 20
	cout << height; returns 16
	*/

	// Get the width and height of the tiles and store it in _tileSize var
	int tileWidth, tileHeight;
	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	_tileSize = Vector2(tileWidth, tileHeight);
	/*
	cout << tileWidth; returns 16
	cout << tileHeight; returns 16
	*/

	// Loading the tileset
	XMLElement* pTileset = mapNode->FirstChildElement("tileset"); // Gets the first element called <tileset>
	if (pTileset != NULL) { // This if loop checks if there are no tileset
		while (pTileset) { // If there is a tileset present, then perform this loop
			int firstgid;
			const char* source = pTileset->FirstChildElement("image")->Attribute("source");
			std::string path = source;
			// char* path;
			// std::stringstream ss;
			// ss << source;
			pTileset->QueryIntAttribute("firstgid", &firstgid);
			SDL_Texture* tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(path)); // Texture loaded
			_tilesets.push_back(Tileset(tex, firstgid));

			pTileset = pTileset->NextSiblingElement("tileset"); // If there isn't more than one tileset, then it moves on to the next part of the code
			// At this point, the tilesets should be all loaded
			cout << path;
		} // end while (pTileset)
	} // end if (pTileset != NULL)

	//Loading <layer> element
	XMLElement* pLayer = mapNode->FirstChildElement("layer");
	if (pLayer != NULL ) {
		while (pLayer) {
			// Loading <data> element
			XMLElement* pData = pLayer->FirstChildElement("data");
			if (pData != NULL) {
				while (pData) {
					// Loading <tile> element
					XMLElement* pTile = pData->FirstChildElement("tile");
					if (pTile != NULL) {
						int tileCounter = 0;
						while (pTile) {
							// Build each individiual tile  here
							// If gid = 0, no tile should be draw, loop continues
							if (pTile->IntAttribute("gid") == 0) { // if this statement is true, then no tile should be drawn
								tileCounter++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								} // if (pTile->NextSiblingElement("tile"))
								else {
									break;
								} // else break
							} // if (pTile->IntAttribute("gid") == 0)

							// Get the tileset for this specific gid
							int gid = pTile->IntAttribute("gid");
							Tileset tls;
							for (int i = 0; i < _tilesets.size(); i++) {
								if (_tilesets[i].FirstGid <= gid) {
									// This is the tileset thats needed
									tls = _tilesets.at(i);
									break;
								}
							}

							if (tls.FirstGid == -1) {
								//No tileset was found for this gid
								tileCounter++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else {
									break;
								} // else break
							}
							// Get the position of the tile in the level
							int xx = 0;
							int yy = 0;
							xx = tileCounter % width;
							xx *= tileWidth;

							yy += tileHeight * (tileCounter / width);
							Vector2 finalTilePosition = Vector2(xx, yy);

							// Calculate the position of the tile in the tileset
							int tilesetWidth, tilesetHeight;
							SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight); // Querying the tileset texture to get its width and height

							int tsxx = gid % (tilesetWidth / tileWidth) - 1; // tilesetWidth = 256, tileWidth = 16
							tsxx *= tileWidth;

							int tsyy = 0;
							int amt = (gid / (tilesetWidth / tileWidth));
							tsyy = tileHeight * amt;
							Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);

							// Build the tile and add it to the level's tile list
							Tile tile(tls.Texture, Vector2(tileWidth, tileHeight), finalTilesetPosition, finalTilePosition);
							_tileList.push_back(tile);
							tileCounter++;

							pTile = pTile->NextSiblingElement("tile");
						} // while (pTile)
					} // if (pTile != NULL)

					pData = pData->NextSiblingElement("data");
				} // while (pData)
			} // if (pData != NULL)

			pLayer = pLayer->NextSiblingElement("layer");
		} // while (pLayer)
	} // if (pLayer != NULL)
}

void Level::update(int elapsedTime) {

}

void Level::draw(Graphics &graphics) {
	for (int i = 0; i < _tileList.size(); i++ ) {
		_tileList.at(i).draw(graphics);
	}
	/*
	SDL_Rect sourceRect = { 0, 0, 64, 64 };
	SDL_Rect destRect;
	for (int x = 0; x < _size.x / 64; x++) {
		for (int y = 0; y < _size.y / 64; y++) {
			destRect.x = x * 64 * globals::SPRITE_SCALE;
			destRect.y = y * 64 * globals::SPRITE_SCALE;
			destRect.w = 64 * globals::SPRITE_SCALE;
			destRect.h = 64 * globals::SPRITE_SCALE;
			graphics.blitSurface(_backgroundTexture, &sourceRect, &destRect);
		}
	}
	*/
}
