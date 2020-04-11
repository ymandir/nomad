#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>
#include <vector>

class Memory
{
public:
	struct memoryConfig
	{
		int w = 1920 / 2;
		int h = 1080;
		int headerSize = 20;
		sf::Color headerColor = sf::Color::White;

		int textSize = 20;
		sf::Color textColor = sf::Color::Black;

		//VERTICAL SIZE OF ITEM
		int itemSize = h / 40;


	}config;

	struct memoryState
	{
		bool valid = 0;

		unsigned int start;
		unsigned int* startPtr;
		int increment = 4;
		int verticalSize = 15;

	}state;


	

	Memory();
	~Memory();
	sf::Sprite getSprite();

	void update(sf::Vector2i mousePos);

	void setStart(void* ptr);
	void updateEvents(sf::Event event);
	

	bool selected = false;
	bool hover = false;

private:
	void drawLines();
	void drawHalfLine(int index);

	sf::RenderTexture target;
	sf::Sprite finalSprite;
	sf::RectangleShape headerBackground;
	sf::RectangleShape selectionRect;
	sf::RectangleShape hoverRect;


	sf::Font inconsolata;
	sf::Text Header;

};

