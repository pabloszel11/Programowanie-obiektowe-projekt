#include <iostream>
#include <vector>
#include "statistics.h"
#ifndef TEAMDATABASE_H
#define TEAMDATABASE_H


using namespace std;

class Player
{
protected:
    string name,surname,team,position,number;
    bool isActive;
    Stats st;
public:
    void setPlayersData(string data[]);
    void showPlayersData();
    string getName();
    string getSurname();
    friend class Game;
};

class Team : public Player
{
protected:
    string name;
    vector <Player> players;
    Player onCourt[5];  //players that are currently on the court
    TeamStats tst;

public:
    void setName(string n);
    string getTeamName();
    void showRoster();
    void setPlayers(Player plr);
    int getSize();
    friend class Game;
};

class Database : public Team
{
    vector <Team> teams;

public:
    void downloadData();
    friend void showTeams(Database d);
    friend class Game;
};

#endif

