#ifndef FACTORYGAMES_H
#define FACTORYGAMES_H
#include "IGameable.h"
#include "PvETicTacToeGame.h"
#include "PvPTicTacToeGame.h"
#include "ClickTime.h"

    class FactoryGames
    {
    public:
        static IGameable* Get(int num)
        {
            switch(num)
            {
                case 0:
                    return new PvE_TicTacToe_Game();
                    break;
                case 1:
                    return new PvP_TicTacToe_Game();
                    break;
                case 2:
                    return new Click_Time_Test();
                    break;
            }
        }
    };
#endif
