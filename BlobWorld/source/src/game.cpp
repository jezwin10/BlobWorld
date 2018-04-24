/* Game Class
 * Holds all the information for the main gameLoop
 */

#include <SDL2/SDL.h>

#include "game.h"
#include "graphics.h"
#include "input.h"

namespace {
	 const int FPS = 50;
	 const int MAX_FRAME_TIME = 5 * 1000 / FPS; // MAX_FRAME_TIME is the maximum amount of time that is allowed for a frame
}

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	gameLoop();
}

Game::~Game() {

}

/* gameLoop
 * This function occurs every frame
 */
void Game::gameLoop() {
	Graphics graphics;
	Input input;
	SDL_Event event; // The SDL_Event object holds whatever event happens during the current frame

	_player = Player(graphics, 100, 100);
	_level = Level("Map 1", Vector2(100,100), graphics);

	int LAST_UPDATE_TIME = SDL_GetTicks(); // Gets the number of milliseconds since the SDL Library was initialised (SDL_Init)

	// Start of game loop
	// SDL checks for all events in this loop and if something happens, it gets stored in the event variable
	while (true) {
		input.beginNewFrame(); // Calling this function resets the pressed and released keys

		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0) { // This statement makes sure that you're not holding a key down
					input.keyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP) {
				input.keyUpEvent(event);
			}
			else if (event.type == SDL_QUIT) {
				return;
			}
		} // end if(SDL_PollEvent) statement

		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
			return;
		} //  end if(input.wasKeyPressed()) statement
		else if (input.isKeyHeld(SDL_SCANCODE_A) == true) {
			_player.moveLeft();
		}
		else if (input.isKeyHeld(SDL_SCANCODE_D) == true) {
			_player.moveRight();
		}
		if (!input.isKeyHeld(SDL_SCANCODE_A) && !input.isKeyHeld(SDL_SCANCODE_D)) {
			_player.stopMoving();
		}

		const int CURRENT_TIME_MS = SDL_GetTicks(); // Current time will be however long it took to go through the while() loop
		int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME; //ELAPSED_TIME_MS is how long the current frame took
		update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
		/* If the while() loop took less than the MAX_FRAME_TIME (maximum amount of time frame is allowed) then that time will be used
		 * If it took more than MAX_FRAME_TIME, then MAX_FRAME_TIME will be used, meaning it will be limited and cannot go higher than 50FPS
		 * All in-game physics will be based off of MAX_FRAME_TIME so that it is consistent across all PCs of varying performance
		 * i.e. All movement regardless of computer is speed will be the same
		 */
		LAST_UPDATE_TIME = CURRENT_TIME_MS;

		draw(graphics);
	} // end while() loop
} // end gameLoop

void Game::draw(Graphics &graphics) {
	graphics.clear(); // Clear whatever is in the renderer at the moment

	_level.draw(graphics);
	_player.draw(graphics); // Draws MainChar at location x and y determined by AnimatedSprite

	graphics.flip(); // draw to screen
}

void Game::update(float elapsedTime) {
	_player.update(elapsedTime);
	_level.update(elapsedTime);
}
