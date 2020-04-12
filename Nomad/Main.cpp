
#include "Debugger.h"




int main()
{
	Debugger debugger;
	int a = 0;


	debugger.start();
	debugger.add(a, "int");

	int cap = 100;
	sf::Clock clock;
	while (a < cap)
	{
			if (clock.getElapsedTime().asMilliseconds() > 1000)
		{
			clock.restart();
			a++;
		}
	}


	
	return 0;
}