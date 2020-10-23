// Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "character.h"
#include "tilemap.h"
#include "tile.h"
#include "enemy.h"
#include "enemymap.h"

using namespace sf;



int main()
{
	char ans;
	do {
		RenderWindow window(VideoMode(1200, 768), "Game");
		Clock gameTime;
		float dt, previousTime = 0, cameraOffset = 0;

		Texture charMap;
		charMap.loadFromFile("SMB/Pics/SMBCharacters.png");
		character mario(charMap, Vector2f(48 * 3, 48 * 11 - 1));

		Texture tileMap;
		tileMap.loadFromFile("SMB/Pics/SMBFullTileset.png");
		tilemap map("SMB/Levels/1-1.txt", tileMap);

		Texture enemyMap;
		enemyMap.loadFromFile("SMB/Pics/SMBEnemies.png");

		enemymap enMap("SMB/Levels/1-1.txt", enemyMap);

		Music music;
		music.openFromFile("SMB/Music/01-main-theme-overworld.wav");
		music.play();
		music.setLoop(true);
		

		while (window.isOpen()) {
			window.clear(Color(98, 148, 252));

			dt = gameTime.getElapsedTime().asSeconds() - previousTime;
			previousTime = gameTime.getElapsedTime().asSeconds();
			if (dt > .15)
				dt = float(.15);
			
			mario.update(Keyboard(), dt, cameraOffset, music, gameTime.getElapsedTime().asSeconds());
			if (mario.getGameState() >= 0) {
				map.update(mario, cameraOffset);
				enMap.update(cameraOffset, dt, map, mario, gameTime.getElapsedTime().asSeconds());
			}
			
			map.draw(window, cameraOffset);
			window.draw(mario);
			enMap.draw(window, cameraOffset);

			Event e;
			window.pollEvent(e);
			switch (e.type) {
			case Event::Closed:
				window.close();
				break;
			}
			

			window.display();
		}
		std::cout << "Run Again? (Y/N)";
		std::cin >> ans;
	} while (ans == 'y' || ans == 'Y');
	return 0;
}
