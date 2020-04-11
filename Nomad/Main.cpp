#include <SFML/Graphics.hpp>
#include <iostream>
#include "WatchList.h"
#include "Memory.h"
#include "Debugger.h"




int main()
{
	Debugger debugger;
	int abc = 500;


	debugger.start();
	debugger.add(abc, "newValue1");
	debugger.add(abc, "newValu3");
	debugger.add(abc, "newValue");

	
	return 0;
}