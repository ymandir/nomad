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

	checkConfigSpaceHover(mousePos);
	checkConfigSpaceSelection();
	
	updateState();

	target.clear();
	target.draw(headerBackground);
	target.draw(Header);
	drawConfigSpace();
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

	if (state.addressBase == 16)	
	{
		sstream << "0x" << std::hex << state.start + index * state.increment;
	}
	else if (state.addressBase == 10)
	{
		sstream <<  state.start + index * state.increment;
	}

	text.setString(sstream.str());
	target.draw(text);

	background.setPosition(posX + config.w / 6, posY);
	background.setSize(sf::Vector2f(config.w / 6, config.h / 40));
	background.setFillColor(color2);
	target.draw(background);

	text.setPosition(posX + config.w / 6 + config.w / 60, posY);
	std::stringstream sstream2;
	std::stringstream sstream3;

	if (state.valueBase == 16)
	{
		sstream2 << std::hex << state.startPtr[index];
	}
	else if (state.valueBase == 10)
	{
		sstream2 <<  state.startPtr[index];
	}

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

void Memory::drawConfigSpace()
{

	int posY = headerBackground.getSize().y;
	int posX = 0;

	int sizeX = config.w;
	int sizeY =  3 * config.itemSize + config.h / 30;

	sf::Color color(150, 150, 150, 255);

	sf::RectangleShape configSpaceRect;
	configSpaceRect.setPosition(posX,posY);
	configSpaceRect.setSize(sf::Vector2f(sizeX,sizeY));
	configSpaceRect.setFillColor(color);
	target.draw(configSpaceRect);

	//CLEAR CONFIGSPACE VECTORS
	configSpace.addressBaseOptions.clear();
	configSpace.valueBaseOptions.clear();
	//CLEAR CONFIGSPACE VECTORS

	//VALUE BASE
	sf::Text text;
	text.setFont(inconsolata);
	text.setCharacterSize(15);
	text.setFillColor(sf::Color::White);
	text.setPosition(posX+10,posY+10);
	text.setString("VALUE BASE");
	target.draw(text);

	//VALUE BASE OPTIONS
	text.setPosition(posX + 10, posY + 25);
	text.setString("10");
	configSpace.valueBaseOptions.push_back(text);
	if (configSpace.valueBaseSelectedIndex == 0) {target.draw(getTextRect(text));}
	target.draw(text);

	text.setPosition(posX + 10, posY + 40);
	text.setString("16");
	configSpace.valueBaseOptions.push_back(text);
	if (configSpace.valueBaseSelectedIndex == 1) { target.draw(getTextRect(text)); }
	target.draw(text);

	//ADDRESS BASE
	text.setFont(inconsolata);
	text.setCharacterSize(15);
	text.setFillColor(sf::Color::White);
	text.setPosition(posX + config.w/10 + 10, posY + 10);
	text.setString("ADDRESS BASE");
	target.draw(text);

	//VALUE BASE OPTIONS
	text.setPosition(posX + config.w/10 + 10, posY + 25);
	text.setString("10");
	configSpace.addressBaseOptions.push_back(text);
	if (configSpace.addressBaseSelectedIndex == 0) { target.draw(getTextRect(text)); }
	target.draw(text);

	text.setPosition(posX + config.w/10 + 10, posY + 40);
	text.setString("16");
	configSpace.addressBaseOptions.push_back(text);
	if (configSpace.addressBaseSelectedIndex == 1) { target.draw(getTextRect(text)); }
	target.draw(text);


}


inline sf::RectangleShape Memory::getTextRect(sf::Text text)
{
	sf::RectangleShape selectedRect;

	int selectedRectWidth = text.getCharacterSize()*text.getString().getSize();
	int selectedRectHeight = text.getCharacterSize();
	int selectedRectPosX = text.getPosition().x;
	int selectedRectPosY = text.getPosition().y + 3;

	selectedRect.setPosition(selectedRectPosX, selectedRectPosY);
	selectedRect.setSize(sf::Vector2f(selectedRectWidth, selectedRectHeight));
	selectedRect.setFillColor(sf::Color(40, 40, 150, 255));

	return selectedRect;
}

void Memory::updateState()
{	
	
	switch (configSpace.valueBaseSelectedIndex)
	{
		case 0: state.valueBase = 10; break;
		case 1: state.valueBase = 16; break;
	}

	switch (configSpace.addressBaseSelectedIndex)
	{
		case 0: state.addressBase = 10; break;
		case 1: state.addressBase = 16; break;
	}
}

void Memory::checkConfigSpaceHover(sf::Vector2i mousePos)
{
	//ADDRESS BASE
	bool hoverValid = false;
	int index = 0;
	for (auto& text : configSpace.addressBaseOptions)
	{
		sf::RectangleShape rect = getTextRect(text);
		sf::Vector2i relMousePos(mousePos.x, mousePos.y - config.h / 2);
		int minX = rect.getPosition().x;
		int minY = rect.getPosition().y;
		int maxX = minX + rect.getSize().x;
		int maxY = minY + rect.getSize().y;

		if ((relMousePos.x > minX && relMousePos.x < maxX) && (relMousePos.y > minY && relMousePos.y < maxY))
		{
			configSpace.addressBaseHoverIndex = index;
			configSpace.addressBaseHoverValid = true;
			hoverValid = true;
		}
		index++;
	}
	if (!hoverValid) { configSpace.addressBaseHoverValid = false; }

	//VALUE BASE
	hoverValid = false;
	index = 0;
	for (auto& text : configSpace.valueBaseOptions)
	{
		sf::RectangleShape rect = getTextRect(text);
		sf::Vector2i relMousePos(mousePos.x, mousePos.y - config.h/2);

		int minX = rect.getPosition().x;
		int minY = rect.getPosition().y;
		int maxX = minX + rect.getSize().x;
		int maxY = minY + rect.getSize().y;

		if ((relMousePos.x > minX && relMousePos.x < maxX) && (relMousePos.y > minY && relMousePos.y < maxY))
		{
			configSpace.valueBaseHoverIndex = index;
			hoverValid = true;
			configSpace.valueBaseHoverValid = true;
		}
		index++;
	}
	if (!hoverValid) { configSpace.valueBaseHoverValid = false; }
}

void Memory::checkConfigSpaceSelection()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (configSpace.addressBaseHoverValid)
		{
			configSpace.addressBaseSelectedIndex = configSpace.addressBaseHoverIndex;
		}
		if (configSpace.valueBaseHoverValid)
		{
			configSpace.valueBaseSelectedIndex = configSpace.valueBaseHoverIndex;
		}
	}

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
