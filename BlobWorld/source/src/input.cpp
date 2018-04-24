/* Input class
 * Keeps track of the state the keyboard is in
 */

#include "input.h"

// This function gets called at the beginning of every new frame to reset the keys that are no longer relevant
void Input::beginNewFrame() {
	_pressedKeys.clear();
	_releasedKeys.clear();
}

// This function is called when a key has been pressed
void Input::keyDownEvent(const SDL_Event& event) {
	_pressedKeys[event.key.keysym.scancode] = true;
	_heldKeys[event.key.keysym.scancode] = true;
}

// This function is called when a key is released
void Input::keyUpEvent(const SDL_Event& event) {
	_releasedKeys[event.key.keysym.scancode] = true;
	_heldKeys[event.key.keysym.scancode] = false; // This event is false because it was already set true by keyDownEvent, so now its set to false because it has been released
}

// This checks if a certain key was pressed during the current frame
bool Input::wasKeyPressed(SDL_Scancode key) {
	return _pressedKeys[key];
}

bool Input::wasKeyReleased(SDL_Scancode key) {
	return _releasedKeys[key];
}

// This function tells us if a key is currently being held
bool Input::isKeyHeld(SDL_Scancode key) {
	return _heldKeys[key];
}
