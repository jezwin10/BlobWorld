/* AnimatedSprite Class
 * Used to animate the sprites
 */

#include "animatedsprite.h"
#include "graphics.h"

AnimatedSprite::AnimatedSprite() {

}

AnimatedSprite::AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY,
		int width, int height, float posX, float posY, float timeToUpdate) :
				Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY),
				_frameIndex(0),
				_timeToUpdate(timeToUpdate),
				_visible(true),
				_currentAnimationOnce(false),
				_currentAnimation("")
{}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset) {
	std::vector<SDL_Rect> rectangles;
	for (int i = 0; i < frames; i++) { // i goes from 0 to 2 from 3 frames per animation
		SDL_Rect newRect = { (i + x) * width, y, width, height}; // (i + x) * width grabs which ever sprite corresponds to x.
		rectangles.push_back(newRect);
	}
	_animations.insert(std::pair<std::string, std::vector<SDL_Rect> >(name, rectangles));
	_offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

// This function clears the maps of both animations and offsets
void AnimatedSprite::resetAnimation() {
	_animations.clear();
	_offsets.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once) {
	_currentAnimationOnce = once;
	// Check if the animation that is trying to play is already playing
	if (_currentAnimation != animation) {
		_currentAnimation = animation;
		_frameIndex = 0;
	}
}

void AnimatedSprite::setVisible(bool visible) {
	_visible = visible;
}

void AnimatedSprite::stopAnimation() {
	_frameIndex = 0;
	animationDone(_currentAnimation);
}

// This function has a timer that checks when to go the next frame in the animation
void AnimatedSprite::update(int elapsedTime) {
	Sprite::update();
	// adding onto the timer every new frame
	_timeElapsed += elapsedTime;
	// if timeElapsed > _timeToUpdate then its time to change frames
	if (_timeElapsed > _timeToUpdate) {
		_timeElapsed -= _timeToUpdate;
		if (_frameIndex < _animations[_currentAnimation].size() -1) { // if frameIndex is not at the last one in the animation, then increase frameIndex by 1
			_frameIndex++;
		}
		else {
			if (_currentAnimationOnce == true) { // if you are on the last one however, then stop, sending it back to the start
				setVisible(false);
			}
			_frameIndex = 0;
			animationDone(_currentAnimation);
		} // end else {}
	} // end if() statement
} //end function

void AnimatedSprite::draw(Graphics &graphics, int x, int y) {
	if (_visible) { // if its visible, then create a temporary destinationRectangle which is where it'll be drawn
		SDL_Rect destinationRectangle;
		destinationRectangle.x = x + _offsets[_currentAnimation].x;
		destinationRectangle.y = y + _offsets[_currentAnimation].y;
		destinationRectangle.w = _sourceRect.w * globals::SPRITE_SCALE;
		destinationRectangle.h = _sourceRect.h * globals::SPRITE_SCALE;

		SDL_Rect sourceRect = _animations[_currentAnimation][_frameIndex]; // get the correct rectangle to draw by using what's passed into _currentAnimation and _frameIndex
		// the map is indexed using _animations[_currentAnimation] to get the correct vector and _frameIndex then indexes the vector to get the correct rectangle from the vector itself
		graphics.blitSurface(_spriteSheet, &sourceRect, &destinationRectangle);
	}
}
