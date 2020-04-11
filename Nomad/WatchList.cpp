#include "WatchList.h"



WatchList::WatchList()
{
	inconsolata.loadFromFile("Inconsolata-Bold.ttf");
	Header.setFont(inconsolata);
	Header.setCharacterSize(config.headerSize);
	Header.setPosition(5, 5);
	Header.setFillColor(config.headerColor);
	Header.setString("WATCH LIST");

	headerBackground.setFillColor(sf::Color(40,40,150,255));
	headerBackground.setSize(sf::Vector2f(config.w,config.h/30));

	selectionRect.setFillColor(sf::Color::Transparent);
	selectionRect.setSize(sf::Vector2f(config.w - 4, config.h / 2 - 4));
	selectionRect.setPosition(2, 2);
	selectionRect.setOutlineThickness(2);
	selectionRect.setOutlineColor(sf::Color::White);

	hoverRect.setFillColor(sf::Color::Transparent);
	hoverRect.setSize(sf::Vector2f(config.w - 4, config.h / 2 - 4));
	hoverRect.setPosition(2, 2);
	hoverRect.setOutlineThickness(2);
	hoverRect.setOutlineColor(sf::Color(100,100,100,255));

	target.create(config.w,config.h/2);
	finalSprite.setTexture(target.getTexture());
	
}


WatchList::~WatchList()
{


}

sf::Sprite WatchList::getSprite()
{
	return finalSprite;
}

void WatchList::add(int* item, std::string name)
{
	watchItem newItem;
	newItem.address = item;
	newItem.byteSize = sizeof(item);
	newItem.value = std::to_string(*item);
	newItem.name = name;
	newItem.type = "int";
	items.push_back(newItem);
}

void WatchList::add(float* item, std::string name)
{
	watchItem newItem;
	newItem.address = item;
	newItem.byteSize = sizeof(item);
	newItem.value = std::to_string(*item);
	newItem.name = name;
	newItem.type = "float";
	items.push_back(newItem);
}



