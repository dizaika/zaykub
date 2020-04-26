#ifndef CLICK_TIME_H
#define CLICK_TIME_H
#include "IGameable.h"
#include "Button.h"

    class Click_Time_Test : public IGameable
    {
    private:

    public:
        void Run(int FirstPlayer, uint32_t FirstColor, uint32_t SecondColor);
    };

    void Click_Time_Test::Run(const int FirstPlayer, const uint32_t FirstColor, const uint32_t SecondColor)
    {
        lcd.clear();
        PrintIn(lcd, 0, 0, F("You must push wh"));
        PrintIn(lcd, 1, 0, F("en cube is white"));
        delay(2000);
        lcd.clear();

        uint32_t time = 0;
        for(uint8_t i = 0; i < 10; ++i)
        {
            visualizer->Clear(true);
            PrintIn(lcd, 0, 0, F("       3        "));
            delay(1000);
            PrintIn(lcd, 0, 0, F("       2        "));
            delay(1000);
            PrintIn(lcd, 0, 0, F("       1        "));
            delay(1000);
            lcd.clear();
            visualizer->SetAllPixelColor(0x00ffffff);
            visualizer->Show();
            if(joySticks[0]->Click() || joySticks[0]->Pressed())
            {
                --i;
                continue;
            }
            else
            {
                uint32_t tmp = millis();
                while(!joySticks[0]->Click())
                {
                    delay(1);
                };
                time += millis()-tmp;
            }
        }
        visualizer->Clear(true);
        lcd.clear();
        PrintIn(lcd, 0, 0, F("Your click time:"));
        PrintIn(lcd, 1, 0, (String)(time/10));
        delay(2000);
        lcd.clear();

    }
#endif
