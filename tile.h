#ifndef _TILE_H
#define _TILE_H

#include <SFML/Graphics.hpp>
#include "gameObject.h"
using namespace sf;

class tile : public gameObject {
public:
	tile();
	tile(Vector2f gamePos);
	tile(Texture &t, Vector2f gamePosition = Vector2f());

	bool getBlank();
	void setBlank(bool blank);
	
	void setAnimation(int row, int column, int direction = 1);

private:
	bool isBlank;
};

tile::tile() {
	isBlank = true;
}

tile::tile(Vector2f gamePosition) {
	setGamePos(gamePosition);
	isBlank = true;
}

tile::tile(Texture &t, Vector2f gamePosition) {
	setTexture(t);
	setGamePos(gamePosition);
	isBlank = true;
}


bool tile::getBlank() {
	return isBlank;
}
void tile::setBlank(bool blank) {
	isBlank = blank;
}

void tile::setAnimation(int row, int column, int direction) {
	setAnimationRow(row);
	setAnimationColumn(column);
	if (direction != 0) {
		setDirection(direction);
	}
	setTextureRect(IntRect(88 - 8 * getDirection() + 16 * (column - 1), 113 + 16 * (row - 1), 16 * getDirection(), 16));
}

#endif