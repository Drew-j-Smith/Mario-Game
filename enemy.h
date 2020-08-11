#ifndef _ENEMY_H
#define _ENEMY_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "tilemap.h"
#include "character.h"
#include "gameObject.h"

using namespace sf;

class enemy : public gameObject {
public:
	enemy();
	enemy(Vector2f gamePos);
	enemy(Texture &t, Vector2f gamePos = Vector2f());

	void setAnimation(int row, int column, int direction = 0, int height = 16);
	void update(float cameraOffset, float deltat, tilemap &t, character &c, float gameTime);

	float getDeathTime();
	void setDeathTime(float deathTime);

	bool isIntersectingStomp(RectangleShape r);

private:
	float myDeathTime;
};

enemy::enemy() {
	setVelocity(Vector2f(150, 0));
	myDeathTime = 0;
}
enemy::enemy(Vector2f gamePos) {
	setGamePos(gamePos);

	setVelocity(Vector2f(150, 0));
	myDeathTime = 0;
}
enemy::enemy(Texture &t, Vector2f gamePos) {
	setTexture(t);
	setGamePos(gamePos);

	setVelocity(Vector2f(150, 0));
	myDeathTime = 0;
}



float enemy::getDeathTime() {
	return myDeathTime;
}
void enemy::setDeathTime(float deathTime) {
	myDeathTime = deathTime;
}


void enemy::update(float cameraOffset, float deltat, tilemap &t, character &c, float gameTime) {
	
	if (myDeathTime == 0) {
		movementUpdate(deltat, cameraOffset);
		if (t.isIntersecting(getHitbox())) {
			undoMovementUpdate(cameraOffset);
			setVelocity(Vector2f(-1 * getVelocity().x, getVelocity().y));
		}
		setGamePos(Vector2f(getGamePos().x, getGamePos().y + 1));
		if (getVelocity().x > 0) {
			if (!t.isIntersecting(Vector2f(getGamePos().x + getTextureRect().width * getScale().x, getGamePos().y + getTextureRect().height * getScale().y)))
				setVelocity(Vector2f(-1 * getVelocity().x, getVelocity().y));
			
		}
		else
		{
			if (!t.isIntersecting(Vector2f(getGamePos().x, getGamePos().y + getTextureRect().height * getScale().y)))
				setVelocity(Vector2f(-1 * getVelocity().x, getVelocity().y));
		}
		setGamePos(Vector2f(getGamePos().x, getGamePos().y - 1));

		if (isIntersectingStomp(c.getStompHitbox())
			&& c.getVelocity().y >= 0) {
			c.setVelocity(Vector2f(c.getVelocity().x, -300));
			c.playSound("SMB/Music/smb_kick.wav");
			myDeathTime = gameTime;
		}
		else if (isIntersecting(c.getHitbox()))
			c.setGameState(-1);
		
		setAnimation(1, int(gameTime * 2) % 2);
	}
	else {
		setAnimation(1, 2);
		if (gameTime - myDeathTime > 1) {
			myDeathTime = -1;
		}
	}
	setPosition(getGamePos().x - cameraOffset, getGamePos().y);

}

void enemy::setAnimation(int row, int column, int direction, int height) {
	setAnimationRow(row);
	setAnimationColumn(column);
	if (direction != 0) {
		setDirection(direction);
	}
	setTextureRect(IntRect(8 - 8 * getDirection() + 16 * column, 32 * (row - 1) + 32 - height, 16 * getDirection(), height));
}


bool enemy::isIntersectingStomp(RectangleShape r) {
	Vector2f p[4];
	p[0] = Vector2f(getGamePos().x, getGamePos().y);
	p[1] = Vector2f(getGamePos().x + abs(getTextureRect().width) * getScale().x, getGamePos().y);
	p[2] = Vector2f(getGamePos().x, getGamePos().y + abs(getTextureRect().height) * getScale().y - (getTextureRect().height - 8) * getScale().y);
	p[3] = Vector2f(getGamePos().x + abs(getTextureRect().width) * getScale().x, getGamePos().y + abs(getTextureRect().height) * getScale().y - (getTextureRect().height - 8) * getScale().y);
	int i;
	for (i = 0; i <= 3; i++) {
		if (r.getPosition().x <= p[i].x &&
			r.getPosition().x + abs(r.getSize().x) >= p[i].x &&
			r.getPosition().y <= p[i].y &&
			r.getPosition().y + abs(r.getSize().y) >= p[i].y)
			return true;
	}
	return false;
}



#endif