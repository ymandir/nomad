#include <SFML/Graphics.hpp>
#include <iostream>
#include "WatchList.h"
#include "Memory.h"
#include "Debugger.h"




int main()
{
	Debugger debugger;
	int a = 0;


	debugger.start();
	debugger.add(a, "int");
	//debugger.add(cba, "integer");



	
	return 0;
}