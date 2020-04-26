#ifndef COWBOY_H
#define COWBOY_H
#define PLAYER_COUNT 2
#include "IToss.h"
// int buttonPins[PLAYER_COUNT] = {1, 2}; //пока пины абстрактные
// int ledPins[PLAYER_COUNT] = {3, 4};
class ButtonCowboy : public IToss
{
public:
	ButtonCowboy();
	int Run();
	~ButtonCowboy();
	
};

ButtonCowboy::ButtonCowboy()
{

}

int ButtonCowboy::Run()
{	
  lcd.clear();
  PrintIn(lcd, 0, 0, F("       3        "));
	visualizer->SetPixelColor(0, 8, 1, 1, 0);
	visualizer->Show();
	delay(1000);
  
  lcd.clear();
  PrintIn(lcd, 0, 0, F("       2        "));
	visualizer->SetPixelColor(9, 17, 16, 16, 0);
	visualizer->Show();
	delay(1000);
  
  lcd.clear();
  PrintIn(lcd, 0, 0, F("       1        "));
	visualizer->SetPixelColor(18, 26, 32, 32, 0);
	visualizer->Show();
	delay(1000+random(0, 500)-250);
  
  lcd.clear();
  PrintIn(lcd, 0, 0, F("     PUSH!      "));
	visualizer->SetAllPixelColor(64, 64, 64);
	visualizer->Show();
 
    joySticks[0]->ResetClick();
    joySticks[1]->ResetClick();
    int res = -1;
  	while(res == -1)
  	{
  		if (joySticks[0]->Pressed())  // если игрок номер «player» нажал кнопку...
	  	{
	  		res = 0;
	    }
	    if (joySticks[1]->Pressed())  // если игрок номер «player» нажал кнопку...
	  	{
	  		res = 1;
	    }
     //Serial.println(res);
      delay(1);
	}
  Serial.print(res);
  Serial.println(F(" toss win"));
  joySticks[0]->ResetClick();
  joySticks[1]->ResetClick();
  lcd.clear();
  visualizer->Clear(true);
  return res;
}

ButtonCowboy::~ButtonCowboy()
{
	
}

#endif
