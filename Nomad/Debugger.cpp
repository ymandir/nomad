#include "Debugger.h"



Debugger::Debugger() : m_thread(&Debugger::update, this)
{
	watchList = new WatchList;
}


Debugger::~Debugger()
{

}



void Debugger::switchTabs(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
			{
				if (memory.selected || watchList->selected)
				{
					if (memory.selected) { memory.selected = false; }
					else { memory.selected = true; }
					if (watchList->selected) { watchList->selected = false; }
					else { watchList->selected = true; }
				}

			}
		}
	}

}

void Debugger::start()
{

	m_thread.launch();


}

void Debugger::add(int& value, std::string name)
{
	watchList->add(&value,name);
}

void Debugger::add(float& value, std::string name)
{
	watchList->add(&value, name);
}

void Debugger::update()
{
	int a = 255;
	memory.setStart(&a);


	sf::RenderWindow window(sf::VideoMode(1920 / 2, 1080), "NOMAD", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				m_thread.terminate();
			}
			memory.updateEvents(event);
			watchList->updateEvents(event);
			switchTabs(event);
		}

		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		if (watchList->selectionChanged)
		{
			memory.setStart(watchList->selectedAdress);
			watchList->selectionChanged = false;
		}



		watchList->update(mousePos);
		memory.update(mousePos);

		window.clear();
		window.draw(watchList->getSprite());
		window.draw(memory.getSprite());
		window.display();
	}
}