#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include "gameObject.h"
using namespace sf;

class character : public gameObject {
public:
	character();
	character(Vector2f gamePos);
	character(Texture &t, Vector2f gamePosition = Vector2f());

	bool getTouchingGround();
	void setTouchingGround(bool touching);

	void setAnimation(int row, int column, int direction = 0);
	int getRowOffset(int row);

	void update(Keyboard input, float deltat, float &cameraOffset, Music &m, float gameTime);
	void undoUpdate(float &cameraOffset);

	void playSound(std::string filename, bool looping = false);

	RectangleShape getStompHitbox();

private:
	SoundBuffer myBuffer;
	Sound mySound;
	bool isTouchingGround;
};

character::character() {
	setGravity(1100);
	setScale(3, 3);
	isTouchingGround = false;
	setWalkAcc(400);
	setMaxWalkSpd(200);
	setRunAcc(600);
	setMaxRunSpd(400);
	setStopAcc(200);
	setAnimation(2, 1);
	mySound.setBuffer(myBuffer);
	mySound.setAttenuation(0);
}

character::character(Vector2f gamePosition) {
	setGamePos(gamePosition);

	setGravity(1100);
	setScale(3, 3);
	isTouchingGround = false;
	setWalkAcc(400);
	setMaxWalkSpd(200);
	setRunAcc(600);
	setMaxRunSpd(400);
	setStopAcc(200);
	setAnimation(2, 1);
	mySound.setBuffer(myBuffer);
	mySound.setAttenuation(0);
}

character::character(Texture &t, Vector2f gamePosition) {
	setTexture(t);
	setGamePos(gamePosition);

	setGravity(1100);
	setScale(3, 3);
	isTouchingGround = false;
	setWalkAcc(400);
	setMaxWalkSpd(200);
	setRunAcc(600);
	setMaxRunSpd(400);
	setStopAcc(200);
	setAnimation(2, 1);
	mySound.setBuffer(myBuffer);
	mySound.setAttenuation(0);
}


//
//sets and gets
//
bool character::getTouchingGround() {
	return isTouchingGround;
}
void character::setTouchingGround(bool touching) {
	isTouchingGround = touching;
}




void character::setAnimation(int row, int column, int direction) {
	setAnimationRow(row);
	setAnimationColumn(column);
	if (direction != 0) {
		setDirection(direction);
	}
	if (row % 2 == 1) {

		setTextureRect(IntRect(88 - 8 * getDirection() + 17 * column, 64 * (row - 1) / 2 + getRowOffset(row), 16 * getDirection(), 32));
	}
	else {
		setTextureRect(IntRect(88 - 8 * getDirection() + 17 * column, 64 * (row - 1) / 2 + getRowOffset(row) + 1, 16 * getDirection(), 16));
	}
}
int character::getRowOffset(int row) {
	switch (row)
	{
	case 1:
	case 2:
		return 1;
	default:
		return 3 - (row - 1) / 2;
	}
}

void character::playSound(std::string filename, bool looping) {
	if (!myBuffer.loadFromFile(filename))
		std::cout << "Could not load file";
	mySound.setLoop(looping);
	mySound.play();
}


void character::update(Keyboard input, float deltat, float &cameraOffset, Music &m, float gameTime) {
	/*
	deltat is the number of seconds from the last update
	*/
	gameObject::movementUpdateType updateType = none;
	if (getGameState() >= 0) {
		if (input.isKeyPressed(Keyboard::Right) && !input.isKeyPressed(Keyboard::Left)) {
			if (input.isKeyPressed(Keyboard::LShift) || input.isKeyPressed(Keyboard::RShift)) {
				updateType = forwardRun;
			}
			else {
				updateType = forwardWalk;
			}
		}
		if (input.isKeyPressed(Keyboard::Left) && !input.isKeyPressed(Keyboard::Right)) {
			if (input.isKeyPressed(Keyboard::LShift) || input.isKeyPressed(Keyboard::RShift)) {
				updateType = backwardRun;
			}
			else {
				updateType = backwardWalk;
			}
		}
		if (input.isKeyPressed(Keyboard::Space)) {
			if (isTouchingGround && getVelocity().y == 0) {
				isTouchingGround = false;
				setVelocity(Vector2f(getVelocity().x, float(-1 * sqrt(pow(700, 2) + pow(getVelocity().x, 2)))));

				if (!myBuffer.loadFromFile("SMB/Music/smb_jump-small.wav"))
					std::cout << "Could not load file";
				mySound.setLoop(false);
				mySound.play();
			}
		}


		if (getGamePos().x > 500) {
			cameraOffset = getGamePos().x - 500;
		}
		else {
			cameraOffset = 0;
		}

		if (getGamePos().y > 768)
			setGameState(-1);


		movementUpdate(deltat, cameraOffset, updateType);

		if (getVelocity().x > 0) {
			setDirection(1);
		}
		else if (getVelocity().x < 0) {
			setDirection(-1);
		}

		if (getGamePos().x < 0){
			setGamePos(Vector2f(0, getGamePos().y));
			setVelocity(Vector2f(0, getVelocity().y));
		}


		if (isTouchingGround == false) {
			setAnimation(1, 5);
		}
		else if (getVelocity().x == 0) {
			setAnimation(1, 0);
			mySound.setLoop(false);
		}
		else if (getVelocity().x < 0 && input.isKeyPressed(Keyboard::Right)) {
			setAnimation(1, 4);
			if (mySound.getStatus() != sf::Sound::Playing) {
				if (!myBuffer.loadFromFile("SMB/Music/Super Mario Bros 1 and 2(JP)/Skid.wav"))
					std::cout << "Could not load file";
				mySound.play();
				mySound.setLoop(true);
			}
		}
		else if (getVelocity().x > 0 && input.isKeyPressed(Keyboard::Left)) {
			setAnimation(1, 4);
			if (mySound.getStatus() != sf::Sound::Playing) {
				if (!myBuffer.loadFromFile("SMB/Music/Super Mario Bros 1 and 2(JP)/Skid.wav"))
					std::cout << "Could not load file";
				mySound.play();
				mySound.setLoop(true);
			}
		}
		else if (getVelocity().x != 0) {
			setAnimation(1, int(gameTime * 6) % 3 + 1);
			mySound.setLoop(false);
		}


	}
	else if (getGameState() == -1){
		setVelocity(Vector2f(0, -500));
		setGravity(getGravity() / 2);
		movementUpdate(deltat, cameraOffset, gameObject::dontUpdate);
		setAnimation(2, 6, 1);

		if (!m.openFromFile("SMB/Music/08-you-re-dead.wav"))
			std::cout << "Could not load file";
		m.play();
		m.setLoop(false);
		mySound.stop();

		setGameState(-2);
	}
	else if(getGameState() == -2) {
		movementUpdate(deltat, cameraOffset, gameObject::dontUpdate);
	}
}

void character::undoUpdate(float &cameraOffset) {
	undoMovementUpdate(cameraOffset);
	if (getGamePos().x > 500) {
		cameraOffset = getGamePos().x - 500;
	}
	else {
		cameraOffset = 0;
	}
}

RectangleShape character::getStompHitbox() {
	RectangleShape r;
	r.setPosition(Vector2f(getGamePos().x, getGamePos().y + (getTextureRect().height - 8) * getScale().y));
	r.setSize(Vector2f(abs(getTextureRect().width) * getScale().x, 8 * getScale().y));
	return r;
}


#endif