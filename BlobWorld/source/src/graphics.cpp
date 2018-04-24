/* Graphics Class
 * Holds all information regarding the graphics for the game
 */
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#include "graphics.h"
#include "globals.h"


Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0, &_window, &_renderer); //Parameters include window width and height, flags used to create the window, window pointer and renderer pointer
	SDL_SetWindowTitle(_window, "BlobWorld"); //Sets the title in the title bar
}

Graphics::~Graphics() {
	SDL_DestroyWindow(_window); // Destructor used to close the window
	SDL_DestroyRenderer(_renderer); // This prevents memory leaks
}

SDL_Surface* Graphics::loadImage(const std::string &filePath) {
	if (_spriteSheets.count(filePath) == 0) { // If this statement is true, then the spriteSheet hasn't been loaded yet
		_spriteSheets[filePath] = IMG_Load(filePath.c_str());
	}
	return _spriteSheets[filePath];
}

void Graphics::blitSurface(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle) {
	SDL_RenderCopy(_renderer, texture, sourceRectangle, destinationRectangle);  // This function copies whatever you pass into it, to the renderer
}

void Graphics::flip() {
	SDL_RenderPresent(_renderer);
}

void Graphics::clear() {
	SDL_RenderClear(_renderer);
}

SDL_Renderer* Graphics::getRenderer() const {
	return _renderer;
}