void WatchList::drawItem(watchItem item, int itemIndex)
{

	int index = itemIndex - shift;

	int posX = 0;
	int posY = (index+1) * config.itemSize + config.h / 30;

	

	sf::Color color1;
	sf::Color color2;
	sf::Color color3;

	color1 = sf::Color::Yellow;
	color3 = sf::Color(130, 130, 130,255);
	color2 = sf::Color(100, 100, 100, 255);


	sf::RectangleShape background;
	background.setPosition(posX,posY);
	background.setSize(sf::Vector2f(config.w,config.h/40));
	background.setFillColor(sf::Color(200,200,200,255));
	target.draw(background);




	//ADDRESS
	background.setPosition(posX, posY);
	background.setSize(sf::Vector2f(config.w/5, config.h / 40));
	background.setFillColor(sf::Color(color2));
	target.draw(background);

	sf::Text text;
	text.setFont(inconsolata);
	text.setCharacterSize(config.textSize);
	text.setPosition(posX + config.w / 20, posY);
	text.setFillColor(config.textColor);
	std::stringstream sstream;
	sstream << "0x" << std::hex << (int)item.address;
	text.setString(sstream.str());
	target.draw(text);


	//ID
	background.setSize(sf::Vector2f((config.w / 30), config.h / 40));
	background.setFillColor(color1);
	target.draw(background);

	text.setPosition(posX + (config.w / 100),posY);
	text.setString(std::to_string(itemIndex));
	target.draw(text);

	//NAME
	background.setSize(sf::Vector2f((config.w / 5), config.h / 40));
	background.setPosition(sf::Vector2f(posX + (config.w / 5), posY));
	background.setFillColor(color3);
	target.draw(background);

	text.setPosition(posX + (config.w / 5) + (config.w / 40), posY);
	text.setString(item.name);
	target.draw(text);

	//BYTESIZE
	background.setSize(sf::Vector2f((config.w / 5), config.h / 40));
	background.setPosition(sf::Vector2f(posX + (config.w / 5)*2, posY));
	background.setFillColor(color2);
	target.draw(background);

	text.setPosition(posX + (config.w / 5)*2 + (config.w / 40), posY);
	text.setString(std::to_string(item.byteSize));
	target.draw(text);
	
	//ARRAYSIZE
	background.setSize(sf::Vector2f((config.w / 5), config.h / 40));
	background.setPosition(sf::Vector2f(posX + (config.w / 5) * 3, posY));
	background.setFillColor(color3);
	target.draw(background);

	text.setPosition(posX + (config.w / 5) * 3 + (config.w / 40), posY);
	text.setString(std::to_string(item.arraySize));
	target.draw(text);

	//VALUE
	background.setSize(sf::Vector2f((config.w / 5), config.h / 40));
	background.setPosition(sf::Vector2f(posX + (config.w / 5) * 4, posY));
	background.setFillColor(color2);
	target.draw(background);

	text.setPosition(posX + (config.w / 5) * 4 + (config.w / 40), posY);
	text.setString(item.value);
	target.draw(text);


	background.setPosition(posX, posY);
	background.setSize(sf::Vector2f(config.w, config.h / 40));
	background.setFillColor(sf::Color::Transparent);
	background.setOutlineColor(sf::Color::Black);
	background.setOutlineThickness(2);
	target.draw(background);

	if (item.changed)
	{
		sf::RectangleShape background;
		background.setPosition(posX, posY);
		background.setSize(sf::Vector2f(config.w, config.h / 40));
		background.setFillColor(sf::Color(255, 255, 0, 150));
		target.draw(background);
	}

	if (hoverIndex == index&&hoverValid)
	{
		sf::RectangleShape hoverRect;
		hoverRect.setPosition(posX, posY+1);
		hoverRect.setSize(sf::Vector2f(config.w, config.h / 40 - 5));
		hoverRect.setFillColor(sf::Color(200, 200, 200, 0));
		hoverRect.setOutlineThickness(2);
		hoverRect.setOutlineColor(sf::Color::White);
		target.draw(hoverRect);
	}

	if (selectedIndex == index)
	{
		sf::RectangleShape hoverRect;
		hoverRect.setPosition(posX, posY+1);
		hoverRect.setSize(sf::Vector2f(config.w, config.h / 40 - 5));
		hoverRect.setFillColor(sf::Color(200, 200, 200, 0));
		hoverRect.setOutlineThickness(2);
		hoverRect.setOutlineColor(sf::Color::Yellow);
		target.draw(hoverRect);
	}


}

void WatchList::drawItems()
{
	int index = 0;
	for (watchItem item : items)
	{
		if (index - shift >= 0)
		{
			drawItem(item, index);
		}
		index++;
	}
}

