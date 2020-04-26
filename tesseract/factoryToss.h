#ifndef FACTORYTOOTH_H
#define FACTORYTOOTH_H
#include "RandomToss.h"
#include "ButtonCowboy.h"

class FactoryToos
{
public:
	static IToss* Get()
  {
    IToss* res;
    switch(random(1, 2))
    {
      case 0: res = new RandomToss();
          break;
      case 1: res = new ButtonCowboy();
          break;
    }
    return res;
  }

};

//IToss* FactoryToos::Get()


#endif
