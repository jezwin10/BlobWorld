/* Graphics Class
 * Holds all information regarding the graphics for the game
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

#include <map>
#include <string>



//Forward declaring these so that the variable names can be used as pointers even if they haven't been included yet
struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
	Graphics();
	~Graphics();

	/* SDL_Surface* loadImage
	 * Loads an image into the _spriteSheets map if it doesn't already exist
	 * It returns the image from the map whether it was just loaded or not
	 */
	SDL_Surface* loadImage(const std::string &filePath);

	/* blitSurface draws SDL_Textures to the screen
	 * source is what's being drawn to the screen, sourceRectangle is what part of the source is being drawn to the screen
	 * destinationRectangle is where on the screen it's being drawn
	 */
	void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

	// void flip() renders everything to the screen
	void flip();

	// void clear() clears the screen
	void clear();

	/* Every time something is going to be drawn to the screen, the renderer is first cleared out
	 * using blitSurface, whatever needs to be drawn, will be drawn into the renderer
	 * then void flip() will be draw what's in the renderer to the screen
	 */

	// This returns the renderer so that it can be used elsewhere
	SDL_Renderer* getRenderer() const;
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	std::map<std::string, SDL_Surface*> _spriteSheets;
	/* This _spriteSheets variable holds every sprite sheet that has been loaded into the game in the Graphics object
	 * This means that an image does not have to be loaded more than once, making it faster and more efficient
	 */


};

#endif