void WatchList::drawItemHeader()
{
	int posX = 0;
	int posY = config.h / 30;

	sf::Color color1;
	sf::Color color2;

	color1 = sf::Color(200,200,200,255);
	color2 = sf::Color(150, 150, 150, 255);



	sf::RectangleShape background;
	background.setPosition(0, posY);
	background.setSize(sf::Vector2f(config.w, config.h / 40));
	background.setFillColor(color1);
	target.draw(background);

	//ADDRESS
	background.setPosition(posX, posY);
	background.setSize(sf::Vector2f(config.w / 5, config.h / 40));
	background.setFillColor(color2);
	target.draw(background);

	sf::Text text;
	text.setFont(inconsolata);
	text.setCharacterSize(config.textSize);
	text.setPosition(posX + config.w / 20, posY);
	text.setFillColor(config.headerColor);
	text.setFillColor(config.textColor);
	text.setString("ADDRESS");
	target.draw(text);


	//ID
	background.setSize(sf::Vector2f((config.w / 30), config.h / 40));
	background.setFillColor(color1);
	target.draw(background);

	text.setPosition(posX + (config.w / 200), posY);
	text.setString("ID");
	target.draw(text);


	//NAME
	background.setSize(sf::Vector2f((config.w / 5), config.h / 40));
	background.setPosition(sf::Vector2f(posX + (config.w / 5), posY));
	background.setFillColor(color1);
	target.draw(background);

	text.setPosition((config.w / 5) + (config.w / 40), posY);
	text.setString("NAME");
	target.draw(text);

	//BYTESIZE
	background.setSize(sf::Vector2f((config.w / 5), config.h / 40));
	background.setPosition(sf::Vector2f(posX + (config.w / 5) * 2, posY));
	background.setFillColor(color2);
	target.draw(background);

	text.setPosition(posX + (config.w / 5) * 2 + (config.w / 40), posY);
	text.setString("BYTE SIZE");
	target.draw(text);

	//ARRAYSIZE
	background.setSize(sf::Vector2f((config.w / 5), config.h / 40));
	background.setPosition(sf::Vector2f(posX + (config.w / 5) * 3, posY));
	background.setFillColor(color1);
	target.draw(background);

	text.setPosition((config.w / 5) * 3 + (config.w / 40), posY);
	text.setString("ARRAY SIZE");
	target.draw(text);

	//VALUE
	background.setSize(sf::Vector2f((config.w / 5), config.h / 40));
	background.setPosition(sf::Vector2f(posX + (config.w / 5) * 4, posY));
	background.setFillColor(color2);
	target.draw(background);

	text.setPosition(posX + (config.w / 5) * 4 + (config.w / 40), posY);
	text.setString("VALUE");
	target.draw(text);


}



void WatchList::updateItems()
{
	int index = 0;
	for (watchItem& item : items)
	{
		if (item.type == "int")
		{
			if(std::to_string(*(int*)(item.address))!=item.value)
			{
				item.value = std::to_string(*(int*)(item.address));
				item.changed = 1;
				item.lastChanged.restart();
			}
			else 
			{
				if (item.lastChanged.getElapsedTime().asMilliseconds() > 500)
				{
					item.changed = 0;
				}
			}
		}
	}
}

void WatchList::update(sf::Vector2i mousePos)
{



	updateHover(mousePos);
	updateItems();

	target.clear();
	target.draw(headerBackground);
	target.draw(Header);
	drawItemHeader();
	drawItems();
	if (windowHover) { target.draw(hoverRect); }
	if (selected) { target.draw(selectionRect); }
	target.display();
}




void WatchList::updateHover(sf::Vector2i mousePos)
{
	//ITEM HOVER
	if (selected)
	{
		hoverIndex = (mousePos.y - config.h / 20) / (config.h / 40);
	}

	if (hoverIndex >= items.size()|| mousePos.x < 0 || mousePos.x > config.w) 
	{ 
		hoverValid = false; 
	}
	else { hoverValid = true; }

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)&&hoverValid&&windowHover)
	{
		selectedIndex = hoverIndex;
		selectionChanged = true;
		selectedAdress = items.at(selectedIndex).address;
	}

	//WATCHLIST WINDOW HOVER
	if (mousePos.x > 0 && mousePos.x < config.w && mousePos.y > 0  && mousePos.y < config.h / 2)
	{
		windowHover = true;
	}
	else
	{
		windowHover = false;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && windowHover)
	{
		selected = true;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !windowHover)
	{
		selected = false;
	}
}


void WatchList::updateEvents(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Down && selected && 
		!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		static sf::Clock lastPressed;
		if (lastPressed.getElapsedTime().asMilliseconds() > 100)
		{
			if (shift < items.size() - 1) 
			{ 
				shift++; 
				selectedIndex--; 
			}
			lastPressed.restart();
		}

	}

	else if (event.key.code == sf::Keyboard::Up && selected)
	{
		static sf::Clock lastPressed;
		if (lastPressed.getElapsedTime().asMilliseconds() > 100)
		{
			if (shift > 0) 
			{ 
				shift--; 
				selectedIndex++; 
			}
			lastPressed.restart();
		}

	}
}