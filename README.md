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

