#ifndef _ENEMYMAP_H
#define _ENEMYMAP_H

#include <SFML/Graphics.hpp>
#include "enemy.h"
using namespace sf;


class enemymap {
public:
	enemymap();
	enemymap(std::string filename, Texture &t);

	void setTexture(Texture &t);
	const Texture *getTexture();
	void loadFromFile(std::string filename);

	void update(float cameraOffset, float deltat, tilemap &t, character &c, float gameTime);
	void draw(RenderWindow &window, float cameraOffset);

private:
	enemy arrEnemies[100];
};

enemymap::enemymap() {
	int i;
	for (i = 1; i < 100; i++) {
		arrEnemies[i].setDeathTime(-1);
		arrEnemies[i].setScale(3, 3);
	}
}

enemymap::enemymap(std::string filename, Texture &t) {
	setTexture(t);
	loadFromFile(filename);
}

void enemymap::setTexture(Texture &t) {
	int i;
	for (i = 1; i < 100; i++) {
		arrEnemies[i].setTexture(t);
	}
}




const Texture *enemymap::getTexture() {
	return arrEnemies[0].getTexture();
}
void enemymap::loadFromFile(std::string filename) {
	std::ifstream infile;
	infile.open(filename, std::ios::in);
	char tileString[501];
	int i1 = 0, i2;
	int numEnemies = 0;

	for (i1 = 1; i1 < 100; i1++) {
		arrEnemies[i1].setDeathTime(-1);
		arrEnemies[i1].setScale(3, 3);
	}


	i1 = 0;
	if (infile) {
		while (!infile.eof()) {
			if (i1 < 16) {
				infile.getline(tileString, 501, '\n');

				for (i2 = 0; tileString[i2] != '\0'; i2++) {

					numEnemies++;
					if (tileString[i2] == 'd') {
						arrEnemies[numEnemies].setDeathTime(0);
						arrEnemies[numEnemies].setGamePos(Vector2f(i2 * 48.f, i1 * 48.f - 1.f));
					}
					else {
						numEnemies--;
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

void enemymap::update(float cameraOffset, float deltat, tilemap &t, character &c, float gameTime) {
	int i;
	for (i = 0; i < 100; i++) {
		if (arrEnemies[i].getDeathTime() != -1)
			arrEnemies[i].update(cameraOffset, deltat, t, c, gameTime);
	}
}

void enemymap::draw(RenderWindow &window, float cameraOffset) {
	int i;
	for (i = 0; i < 100; i++) {
		if (arrEnemies[i].getDeathTime() != -1 && arrEnemies[i].getPosition().x >= -48 && arrEnemies[i].getPosition().x <= window.getSize().x)
			window.draw(arrEnemies[i]);
	}
}

#endif