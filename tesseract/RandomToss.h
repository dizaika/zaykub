#ifndef RANDOMTOOS_H
#define RANDOMTOOS_H
#include "IToss.h"

class RandomToss : public IToss
{
public:
	RandomToss(){};
	int Run();
	~RandomToss(){};
};

int RandomToss::Run()
{
	return random(0, 1);
}

#endif
