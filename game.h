#include <iostream>
#include "teamdatabase.h"
#ifndef GAME_H
#define GAME_H

using namespace std;

class Game
{
    Team teamA, teamB;
    int quarter;

public:
    Game();
    void selectTeams();
    void selectStartingFive();
    void gameplay();
    void whatToDo(string action);
};

#endif
