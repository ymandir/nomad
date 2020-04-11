#include "Memory.h"



Memory::Memory()
{
	inconsolata.loadFromFile("Inconsolata-Bold.ttf");
	Header.setFont(inconsolata);
	Header.setCharacterSize(config.headerSize);
	Header.setPosition(5, 5);
	Header.setFillColor(config.headerColor);
	Header.setString("MEMORY");

	headerBackground.setFillColor(sf::Color(40, 40, 150, 255));
	headerBackground.setSize(sf::Vector2f(config.w, config.h / 30));

	selectionRect.setFillColor(sf::Color::Transparent);
	selectionRect.setSize(sf::Vector2f(config.w-4, config.h / 2 -4));
	selectionRect.setPosition(2,2);
	selectionRect.setOutlineThickness(2);
	selectionRect.setOutlineColor(sf::Color::White);

	hoverRect.setFillColor(sf::Color::Transparent);
	hoverRect.setSize(sf::Vector2f(config.w - 4, config.h / 2 - 4));
	hoverRect.setPosition(2, 2);
	hoverRect.setOutlineThickness(2);
	hoverRect.setOutlineColor(sf::Color(100, 100, 100, 255));

	target.create(config.w,config.h/2); 
	finalSprite.setTexture(target.getTexture());
	finalSprite.setPosition(0, config.h / 2);
}


Memory::~Memory()
{
}

sf::Sprite Memory::getSprite()
{
	return finalSprite;
}

void Memory::update(sf::Vector2i mousePos)
{
	if (mousePos.x > 0 && mousePos.x < config.w && mousePos.y > config.h / 2 && mousePos.y < config.h)
	{
		hover = true;
	}
	else 
	{
		hover = false;
	}

	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)&&hover)
	{
		selected = true;
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !hover)
	{
		selected = false;
	}

	target.clear();
	target.draw(headerBackground);
	target.draw(Header);
	drawLines();
	if (hover) { target.draw(hoverRect); }
	if (selected) { target.draw(selectionRect); }
	target.display();

}

void Memory::drawLines()
{
	for (int i = 0; i < state.verticalSize*3; i++)
	{
		drawHalfLine(i);
	}
}

void Memory::drawHalfLine(int index)
{
	int verticalSize = state.verticalSize;
	int posX = (config.w/3) * (index%3);
	int posY = (index/3 + 3) * config.itemSize + config.h / 30;

	sf::Color color1;
	sf::Color color2;

	color1 = sf::Color::Yellow;
	color2 = sf::Color(200, 200, 200, 255);

	sf::RectangleShape background;
	background.setPosition(posX, posY);
	background.setSize(sf::Vector2f(config.w/6, config.h / 40));
	background.setFillColor(color1);
	target.draw(background);

	sf::Text text;
	text.setFont(inconsolata);
	text.setCharacterSize(config.textSize);
	text.setPosition(posX + config.w / 60, posY);
	text.setFillColor(config.textColor);

	std::stringstream sstream;
	sstream << "0x" << std::hex << state.start + index * state.increment;
	text.setString(sstream.str());
	target.draw(text);

	background.setPosition(posX + config.w / 6, posY);
	background.setSize(sf::Vector2f(config.w / 6, config.h / 40));
	background.setFillColor(color2);
	target.draw(background);

	text.setPosition(posX + config.w / 6 + config.w / 60, posY);
	std::stringstream sstream2;
	std::stringstream sstream3;

	sstream2 << std::hex << state.startPtr[index];
	if (sstream2.str().size() < state.increment*2)
	{

		int zeroSpace = state.increment*2 - sstream2.str().size();
		for (int i = 0; i < zeroSpace; i++)
		{

			sstream3 << 0;
		}
	}
	sstream3 << sstream2.str().substr(0,state.increment*2);

	text.setString(sstream3.str());
	target.draw(text);
}

void Memory::setStart(void * ptr)
{
	state.start = (unsigned int)ptr;
	state.startPtr = (unsigned int*)ptr;
}

void Memory::updateEvents(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Up && selected &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		static sf::Clock lastPressed;
		if (lastPressed.getElapsedTime().asMilliseconds() > 100)
		{
			setStart(state.startPtr - 3);
			lastPressed.restart();
		}

	}

	else if (event.key.code == sf::Keyboard::Down && selected &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		static sf::Clock lastPressed;
		if (lastPressed.getElapsedTime().asMilliseconds() > 100)
		{
			setStart(state.startPtr + 3);
			lastPressed.restart();
		}

	}

}
