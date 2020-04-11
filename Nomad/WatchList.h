#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <sstream>

class WatchList
{

	struct watchItem
	{
		std::string name;
		void* address = 0;
		int byteSize = 0;
		int arraySize = 1;
		std::string value = "0";
		std::string type;

		bool changed = 0;
		sf::Clock lastChanged;
	};


public:

	struct watchListConfig
	{
		int w = 1920/2;
		int h = 1080;
		int headerSize = 20;
		sf::Color headerColor = sf::Color::White;

		int textSize = 20;
		sf::Color textColor = sf::Color::Black;

		//VERTICAL SIZE OF ITEM
		int itemSize = h/40;

	}config;

	WatchList();
	~WatchList();
	sf::Sprite getSprite();

	void add(int* item, std::string name);
	void add(float* item, std::string name);


	void addArray(int* item, int size);

	void updateItems();
	void update(sf::Vector2i mousePos);
	void updateEvents(sf::Event event);

	bool selectionChanged = false;
	void* selectedAdress;

	bool selected = false;
	bool windowHover = false;

	int shift = 0;
	
private:

	std::vector<watchItem> items;

	void drawItem(watchItem item, int index);
	void drawItems();
	void drawItemHeader();

	sf::Font inconsolata;
	sf::Text Header;
	sf::RectangleShape headerBackground;
	sf::RenderTexture target;
	sf::Sprite finalSprite;

	sf::RectangleShape selectionRect;
	sf::RectangleShape hoverRect;

	void updateHover(sf::Vector2i mousePos);
	int hoverIndex = 0;
	int selectedIndex = 0;
	bool hoverValid = false;

};

