#include "teamdatabase.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define PLAYERSLIMIT 12
#define TEAMLIMIT 1000

using namespace std;


void Player :: setPlayersData(string data[])
{
    number = data[0];
    name = data[1];
    surname = data[2];
    position = data[3];
    team = data[4];
    isActive = false;
}
void Player :: showPlayersData()
{
    cout << position << "\t" << number << "\t" << name << " " << surname << endl;
}
string Player :: getName()
{
    return name;
}
string Player :: getSurname()
{
    return surname;
}
void Team :: setName(string n)
{
    name = n;
}
string Team :: getTeamName()
{
    return name;
}
void Team :: showRoster()
{
    cout << "\t" << this -> name << endl;
    for(unsigned int i = 0; i != players.size(); i++)
    {
        players[i].showPlayersData();
    }
}
void Team :: setPlayers(Player plr)
{
    this -> players.push_back(plr);
}
int Team :: getSize()
{
    return this -> players.size();
}
void Database :: downloadData()
{
    int j,a;
    a = 0;
    int playerCount = 0;
    int teamCount = 0;
    fstream file;
    string line;
    string words[5] = {"","","","",""};
    file.open("teams.txt");
    if(file.good())
    {
        Team t[TEAMLIMIT];
        Player p[PLAYERSLIMIT];
        while(getline(file,line) && teamCount < TEAMLIMIT)
        {
            t[teamCount].setName(line);
            while(getline(file,line) && line != "")
            {
                j = 0;
                for(unsigned int i = 0; j != 4; i++)
                {
                    while(line[i] != ' ' && i < line.size())
                    {
                        words[j] += line[i];
                        i++;
                    }
                    j++;
                }
                words[4] = t[teamCount].getName();
                p[playerCount].setPlayersData(words);
                t[teamCount].setPlayers(p[playerCount]);
                while(a != 5)
                {
                    words[a] = "";
                    a++;
                }
                a = 0;
                playerCount++;
            }
            teams.push_back(t[teamCount]);
            teamCount++;

            playerCount = 0;
        }
        file.close();
    }
    else
        cout << "Unable to open file!" << endl;
}
void showTeams(Database d)
{
    system("clear");
    int returnKey;
    for(unsigned int i = 0; i != d.teams.size(); i++)
    {
        d.teams[i].showRoster();
        cout << endl;
    }

    cout << "Press enter to return" << endl;
    returnKey = getchar();
    returnKey = getchar();
}
