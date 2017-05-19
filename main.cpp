#include <iostream>
#include <SFML/Graphics.hpp>

#include "Chip-8.h"

using namespace sf;

int main()
{
	while (true)
	{

		Clock clock;

		RectangleShape rectangle;
		rectangle.setSize(Vector2f(10, 10));

		Chip8 chip8;

		string Path;
		sf::Int64 time;
		float heroteleporttimer = 0;

		cout << "input path to game, input q to exit: " << endl;
		getline(cin, Path);
		if (Path == "q")
			return 0;
		if (!chip8.loadGame(Path))
			continue;
	
		RenderWindow window(VideoMode(640, 320), "CHip-8 emul");

		while (window.isOpen())
		{
			time = clock.getElapsedTime().asMicroseconds(); 
			heroteleporttimer += time;

			Event event;
			while (window.pollEvent(event))
			{
				if (event.key.code == Keyboard::Escape)
				{
					window.clear();
					window.close();
				}

				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == Event::KeyPressed)
					chip8.PressedKey = chip8.KeyboardDict[event.key.code];

				if (event.type == Event::KeyReleased)
					chip8.PressedKey = 0x10;
			}

			if (heroteleporttimer > 200) {
				chip8.emulateCycle();
				heroteleporttimer = 0; 
			
				window.clear();

				if (chip8.drawFlag)
					for (size_t i = 0; i < 64 * 32; i++)
						if (chip8.display[i])
						{
							rectangle.setPosition((((int)i % 64) * 10), ((std::floor(i / 64)) * 10));
							window.draw(rectangle);
						}

				window.display();
			}
			clock.restart();
			time = time / 800;
		}
	}
	return 0;
}
