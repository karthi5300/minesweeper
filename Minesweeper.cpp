// Minesweeper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <SFML/Graphics.hpp>
#include <time.h>

int main()
{
	srand(time(0)); //to input new seed

	sf::RenderWindow app(sf::VideoMode(480, 480), "Minesweeper Game"); //480 is used because the tiles.img is 480 x 40

	int w = 40; //width of each tile
	int backGrid[12][12]; //1 and 12 will not be used
	int frontGrid[12][12];

	sf::Texture texture;
	texture.loadFromFile("images/tiles.jpg");

	sf::Sprite sprite(texture);

	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			frontGrid[i][j] = 10;// populating frontGrid with hiding tile

			
			if (rand() % 5 == 0)
				backGrid[i][j] = 9; //populating backGrid with bombs
			else
				backGrid[i][j] = 0; //populating backGrid with empty slot
		}
	}

	//calculating the numbers to be printed if a bomb is present in backGrid
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			int n = 0;
			if (backGrid[i][j] == 9) continue;

			if (backGrid[i + 1][j] == 9) n++;
			if (backGrid[i][j + 1] == 9) n++;
			if (backGrid[i - 1][j] == 9) n++;
			if (backGrid[i][j - 1] == 9) n++;

			if (backGrid[i + 1][j + 1] == 9) n++;
			if (backGrid[i + 1][j - 1] == 9) n++;
			if (backGrid[i - 1][j + 1] == 9) n++;
			if (backGrid[i - 1][j - 1] == 9) n++;

			backGrid[i][j] = n;
		}
	}

	while (app.isOpen()) {

		sf::Vector2i pos = sf::Mouse::getPosition(app);
		int x = pos.x / w;
		int y = pos.y / w;

		sf::Event e;

		//to handle events
		while (app.pollEvent(e)) {
			if (e.type == sf::Event::Closed) {
				app.close();
			}
			else if (e.type == sf::Event::MouseButtonPressed) {
				if (e.key.code == sf::Mouse::Left)
					frontGrid[x][y] = backGrid[x][y];
				else if (e.key.code == sf::Mouse::Right)
					frontGrid[x][y] = 11;
			}
		}

		app.clear(sf::Color::Color(96,96,96,0));

		for (int i = 1; i <= 10; i++)
			for (int j = 1; j <= 10; j++) {

				//checking if we clicked on bomb
				if(frontGrid[x][y] == 9)
					frontGrid[i][j] = backGrid[i][j];

				sprite.setTextureRect(sf::IntRect(frontGrid[i][j] * w, 0, w, w));
				sprite.setPosition(i * w, j * w);
				app.draw(sprite);
			}

		app.display();
	}
}