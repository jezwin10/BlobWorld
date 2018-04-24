#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"
#include "animatedsprite.h"

class Graphics;

class Player : public AnimatedSprite {
public:
	Player();
	Player(Graphics &graphics, float x, float y);
	void draw(Graphics &graphics);
	void update(float elapsedTime);

	void moveLeft(); // moves the player left by -_dx
	void moveRight(); // moves the player right by _dx
	void stopMoving(); // stops the player moving

	virtual void animationDone(std::string currentAnimation);
	virtual void setupAnimations();
private:
	float _dx, _dy;

	Direction _facing;

};

#endif
