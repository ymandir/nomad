#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "WatchList.h"
#include "Memory.h"



class Debugger
{
public:
	sf::Mutex mutex;
	sf::Font inconsolata;
	WatchList* watchList;
	Memory memory;


	void start();
	void add(int&, std::string);
	void add(float&,std::string);

	Debugger();
	~Debugger();
private: 
	sf::Thread m_thread;
	void update();
	void switchTabs(sf::Event event);
};

