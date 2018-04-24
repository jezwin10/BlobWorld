/* Animated Sprite Class
 * Holds all the logic for animating sprites
 */
#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <map>
#include <string>
#include <vector>

#include "sprite.h"
#include "globals.h"

class Graphics;

class AnimatedSprite : public Sprite { // publicly inherits from the sprite class
public:
	AnimatedSprite();
	AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height, float posX, float posY, float timeToUpdate);
	// timeToUpdate is how long until you're supposed to go onto the next frame in the animation

	// void playAnimation() plays the animation provided its not already playing
	void playAnimation(std::string animation, bool once = false);
	/* bool once = false is an optional parameter
	 * Nothing has to be passed through it
	 * It determines whether the animation should only played once or if it should loop
	 */

	// void update() updates the animated sprite using a timer
	void update(int elapsedTime);

	// void draw() draws the sprite to the screen
	void draw(Graphics &graphics, int x, int y);

protected:
	double _timeToUpdate; // amount of time between frames
	bool _currentAnimationOnce; // check if an animation is only being played once
	std::string _currentAnimation; // name of the current animation that's being played

	// This function is  how you add animations to the list of animations for a sprite
	void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset); // (the number of frames in an animation, x and y coord of where on the sprite sheet the animation starts, the name of the animation and the width and height of the animation)

	// void resetAnimation() resets all animations associated with the sprite
	void resetAnimation();

	// void stopAnimation() stops the current animation
	void stopAnimation();

	// void setVisible() changes the visibility of the animated sprite
	void setVisible(bool visible);

	// virtual void animationDone() is logic that takes places when an animation ends
	virtual void animationDone(std::string currentAnimation) = 0;

	// void setupAnimation() is a required function that sets up all the animations for a sprite
	virtual void setupAnimations() = 0;
private:
	std::map<std::string, std::vector<SDL_Rect> > _animations; // This gives you a map full of animations so you can keep track of all the animations that a sprite has
	std::map<std::string, Vector2> _offsets;

	int _frameIndex; // Which frame in the animation you're at
	double _timeElapsed;
	bool _visible; // to check if the animation is visible
};

#endif
