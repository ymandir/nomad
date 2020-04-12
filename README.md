
![ssWide](https://user-images.githubusercontent.com/62177295/79069683-cc43d880-7cd8-11ea-9cff-0b3d5c192817.png)

# Nomad Memory Watch
Nomad is a minimalist memory watch for C++ that has a watchlist feature to keep track of anything. All you have to do is link it to your project and debugger.add anything and everything (that's a lie) you want to track!

As soon as you run the application that is being watched, Nomad will launch it's own window in it's own thread and you will be able to watch the added variables as well as memory around them. 

## Show Me

```c++
#include "Debugger.h"

Debugger debugger;

int main () 
{
  //Nomad launches it's own thread
  debugger.start();
  
  //Add the variable you want to track
  debugger.add(entity.health, "monsterHP");
}
```

![monsterHP](https://user-images.githubusercontent.com/62177295/79069688-dbc32180-7cd8-11ea-81a6-abbb6c0cda70.png)

## How to use the window? 

Nomad window is composed of two tabs: watchlist and memory. 

- Switch between tabs: CTRL + UP / CRTL + DOWN
- Scroll on the active tab: UP / DOWN

## How do I link it?

Just get the most recent release and link it like any other external library and don't forget to unlink before publishing a release :)

## Tell me about the current state of developement

It is very early but I still encourage anyone to try it out and see if they like the idea or not. Many great features are going to be added in the near future. 


