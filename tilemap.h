#ifndef _TILEMAP_H
#define _TILEMAP_H

#include "tile.h"
#include "character.h"
#include <string>
#include <fstream>
#include <cmath>
using namespace sf;

class tilemap {
public:
	tilemap();
	tilemap(std::string filename, Texture &t);

	void setTexture(Texture &t);
	const Texture *getTexture();
	void loadFromFile(std::string filename);

	bool isIntersecting(RectangleShape r);
	bool isIntersecting(Vector2f gamePos);

	void update(character &c, float &cameraOffset);
	void draw(RenderWindow &window, float cameraOffset);

private:
	tile myArrTiles[2200];

};


tilemap::tilemap() {
	int i;
	for (i = 0; i < 2200; i++) {
			myArrTiles[i].setScale(3, 3);
	}
}

tilemap::tilemap(std::string filename, Texture &t) {
	setTexture(t);
	loadFromFile(filename);
}


void tilemap::loadFromFile(std::string filename) {
	std::ifstream infile;
	infile.open(filename, std::ios::in);
	char tileString[501];
	int i1, i2;


	for (i1 = 0; i1 < 2200; i1++) {
			myArrTiles[i1].setBlank(true);
			myArrTiles[i1].setScale(3, 3);
	}

	int numTiles = 0;
	i1 = 0;
	if (infile) {
		while (!infile.eof()) {
			if (i1 < 16) {
				infile.getline(tileString, 501, '\n');
				
				for (i2 = 0; tileString[i2] != '\0'; i2++) {
					numTiles++;
					if (tileString[i2] == 'a') {
						myArrTiles[numTiles].setAnimation(1, 24);
						myArrTiles[numTiles].setGamePos(Vector2f(i2 * 48.f, i1 * 48.f));
						myArrTiles[numTiles].setBlank(false);
					}
					else if (tileString[i2] == 'b') {
						myArrTiles[numTiles].setAnimation(2, 24);
						myArrTiles[numTiles].setGamePos(Vector2f(i2 * 48.f, i1 * 48.f));
						myArrTiles[numTiles].setBlank(false);
					}
					else if (tileString[i2] == 'c') {
						myArrTiles[numTiles].setAnimation(1, 25);
						myArrTiles[numTiles].setGamePos(Vector2f(i2 * 48.f, i1 * 48.f));
						myArrTiles[numTiles].setBlank(false);
					}
					else if (tileString[i2] == 'e') {
						myArrTiles[numTiles].setAnimation(9, 24);
						myArrTiles[numTiles].setGamePos(Vector2f(i2 * 48.f, i1 * 48.f));
						myArrTiles[numTiles].setBlank(false);
					}
					else if (tileString[i2] == 'f') {
						myArrTiles[numTiles].setAnimation(9, 25);
						myArrTiles[numTiles].setGamePos(Vector2f(i2 * 48.f, i1 * 48.f));
						myArrTiles[numTiles].setBlank(false);
					}
					else if (tileString[i2] == 'g') {
						myArrTiles[numTiles].setAnimation(10, 24);
						myArrTiles[numTiles].setGamePos(Vector2f(i2 * 48.f, i1 * 48.f));
						myArrTiles[numTiles].setBlank(false);
					}
					else if (tileString[i2] == 'h') {
						myArrTiles[numTiles].setAnimation(10, 25);
						myArrTiles[numTiles].setGamePos(Vector2f(i2 * 48.f, i1 * 48.f));
						myArrTiles[numTiles].setBlank(false);
					}
					else {
						numTiles--;
					}

				}

				i1++;
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		std::cout << "Error opening file.\n";
	}
	infile.close();
}


void tilemap::setTexture(Texture &t) {
	int i;
	for (i = 0; i < 2200; i++) {
			myArrTiles[i].setTexture(t);
	}
}
const Texture *tilemap::getTexture() {
	return myArrTiles[0].getTexture();
}


bool tilemap::isIntersecting(RectangleShape r) {
	int i;
	for (i = 0; i < 2200; i++) {
			if (!myArrTiles[i].getBlank() && myArrTiles[i].isIntersecting(r))
				return true;
	}
	return false;
}
bool tilemap::isIntersecting(Vector2f gamePos) {
	int i;
	for (i = 0; i < 2200; i++) {
			if (!myArrTiles[i].getBlank() && myArrTiles[i].isIntersecting(gamePos))
				return true;
	}
	return false;
}


void tilemap::update(character &c, float &cameraOffset) {
	int i;
	for (i = 0; i < 2200; i++) {
		if (!myArrTiles[i].getBlank())
			myArrTiles[i].setPosition(myArrTiles[i].getGamePos().x - cameraOffset, myArrTiles[i].getGamePos().y);
	}

	if (isIntersecting(c.getHitbox())) {
		c.undoUpdate(cameraOffset);
		Vector2f pos = c.getGamePos();

		c.setGamePos(Vector2f(pos.x + c.getVelocity().x * c.getDt(), pos.y));
		if (isIntersecting(c.getHitbox())) {
			c.setGamePos(Vector2f(pos.x, pos.y + c.getVelocity().y * c.getDt()));
			if (!isIntersecting(c.getHitbox()))
				c.setVelocity(Vector2f(0, c.getVelocity().y + c.getGravity() * c.getDt()));
			else {
				c.setVelocity(Vector2f(0, 0));
				c.setGamePos(pos);
				c.setTouchingGround(true);
			}
			if (isIntersecting(c.getHitbox())) {
				c.setGamePos(Vector2f(pos.x, pos.y - 1));
			}
		}
		else {
			c.setGamePos(Vector2f(pos.x, pos.y + c.getVelocity().y * c.getDt()));
			if (isIntersecting(c.getHitbox())) {
				if (c.getVelocity().y > 0) {
					c.setTouchingGround(true);
				}
				c.setGamePos(Vector2f(pos.x + c.getVelocity().x * c.getDt(), pos.y));
				c.setVelocity(Vector2f(c.getVelocity().x, 0));
			}
			else
				c.setGamePos(pos);
		}

		c.setPosition(c.getGamePos().x - cameraOffset, c.getGamePos().y);
	}
}

void tilemap::draw(RenderWindow &window, float cameraOffset) {
	int i;
	for (i = 0; i < 2200; i++) {
			if (!myArrTiles[i].getBlank() && myArrTiles[i].getPosition().x >= -48 && myArrTiles[i].getPosition().x <= window.getSize().x)
				window.draw(myArrTiles[i]);
	}
}



#endif
