#include "Arduino.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MsTimer2.h>
#include "Visualizer.h"
#include "cube.h"
#include "Button.h"

//#define BUTTON_COUNT 2
#define JOY_STICK_COUNT 2

#define BUTTON_LEFT  0
#define BUTTON_RIGHT 1
#define BUTTON_ENTER 2

#define LCD_ADDR 0x3F


LiquidCrystal_I2C lcd(LCD_ADDR, 16, 2);
void PrintIn(LiquidCrystal_I2C& alcd, const uint8_t row, const uint8_t column, const String message)
{
    alcd.setCursor(column, row);
    alcd.print(message);
    Serial.println(message);
}

JoyStick** joySticks;
Visualizer* visualizer;
Cube* cube;

inline void ScanButtons()
{
    for(int i = 0; i < JOY_STICK_COUNT; ++i) joySticks[i]->ScanState();
}

void TimerInterrupt()
{
    ScanButtons();
}

#include "factoryToss.h"
#include "factoryGames.h"

void setup()
{
    joySticks = new JoyStick*[JOY_STICK_COUNT];
    // for(int i = 0; i < JOY_STICK_COUNT; ++i) joySticks[i] = new JoyStick(A0+2*i, A0+1+2*i, 6+i);
    joySticks[0] = new JoyStick(A0, A1, 6);
    joySticks[1] = new JoyStick(A3, A2, 7);

    visualizer = new Visualizer(8, 27);
    cube = new Cube(3, 3, 3, visualizer);
    lcd.init();
    lcd.backlight();
    PrintIn(lcd, 0, 0, F("First String"));
    PrintIn(lcd, 0, 1, F("Second String"));

    MsTimer2::set(5, TimerInterrupt);
    MsTimer2::start();

    pinMode(13, OUTPUT);
    randomSeed(analogRead(A7));

    Serial.begin(9600);
}

void loop()
{
    const uint8_t GameCount = 3;
    uint8_t SelectedGame = 0;
    String* GameTitleArray = new String[GameCount];
    GameTitleArray[0] = F("1  PvE TicTaeToe");
    GameTitleArray[1] = F("2  PvP TicTaeToe");
    GameTitleArray[2] = F("3  ClickTimeTest");

    lcd.clear();
    joySticks[0]->ResetClick();
    while(!joySticks[0]->Pressed())
    {
        if(joySticks[0]->AxisX() > 480) ++SelectedGame;
        if(joySticks[0]->AxisX() < -480) --SelectedGame;
        if(SelectedGame < 0) SelectedGame = GameCount - 1;
        if(SelectedGame >= GameCount) SelectedGame = 0;
        PrintIn(lcd, 0, 0, F("Select game"));
        PrintIn(lcd, 1, 0, GameTitleArray[SelectedGame]);
        delay(250);
    }
    delete[] GameTitleArray;
    lcd.clear();

    IToss* toos = FactoryToos::Get();
    int res = toos->Run();
    delete toos;

    IGameable* game = FactoryGames::Get(SelectedGame);
    Serial.println(F("Game created"));
    game->Run(res, 0x00000700, 0x00070000);
    delete game;
}
