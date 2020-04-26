#ifndef PVP_TIC_TAC_TOE_GAME_H
#define PVP_TIC_TAC_TOE_GAME_H
#include "IGameable.h"
#include "Button.h"
    namespace PvPTicTacToeGameGlobals{
        long PlayerColors[2];
        long*** stateMatrix;

        Point3D* analyzeField(long*** Matrix, Point3D point)
        {
            long& Value = Matrix[point.X][point.Y][point.Z];
            long LastValue = 0;
            uint8_t count = 0;
            Point3D* res = new Point3D[3];
            for(int8_t i = 0; i < 3; ++i)
            {
              res[i].X = 0;
              res[i].Y = 0;
              res[i].Z = 0;

            }
            int8_t X;
            int8_t Y;
            int8_t Z;

            for(int8_t dz = -1; dz <= 1; ++dz)
                for(int8_t dy = -1; dy <= 1; ++dy)
                    for(int8_t dx = -1; dx <= 1; ++dx)
                        if(dx != 0 || dy != 0 || dz != 0)
                        {
                            long LastValue = 0;
                            count = 0;

                            for(int8_t i = -2; i < 2; ++i)
                            {
                                X = point.X + i * dx;
                                Y = point.Y + i * dy;
                                Z = point.Z + i * dz;

                                if(X >= 0 && X < 3 &&
                                   Y >= 0 && Y < 3 &&
                                   Z >= 0 && Z < 3)
                                   {
                                       if (Matrix[X][Y][Z] == LastValue)
                                       {
                                           if(LastValue != 0)
                                           {
                                               ++count;
                                               res[count-1].X = X;
                                               res[count-1].Y = Y;
                                               res[count-1].Z = Z;
                                               if(count == 3)
                                               {
                                                   return res;
                                               }
                                           }
                                       }
                                       else
                                       {
                                           LastValue = Matrix[X][Y][Z];
                                           count = 1;
                                           res[count-1].X = X;
                                           res[count-1].Y = Y;
                                           res[count-1].Z = Z;
                                       }
                                   }
                            }
                        }

                delete[] res;
            return nullptr;
        }

        bool IsDrawGame(long*** Matrix, int8_t& z)
        {
            for(int y = 0; y <= 2; ++y)
                for(int x = 0; x <= 2; ++x)
                    if(Matrix[x][y][z] == 0) return false;

            return true;
        }
    }

    class PvP_Player
    {
    public:
        int8_t Num;
        Point3D fCurrentPosition;
        JoyStick* fJoyStick;

        PvP_Player(int8_t aNum, JoyStick* aJoyStick)
        {
            Num = aNum;
            fJoyStick = aJoyStick;
            fCurrentPosition.X = 1;
            fCurrentPosition.Y = 1;
            fCurrentPosition.Z = 0;
        }

        void CheckControls()
        {
            if(Num)
            {
                if(fJoyStick->AxisX() > 490) ++fCurrentPosition.X;
                if(fJoyStick->AxisX() < -490) --fCurrentPosition.X;
            }
            else
            {
                if(fJoyStick->AxisX() > 490) --fCurrentPosition.X;
                if(fJoyStick->AxisX() < -490) ++fCurrentPosition.X;
            }

            if(Num)
            {
                if(fJoyStick->AxisY() > 490) --fCurrentPosition.Y;
                if(fJoyStick->AxisY() < -490) ++fCurrentPosition.Y;
            }
            else
            {
                if(fJoyStick->AxisY() > 490) ++fCurrentPosition.Y;
                if(fJoyStick->AxisY() < -490) --fCurrentPosition.Y;
            }

            if(fCurrentPosition.X >= cube->LenX()) fCurrentPosition.X = 0;
            if(fCurrentPosition.X < 0) fCurrentPosition.X = cube->LenX()-1;

            if(fCurrentPosition.Y >= cube->LenY()) fCurrentPosition.Y = 0;
            if(fCurrentPosition.Y < 0) fCurrentPosition.Y = cube->LenY()-1;

        }

        bool TryMakeTurn()
        {
            long& elem = PvPTicTacToeGameGlobals::stateMatrix[fCurrentPosition.X][fCurrentPosition.Y][fCurrentPosition.Z];
            if(!elem)
            {
              elem = PvPTicTacToeGameGlobals::PlayerColors[this->Num];
              return true;
            }
            return false;
        }

        ~PvP_Player()
        {

        }

    };

    class PvP_TicTacToe_Game : public IGameable
    {
    private:
        PvP_Player** fPlayer;
        int8_t fPlayerNum;
    public:
        PvP_TicTacToe_Game()
        {
            fPlayer = new PvP_Player*[2];
            for(int i = 0; i < 2; ++i) fPlayer[i] = new PvP_Player(i, nullptr);
        }

        ~PvP_TicTacToe_Game()
        {
            for(int count = 1 ;count >= 0; --count) delete fPlayer[count];
            delete[] fPlayer;
            Serial.println(F("Players deleted"));
        }

        void Run(int FirstPlayer, uint32_t FirstColor, uint32_t SecondColor);
    };

    void PvP_TicTacToe_Game::Run(const int FirstPlayer, const uint32_t FirstColor, const uint32_t SecondColor)
    {
        Serial.println(F("Game run"));
        Serial.println(FirstPlayer);
        bool gameEnd = false;
        int8_t layer = 0;
        Point3D* WinCombination;

        fPlayerNum = FirstPlayer;
        if(fPlayerNum < 0) fPlayerNum = 0;
        if(fPlayerNum > 1) fPlayerNum = 1;

        PvPTicTacToeGameGlobals::PlayerColors[0] = FirstColor;
        PvPTicTacToeGameGlobals::PlayerColors[1] = SecondColor;

        fPlayer[0]->fCurrentPosition.X = 1;
        fPlayer[0]->fCurrentPosition.Y = 1;
        fPlayer[0]->fCurrentPosition.Z = 0;

        fPlayer[1]->fCurrentPosition.X = 1;
        fPlayer[1]->fCurrentPosition.Y = 1;
        fPlayer[1]->fCurrentPosition.Z = 0;

        fPlayer[0]->Num = 0;
        fPlayer[0]->fJoyStick = joySticks[0];

        fPlayer[1]->Num = 1;
        fPlayer[1]->fJoyStick = joySticks[1];

        joySticks[0]->ResetClick();
        joySticks[1]->ResetClick();

        delay(100);

        PvPTicTacToeGameGlobals::stateMatrix = GenerateMatrix(3, 3, 3);
            long*** VisibleMatrix = GenerateMatrix(3, 3, 3);

        cube->SetPixelColor(PvPTicTacToeGameGlobals::stateMatrix, 3, 3, 3);
        CopyMatrix(VisibleMatrix, PvPTicTacToeGameGlobals::stateMatrix, 3, 3, 3);
        VisibleMatrix[fPlayer[fPlayerNum]->fCurrentPosition.X][fPlayer[fPlayerNum]->fCurrentPosition.Y][fPlayer[fPlayerNum]->fCurrentPosition.Z] = (PvPTicTacToeGameGlobals::PlayerColors[fPlayer[fPlayerNum]->Num]+0x00010101) & 0x00ffffff;
        cube->SetPixelColor(VisibleMatrix, 3, 3, 3);
        cube->Show();

        Serial.println(F("Game loop start"));
        uint8_t blinkCounter = 0;
        while(!gameEnd)
        {
            long PlayerWin = 0;
            fPlayer[0]->fCurrentPosition.Z = layer;
            fPlayer[1]->fCurrentPosition.Z = layer;

            if(++blinkCounter > 1) blinkCounter = 0;

            switch(fPlayerNum)
            {
            case 0:
                fPlayer[0]->CheckControls();
                if(fPlayer[0]->fJoyStick->Click())
                {
                    Serial.println(F("People 1 make turn"));
                    if(fPlayer[0]->TryMakeTurn())
                    {
                        fPlayerNum = 1 - fPlayerNum;
                        WinCombination = PvPTicTacToeGameGlobals::analyzeField(PvPTicTacToeGameGlobals::stateMatrix, fPlayer[0]->fCurrentPosition);
                        if(WinCombination != nullptr)
                        {
                            PlayerWin = PvPTicTacToeGameGlobals::stateMatrix[WinCombination[0].X][WinCombination[0].Y][WinCombination[0].Z];
                        }
                    }
                }
                break;
            case 1:
                fPlayer[1]->CheckControls();
                if(fPlayer[1]->fJoyStick->Click())
                {
                    Serial.println(F("People 2 make turn"));
                    if(fPlayer[1]->TryMakeTurn())
                    {
                        fPlayerNum = 1 - fPlayerNum;
                        WinCombination = PvPTicTacToeGameGlobals::analyzeField(PvPTicTacToeGameGlobals::stateMatrix, fPlayer[1]->fCurrentPosition);
                        if(WinCombination != nullptr)
                        {
                            PlayerWin = PvPTicTacToeGameGlobals::stateMatrix[WinCombination[0].X][WinCombination[0].Y][WinCombination[0].Z];
                        }
                    }
                }
                break;
            }

            if(PlayerWin == FirstColor)
            {
                    lcd.clear();
                    PrintIn(lcd, 0, 2, F("First player"));
                    PrintIn(lcd, 1, 6, F("WIN!"));
                    delay(500);
                    lcd.clear();

                    if(++layer > 2) gameEnd = true;
                    PrintIn(lcd, 0, 3, F("Next layer"));
                    delay(500);
                    lcd.clear();
            }
            else if(PlayerWin == SecondColor)
            {
                    lcd.clear();
                    PrintIn(lcd, 0, 2, F("Second player"));
                    PrintIn(lcd, 1, 6, F("WIN!"));
                    delay(500);
                    lcd.clear();

                    if(++layer > 2) gameEnd = true;

                    PrintIn(lcd, 0, 3, F("Next layer"));
                    delay(500);
                    lcd.clear();
            }
            else
            {
                if(PvPTicTacToeGameGlobals::IsDrawGame(PvPTicTacToeGameGlobals::stateMatrix, layer))
                    if(++layer > 2) gameEnd = true;
            }

            CopyMatrix(VisibleMatrix, PvPTicTacToeGameGlobals::stateMatrix, 3, 3, 3);
            if(blinkCounter == 0) //0x000F0F0F 0x00010101
              VisibleMatrix[fPlayer[fPlayerNum]->fCurrentPosition.X][fPlayer[fPlayerNum]->fCurrentPosition.Y][fPlayer[fPlayerNum]->fCurrentPosition.Z] = (PvPTicTacToeGameGlobals::PlayerColors[fPlayer[fPlayerNum]->Num]*10) & 0x00ffffff;
            else
              VisibleMatrix[fPlayer[fPlayerNum]->fCurrentPosition.X][fPlayer[fPlayerNum]->fCurrentPosition.Y][fPlayer[fPlayerNum]->fCurrentPosition.Z] = (PvPTicTacToeGameGlobals::PlayerColors[fPlayer[fPlayerNum]->Num]*2) & 0x00ffffff;

            cube->SetPixelColor(VisibleMatrix, 3, 3, 3);
            cube->Show();

            delay(250);

            if(gameEnd)
            {
                Serial.println(F("Game ended"));
                CopyMatrix(VisibleMatrix, PvPTicTacToeGameGlobals::stateMatrix, 3, 3, 3);
                Serial.println(F("StateMatrix Copy"));
                for(int8_t i = 0; i < 3; ++i)
                {
                    VisibleMatrix[WinCombination[i].X][WinCombination[i].Y][WinCombination[i].Z] = (PvPTicTacToeGameGlobals::PlayerColors[fPlayer[fPlayerNum]->Num]+0x000F0F0F) & 0x00ffffff;
                    cube->SetPixelColor(VisibleMatrix, 3, 3, 3);
                    cube->Show();

                    delay(250);
                }

                delay(1000);
            }

        }

        FreeMatrix(VisibleMatrix, 3, 3, 3);
        Serial.println(F("Visible Matrix freed"));
        FreeMatrix(PvPTicTacToeGameGlobals::stateMatrix, 3, 3, 3);
        Serial.println(F("State Matrix freed"));
    }
#endif
