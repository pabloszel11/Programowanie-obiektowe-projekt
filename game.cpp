#include <iostream>
#include <unistd.h>
#include "menu.h"
#include <iomanip>
#include "teamdatabase.h"
#include "game.h"

using namespace std;

Game :: Game()
{
    quarter = 1;
}
void Game :: selectTeams()
{
    Game g;
    system("clear");
    Database d;
    d.downloadData();
    cout << "Choose first team" << endl;
    for(unsigned int i = 0; i != d.teams.size(); i++)
    {
        cout << i + 1 << " " << d.teams[i].getTeamName() << endl;
    }
    int choice1,choice2;
    cin >> choice1;
    teamA = d.teams[choice1 - 1];
    system("clear");
    cout << "Choose second team" << endl;
    for(unsigned int i = 0; i != d.teams.size(); i++)
    {
        if(i != choice1 - 1)
            cout << i + 1 << " " << d.teams[i].getTeamName() << endl;
    }
    cin >> choice2;
    teamB = d.teams[choice2 - 1];

    system("clear");
    cout << teamA.getTeamName() << " vs " << teamB.getTeamName() << endl;

    selectStartingFive();
}

void Game :: selectStartingFive()
{
    char a;
    system("clear");
    bool ok;
    string choice;
    teamA.showRoster();
    cout << "Select starting five for " << teamA.getTeamName() << endl;
    int i = 0;
    int j;
    while(i < 5)
    {
        ok = false;
        cin >> choice;
        j = 0;
        try
        {
            while(j < teamA.getSize())
            {
                if(choice == teamA.players[j].number)
                {
                    teamA.onCourt[i] = teamA.players[j];
                    teamA.players[j].isActive = true;
                    ok = true;
                }
                j++;
            }

            if(ok == false)
                throw "There is no player in this team with that number";

            i++;
        }
        catch(char const* a)
        {
            cout << a << endl;
        }

    }

    a = getchar();

    system("clear");

    teamB.showRoster();
    cout << "Select starting five for " << teamB.getTeamName() << endl;
    i = 0;
    while(i < 5)
    {
        ok = false;
        cin >> choice;
        j = 0;
        try
        {
            while(j < teamB.getSize())
            {
                if(choice == teamB.players[j].number)
                {
                    teamB.onCourt[i] = teamB.players[j];
                    teamB.players[j].isActive = true;
                    ok = true;
                }
                j++;
            }

            if(ok == false)
                throw "There is no player in this team with that number";

            i++;
        }
        catch(char const* a)
        {
            cout << a << endl;
        }

    }
    gameplay();
    mainMenu();
}

void Game :: gameplay()
{
    string action;
    char tip;
    int i = 0;
    if(quarter == 1)
    {
        cout << "Who won the tip-off?" << endl;
        cout << "(1)" << teamA.getTeamName() << endl;
        cout << "(2)" << teamB.getTeamName() << endl;
        tip = getchar();
        tip = getchar();
        if(tip == '1')
            teamA.tst.gainPossession();
        else
            teamB.tst.gainPossession();
    }

    while(1)
    {
        system("clear");
        if(quarter > 4 && teamA.tst.getPts() != teamB.tst.getPts())
        {
            int a;
            cout << "GAME OVER. FINAL SCORE:" << endl;
            cout << teamA.getTeamName() << " " << teamA.tst.getPts() << ":" << teamB.tst.getPts() << " " << teamB.getTeamName() << endl;
            a = getchar();
            a = getchar();
            system("clear");
            break;
        }
        if(quarter != 1)
        {
            cout << "Who has the possession?" << endl;
            cout << "(1)" << teamA.getTeamName() << endl;
            cout << "(2)" << teamB.getTeamName() << endl;
            tip = getchar();
            tip = getchar();
            if(tip == '1')
            {
                teamA.tst.gainPossession();
                teamB.tst.losePossession();
            }
            else
            {
                teamB.tst.gainPossession();
                teamA.tst.losePossession();
            }
            system("clear");
        }
        if(quarter <= 4)
            cout << "QUARTER " << quarter << endl << endl;
        else
            cout << "OVERTIME " << quarter - 4 << endl;
        cout << teamA.getTeamName() << " " << teamA.tst.getPts();
        cout << "\tTeam fouls: " << teamA.tst.getFls();
        if(teamA.tst.getPossession() == true)
            cout << "\t*" << endl;
        else
            cout << endl;
        cout << "\t\t\t" << "PTS\t" << "RBS\t" << "AST\t" << "FLS\t";
        cout << "BLKS\t" << "STLS\t" << "TOS\t" << "FGM/A\t" << "FG%\t";
        cout << "TPM/A\t" << "TP%\t" << "FTM/A\t" << "FT%" << endl;
        cout << "\tON THE COURT" << endl;
        int i = 0;
        while(i < teamA.getSize())
        {
            if(teamA.players[i].isActive == true)
            {
                cout << teamA.players[i].number << " " << teamA.players[i].getName()[0] << "." << teamA.players[i].getSurname() << "\t\t";
                cout << teamA.players[i].st.getPts();
                cout << "\t" << teamA.players[i].st.getRbs();
                cout << "\t" << teamA.players[i].st.getAst();
                cout << "\t" << teamA.players[i].st.getFls();
                cout << "\t" << teamA.players[i].st.getBlks();
                cout << "\t" << teamA.players[i].st.getStls();
                cout << "\t" << teamA.players[i].st.getTos();
                cout << "\t" << teamA.players[i].st.getFgm() << "/" << teamA.players[i].st.getFga();
                cout << "\t" << setprecision(3) << teamA.players[i].st.getFgPrct() << "%";
                cout << "\t" << teamA.players[i].st.getTpm() << "/" << teamA.players[i].st.getTpa();
                cout << "\t" << setprecision(3) << teamA.players[i].st.getTpPrct() << "%";
                cout << "\t" << teamA.players[i].st.getFtm() << "/" << teamA.players[i].st.getFta();
                cout << "\t" << setprecision(3) << teamA.players[i].st.getFtPrct() << "%" << endl;


            }

            i++;
        }
        i = 0;
        cout << "\tON THE BENCH" << endl;
        while(i < teamA.getSize())
        {
            if(teamA.players[i].isActive == false)
            {
                cout << teamA.players[i].number << " " << teamA.players[i].getName()[0] << "." << teamA.players[i].getSurname() << "\t\t";
                cout << teamA.players[i].st.getPts();
                cout << "\t" << teamA.players[i].st.getRbs();
                cout << "\t" << teamA.players[i].st.getAst();
                cout << "\t" << teamA.players[i].st.getFls();
                cout << "\t" << teamA.players[i].st.getBlks();
                cout << "\t" << teamA.players[i].st.getStls();
                cout << "\t" << teamA.players[i].st.getTos();
                cout << "\t" << teamA.players[i].st.getFgm() << "/" << teamA.players[i].st.getFga();
                cout << "\t" << setprecision(3) << teamA.players[i].st.getFgPrct() << "%";
                cout << "\t" << teamA.players[i].st.getTpm() << "/" << teamA.players[i].st.getTpa();
                cout << "\t" << setprecision(3) << teamA.players[i].st.getTpPrct() << "%";
                cout << "\t" << teamA.players[i].st.getFtm() << "/" << teamA.players[i].st.getFta();
                cout << "\t" << setprecision(3) << teamA.players[i].st.getFtPrct() << "%" << endl;

            }
            i++;
        }
        i = 0;
        cout << endl;
        cout << endl;
        cout << teamB.getTeamName() << " " << teamB.tst.getPts();
        cout << "\tTeam fouls: " << teamB.tst.getFls();
        if(teamB.tst.getPossession() == true)
            cout << "\t*" << endl;
        else
            cout << endl;
        cout << "\t\t\t" << "PTS\t" << "RBS\t" << "AST\t" << "FLS\t";
        cout << "BLKS\t" << "STLS\t" << "TOS\t" << "FGM/A\t" << "FG%\t";
        cout << "TPM/A\t" << "TP%\t" << "FTM/A\t" << "FT%" << endl;
        cout << "\tON THE COURT" << endl;
        while(i < teamB.getSize())
        {
            if(teamB.players[i].isActive == true)
            {
                cout << teamB.players[i].number << " " << teamB.players[i].getName()[0] << "." << teamB.players[i].getSurname() << "\t\t";
                cout << teamB.players[i].st.getPts();
                cout << "\t" << teamB.players[i].st.getRbs();
                cout << "\t" << teamB.players[i].st.getAst();
                cout << "\t" << teamB.players[i].st.getFls();
                cout << "\t" << teamB.players[i].st.getBlks();
                cout << "\t" << teamB.players[i].st.getStls();
                cout << "\t" << teamB.players[i].st.getTos();
                cout << "\t" << teamB.players[i].st.getFgm() << "/" << teamB.players[i].st.getFga();
                cout << "\t" << setprecision(3) << teamB.players[i].st.getFgPrct() << "%";
                cout << "\t" << teamB.players[i].st.getTpm() << "/" << teamB.players[i].st.getTpa();
                cout << "\t" << setprecision(3) << teamB.players[i].st.getTpPrct() << "%";
                cout << "\t" << teamB.players[i].st.getFtm() << "/" << teamB.players[i].st.getFta();
                cout << "\t" << setprecision(3) << teamB.players[i].st.getFtPrct() << "%" << endl;

            }

            i++;
        }
        i = 0;
        cout << "\tON THE BENCH" << endl;
        while(i < teamB.getSize())
        {
            if(teamB.players[i].isActive == false)
            {
                cout << teamB.players[i].number << " " << teamB.players[i].getName()[0] << "." << teamB.players[i].getSurname() << "\t\t";
                cout << teamB.players[i].st.getPts();
                cout << "\t" << teamB.players[i].st.getRbs();
                cout << "\t" << teamB.players[i].st.getAst();
                cout << "\t" << teamB.players[i].st.getFls();
                cout << "\t" << teamB.players[i].st.getBlks();
                cout << "\t" << teamB.players[i].st.getStls();
                cout << "\t" << teamB.players[i].st.getTos();
                cout << "\t" << teamB.players[i].st.getFgm() << "/" << teamB.players[i].st.getFga();
                cout << "\t" << setprecision(3) << teamB.players[i].st.getFgPrct() << "%";
                cout << "\t" << teamB.players[i].st.getTpm() << "/" << teamB.players[i].st.getTpa();
                cout << "\t" << setprecision(3) << teamB.players[i].st.getTpPrct() << "%";
                cout << "\t" << teamB.players[i].st.getFtm() << "/" << teamB.players[i].st.getFta();
                cout << "\t" << setprecision(3) << teamB.players[i].st.getFtPrct() << "%" << endl;

            }
            i++;
        }

        cin >> action;
        whatToDo(action);

    }
}
void Game :: whatToDo(string action)
{
    if(action == "2p")
    {
        //TeamA has the ball
        if(teamA.tst.getPossession() == true)
        {
            try
            {
                string num;
                cout << "Who took the shot?" << endl;
                cin >> num;
                for(int i = 0; i < teamA.getSize(); i++)
                {
                    bool ok = false;
                    if(teamA.players[i].number == num)
                    {
                        if(teamA.players[i].isActive == false)
                            throw "This player is on the bench!";
                        //if the shot is made
                        if(teamA.players[i].st.twoPointShotTaken() == true)
                        {
                            ok = true;
                            teamA.tst.twoPointShotMade();
                            cout << "Who got the assist? (type 'n' if noone)" << endl;
                            cin >> num;
                            for(int j = 0; j < teamA.getSize() && num != "n"; j++)
                            {
                                if(teamA.players[j].number == num)
                                {
                                    teamA.players[j].st.assist();
                                    teamA.tst.losePossession();
                                    teamB.tst.gainPossession();
                                    return ;
                                }
                            }
                            teamA.tst.losePossession();
                                    teamB.tst.gainPossession();
                            if(ok == false)
                                throw "There is no player with that number";
                        }
                        //if the shot is missed
                        else
                        {
                            cout << "Which team got the rebound?" << endl;
                            cout << "(1)" << teamA.getTeamName() << endl;
                            cout << "(2)" << teamB.getTeamName() << endl;
                            cout << "(n)one" << endl;
                            cin >> num;
                            if(num == "1")
                            {
                                cout << "Who exactly?" << endl;
                                cin >> num;
                                for(int j = 0; j < teamA.getSize(); j++)
                                {
                                    if(teamA.players[j].number == num)
                                    {
                                        teamA.players[j].st.rebound();
                                        ok = true;
                                        return ;
                                    }
                                }
                            }
                            else if(num == "2")
                            {
                                cout << "Who exactly?" << endl;
                                cin >> num;
                                for(int j = 0; j < teamB.getSize(); j++)
                                {
                                    if(teamB.players[j].number == num)
                                    {
                                        teamB.players[j].st.rebound();
                                        teamB.tst.gainPossession();
                                        teamA.tst.losePossession();
                                        ok = true;
                                        return ;
                                    }
                                }
                            }
                            else
                                return;
                            if(ok == false)
                                throw "There is no player with that number";
                        }

                    }
                }
            }
            catch(char const* a)
            {
                cout << a << endl;
                whatToDo(action);
            }
        }
        //teamB has the ball
        else
        {
            try
            {
                string num;
                cout << "Who took the shot?" << endl;
                cin >> num;
                for(int i = 0; i < teamB.getSize(); i++)
                {
                    bool ok = false;
                    if(teamB.players[i].number == num)
                    {
                        if(teamB.players[i].isActive == false)
                            throw "This player is on the bench!";
                        //if the shot is made
                        if(teamB.players[i].st.twoPointShotTaken() == true)
                        {
                            ok = true;
                            teamB.tst.twoPointShotMade();
                            cout << "Who got the assist? (type 'n' if noone)" << endl;
                            cin >> num;
                            for(int j = 0; j < teamB.getSize() && num != "n"; j++)
                            {
                                if(teamB.players[j].number == num)
                                {
                                    teamB.players[j].st.assist();
                                    teamB.tst.losePossession();
                                    teamA.tst.gainPossession();
                                    return ;
                                }
                            }
                            teamB.tst.losePossession();
                                    teamA.tst.gainPossession();
                            if(ok == false)
                                throw "There is no player with that number";
                        }
                        //if the shot is missed
                        else
                        {
                            cout << "Which team got the rebound?" << endl;
                            cout << "(1)" << teamB.getTeamName() << endl;
                            cout << "(2)" << teamA.getTeamName() << endl;
                            cout << "(n)one" << endl;
                            cin >> num;
                            if(num == "1")
                            {
                                cout << "Who exactly?" << endl;
                                cin >> num;
                                for(int j = 0; j < teamB.getSize(); j++)
                                {
                                    if(teamB.players[j].number == num)
                                    {
                                        teamB.players[j].st.rebound();
                                        ok = true;
                                        return ;
                                    }
                                }
                            }
                            else if(num == "2")
                            {
                                cout << "Who exactly?" << endl;
                                cin >> num;
                                for(int j = 0; j < teamA.getSize(); j++)
                                {
                                    if(teamA.players[j].number == num)
                                    {
                                        teamA.players[j].st.rebound();
                                        teamA.tst.gainPossession();
                                        teamB.tst.losePossession();
                                        ok = true;
                                        return ;
                                    }
                                }
                            }
                            else
                                return ;
                            if(ok == false)
                                throw "There is no player with that number";
                        }

                    }
                }
            }
            catch(char const* a)
            {
                cout << a << endl;
                whatToDo(action);
            }
        }

    }
    if(action == "3p")
    {
        //TeamA has the ball
        if(teamA.tst.getPossession() == true)
        {
            try
            {
                string num;
                cout << "Who took the shot?" << endl;
                cin >> num;
                for(int i = 0; i < teamA.getSize(); i++)
                {
                    bool ok = false;
                    if(teamA.players[i].number == num)
                    {
                        if(teamA.players[i].isActive == false)
                            throw "This player is on the bench!";
                        //if the shot is made
                        if(teamA.players[i].st.threePointShotTaken() == true)
                        {
                            ok = true;
                            teamA.tst.threePointShotMade();
                            cout << "Who got the assist? (type 'n' if noone)" << endl;
                            cin >> num;
                            for(int j = 0; j < teamA.getSize() && num != "n"; j++)
                            {
                                if(teamA.players[j].number == num)
                                {
                                    teamA.players[j].st.assist();
                                    teamA.tst.losePossession();
                                    teamB.tst.gainPossession();
                                    return ;
                                }
                            }
                            teamA.tst.losePossession();
                                    teamB.tst.gainPossession();
                            if(ok == false)
                                throw "There is no player with that number";
                        }
                        //if the shot is missed
                        else
                        {
                            cout << "Which team got the rebound?" << endl;
                            cout << "(1)" << teamA.getTeamName() << endl;
                            cout << "(2)" << teamB.getTeamName() << endl;
                            cout << "(n)one" << endl;
                            cin >> num;
                            if(num == "1")
                            {
                                cout << "Who exactly?" << endl;
                                cin >> num;
                                for(int j = 0; j < teamA.getSize(); j++)
                                {
                                    if(teamA.players[j].number == num)
                                    {
                                        teamA.players[j].st.rebound();
                                        teamA.tst.gainPossession();
                                        teamB.tst.losePossession();
                                        ok = true;
                                        return ;
                                    }
                                }
                            }
                            else if(num == "2")
                            {
                                cout << "Who exactly?" << endl;
                                cin >> num;
                                for(int j = 0; j < teamB.getSize(); j++)
                                {
                                    if(teamB.players[j].number == num)
                                    {
                                        teamB.players[j].st.rebound();
                                        teamB.tst.gainPossession();
                                        teamA.tst.losePossession();
                                        ok = true;
                                        return ;
                                    }
                                }
                            }
                            else
                                return;
                            if(ok == false)
                                throw "There is no player with that number";
                        }

                    }
                }
            }
            catch(char const* a)
            {
                cout << a << endl;
                whatToDo(action);
            }
        }
        //teamB has the ball
        else
        {
            try
            {
                string num;
                cout << "Who took the shot?" << endl;
                cin >> num;
                for(int i = 0; i < teamB.getSize(); i++)
                {
                    bool ok = false;
                    if(teamB.players[i].number == num)
                    {
                        if(teamB.players[i].isActive == false)
                            throw "This player is on the bench!";
                        //if the shot is made
                        if(teamB.players[i].st.threePointShotTaken() == true)
                        {
                            ok = true;
                            teamB.tst.threePointShotMade();
                            cout << "Who got the assist? (type 'n' if noone)" << endl;
                            cin >> num;
                            for(int j = 0; j < teamB.getSize() && num != "n"; j++)
                            {
                                if(teamB.players[j].number == num)
                                {
                                    teamB.players[j].st.assist();
                                    teamB.tst.losePossession();
                                    teamA.tst.gainPossession();
                                    return ;
                                }
                            }
                            teamB.tst.losePossession();
                                    teamA.tst.gainPossession();
                            if(ok == false)
                                throw "There is no player with that number";
                        }
                        //if the shot is missed
                        else
                        {
                            cout << "Which team got the rebound?" << endl;
                            cout << "(1)" << teamB.getTeamName() << endl;
                            cout << "(2)" << teamA.getTeamName() << endl;
                            cout << "(n)one" << endl;
                            cin >> num;
                            if(num == "1")
                            {
                                cout << "Who exactly?" << endl;
                                cin >> num;
                                for(int j = 0; j < teamB.getSize(); j++)
                                {
                                    if(teamB.players[j].number == num)
                                    {
                                        teamB.players[j].st.rebound();
                                        ok = true;
                                        return ;
                                    }
                                }
                            }
                            else if(num == "2")
                            {
                                cout << "Who exactly?" << endl;
                                cin >> num;
                                for(int j = 0; j < teamA.getSize(); j++)
                                {
                                    if(teamA.players[j].number == num)
                                    {
                                        teamA.players[j].st.rebound();
                                        teamA.tst.gainPossession();
                                        teamB.tst.losePossession();
                                        ok = true;
                                        return ;
                                    }
                                }
                            }
                            else
                                return;
                            if(ok == false)
                                throw "There is no player with that number";
                        }

                    }
                }
            }
            catch(char const* a)
            {
                cout << a << endl;
                whatToDo(action);
            }
        }

    }
    if(action == "df")
    {
        try
        {
            bool ok = false;
            //teamA has the ball
            if(teamA.tst.getPossession() == true)
            {
                cout << "Who commited a foul?" << endl;
                string num;
                cin >> num;
                for(int i = 0; i < teamB.getSize(); i++)
                {
                    if(num == teamB.players[i].number)
                    {
                        if(teamB.players[i].isActive == false)
                            throw "This player is on the bench!";
                        ok = true;
                        teamB.players[i].st.foul();
                        teamB.tst.foul();
                        if(teamB.players[i].st.getFls() >= 6)
                        {
                            teamB.players[i].isActive = false;
                            cout << teamB.players[i].getName() << " " << teamB.players[i].getSurname() << " fouled out! Choose a substitution" << endl;
                            cin >> num;
                            for(int j = 0; j < teamB.getSize(); j++)
                            {
                                if(num == teamB.players[j].number)
                                {
                                    if(teamB.players[j].isActive == true)
                                        throw "This player is already on the court!";
                                    if(teamB.players[j].st.getFls() >= 6)
                                        throw "This player is over the foul limit!";
                                    teamB.players[j].isActive = true;
                                    ok = true;
                                }
                            }
                        }
                        cout << "How many free throws should the player take? (n if none)" << endl;
                        cin >> num;
                        if(num == "1")
                        {
                            cout << "Who was fouled?" << endl;
                            cin >> num;
                            for(int j = 0; j < teamA.getSize(); j++)
                            {
                                ok = false;
                                if(num == teamA.players[j].number)
                                {
                                    if(teamA.players[j].isActive == false)
                                        throw "This player is on the bench!";
                                    ok = true;
                                    if(teamA.players[j].st.freeThrowTaken() == true)
                                    {
                                        teamA.tst.freeThrowMade();
                                        teamB.tst.gainPossession();
                                        teamA.tst.losePossession();
                                        return ;
                                    }
                                    else
                                    {
                                        cout << "Which team got the rebound?" << endl;
                                        cout << "(1)" << teamA.getTeamName() << endl;
                                        cout << "(2)" << teamB.getTeamName() << endl;
                                        cout << "(n)one" << endl;
                                        cin >> num;
                                        if(num == "1")
                                        {
                                            cout << "Who exactly?" << endl;
                                            cin >> num;
                                            for(int j = 0; j < teamA.getSize(); j++)
                                            {
                                                if(teamA.players[j].number == num)
                                                {
                                                    teamA.players[j].st.rebound();
                                                    ok = true;
                                                    return ;
                                                }
                                            }
                                        }
                                        else if (num == "2")
                                        {
                                            cout << "Who exactly?" << endl;
                                            cin >> num;
                                            for(int j = 0; j < teamB.getSize(); j++)
                                            {
                                                if(teamB.players[j].number == num)
                                                {
                                                    teamB.players[j].st.rebound();
                                                    teamB.tst.gainPossession();
                                                    teamA.tst.losePossession();
                                                    ok = true;
                                                    return ;
                                                }
                                            }
                                        }
                                        else
                                            return;
                                    }
                                }
                            }
                        }
                        else if(num == "2")
                        {
                            cout << "Who was fouled?" << endl;
                            cin >> num;
                            for(int j = 0; j < teamA.getSize(); j++)
                            {
                                ok = false;
                                if(num == teamA.players[j].number)
                                {
                                    if(teamA.players[j].isActive == false)
                                        throw "This player is on the bench!";
                                    ok = true;
                                    if(teamA.players[j].st.freeThrowTaken()){teamA.tst.freeThrowMade();}
                                    if(teamA.players[j].st.freeThrowTaken() == true)
                                    {
                                        teamA.tst.freeThrowMade();
                                        teamB.tst.gainPossession();
                                        teamA.tst.losePossession();
                                        return ;
                                    }
                                    else
                                    {
                                        cout << "Which team got the rebound?" << endl;
                                        cout << "(1)" << teamA.getTeamName() << endl;
                                        cout << "(2)" << teamB.getTeamName() << endl;
                                        cout << "(n)one" << endl;
                                        cin >> num;
                                        if(num == "1")
                                        {
                                            cout << "Who exactly?" << endl;
                                            cin >> num;
                                            for(int j = 0; j < teamA.getSize(); j++)
                                            {
                                                if(teamA.players[j].number == num)
                                                {
                                                    teamA.players[j].st.rebound();
                                                    ok = true;
                                                    return ;
                                                }
                                            }
                                        }
                                        else if (num == "2")
                                        {
                                            cout << "Who exactly?" << endl;
                                            cin >> num;
                                            for(int j = 0; j < teamB.getSize(); j++)
                                            {
                                                if(teamB.players[j].number == num)
                                                {
                                                    teamB.players[j].st.rebound();
                                                    teamB.tst.gainPossession();
                                                    teamA.tst.losePossession();
                                                    ok = true;
                                                    return ;
                                                }
                                            }
                                        }
                                        else
                                            return;
                                    }
                                }
                            }
                        }
                        else if(num == "3")
                        {
                            cout << "Who was fouled?" << endl;
                            cin >> num;
                            for(int j = 0; j < teamA.getSize(); j++)
                            {
                                ok = false;
                                if(num == teamA.players[j].number)
                                {
                                    ok = true;
                                    if(teamA.players[j].st.freeThrowTaken()){teamA.tst.freeThrowMade();}
                                    if(teamA.players[j].st.freeThrowTaken()){teamA.tst.freeThrowMade();}
                                    if(teamA.players[j].st.freeThrowTaken() == true)
                                    {
                                        teamA.tst.freeThrowMade();
                                        teamA.tst.losePossession();
                                        teamB.tst.gainPossession();
                                        return ;
                                    }
                                    else
                                    {
                                        cout << "Which team got the rebound?" << endl;
                                        cout << "(1)" << teamA.getTeamName() << endl;
                                        cout << "(2)" << teamB.getTeamName() << endl;
                                        cout << "(n)one" << endl;
                                        cin >> num;
                                        if(num == "1")
                                        {
                                            cout << "Who exactly?" << endl;
                                            cin >> num;
                                            for(int j = 0; j < teamA.getSize(); j++)
                                            {
                                                if(teamA.players[j].number == num)
                                                {
                                                    teamA.players[j].st.rebound();
                                                    ok = true;
                                                    return ;
                                                }
                                            }
                                        }
                                        else if(num == "2")
                                        {
                                            cout << "Who exactly?" << endl;
                                            cin >> num;
                                            for(int j = 0; j < teamB.getSize(); j++)
                                            {
                                                if(teamB.players[j].number == num)
                                                {
                                                    teamB.players[j].st.rebound();
                                                    teamB.tst.gainPossession();
                                                    teamA.tst.losePossession();
                                                    ok = true;
                                                    return ;
                                                }
                                            }
                                        }
                                        else
                                            return;

                                    }
                                }
                            }
                        }
                        else if(num == "n")
                        {
                            if(teamB.tst.getFls() > 5)
                            {
                                cout << "Who was fouled?" << endl;
                                cin >> num;
                                for(int j = 0; j < teamA.getSize(); j++)
                                {
                                    ok = false;
                                    if(num == teamA.players[j].number)
                                    {
                                        ok = true;
                                        if(teamA.players[j].st.freeThrowTaken()){teamA.tst.freeThrowMade();}
                                        if(teamA.players[j].st.freeThrowTaken() == true)
                                        {
                                            teamA.tst.freeThrowMade();
                                            teamB.tst.gainPossession();
                                            teamA.tst.losePossession();
                                            return ;
                                        }
                                        else
                                        {
                                            cout << "Which team got the rebound?" << endl;
                                            cout << "(1)" << teamA.getTeamName() << endl;
                                            cout << "(2)" << teamB.getTeamName() << endl;
                                            cout << "(n)one" << endl;
                                            cin >> num;
                                            if(num == "1")
                                            {
                                                cout << "Who exactly?" << endl;
                                                cin >> num;
                                                for(int j = 0; j < teamA.getSize(); j++)
                                                {
                                                    if(teamA.players[j].number == num)
                                                    {
                                                        teamA.players[j].st.rebound();
                                                        ok = true;
                                                        return ;
                                                    }
                                                }
                                            }
                                            else if(num == "2")
                                            {
                                                cout << "Who exactly?" << endl;
                                                cin >> num;
                                                for(int j = 0; j < teamB.getSize(); j++)
                                                {
                                                    if(teamB.players[j].number == num)
                                                    {
                                                        teamB.players[j].st.rebound();
                                                        teamB.tst.gainPossession();
                                                        teamA.tst.losePossession();
                                                        ok = true;
                                                        return ;
                                                    }
                                                }
                                            }
                                            else
                                                return;
                                        }

                                    }
                                }
                            }
                        }
                    }
                }
            }

            else
            {
                cout << "Who commited a foul?" << endl;
                string num;
                cin >> num;
                for(int i = 0; i < teamA.getSize(); i++)
                {
                    if(num == teamA.players[i].number)
                    {
                        if(teamA.players[i].isActive == false)
                            throw "This player is on the bench!";
                        ok = true;
                        teamA.players[i].st.foul();
                        teamA.tst.foul();
                        if(teamA.players[i].st.getFls() >= 6)
                        {
                            teamA.players[i].isActive = false;
                            cout << teamA.players[i].getName() << " " << teamA.players[i].getSurname() << " fouled out! Choose a substitution" << endl;
                            cin >> num;
                            for(int j = 0; j < teamA.getSize(); j++)
                            {
                                if(num == teamA.players[j].number)
                                {
                                    if(teamA.players[j].isActive == true)
                                        throw "This player is already on the court!";
                                    if(teamA.players[j].st.getFls() >= 6)
                                        throw "This player is over the foul limit!";
                                    teamA.players[j].isActive = true;
                                    ok = true;
                                }
                            }
                        }
                        cout << "How many free throws should the player take?('n' if none)" << endl;
                        cin >> num;
                        if(num == "1")
                        {
                            cout << "Who was fouled?" << endl;
                            cin >> num;
                            for(int j = 0; j < teamB.getSize(); j++)
                            {
                                ok = false;
                                if(num == teamB.players[j].number)
                                {
                                    if(teamB.players[j].isActive == false)
                                        throw "This player is on the bench!";
                                    ok = true;
                                    if(teamB.players[j].st.freeThrowTaken() == true)
                                    {
                                        teamB.tst.freeThrowMade();
                                        teamA.tst.gainPossession();
                                        teamB.tst.losePossession();
                                        return ;
                                    }
                                    else
                                    {
                                        cout << "Which team got the rebound?" << endl;
                                        cout << "(1)" << teamB.getTeamName() << endl;
                                        cout << "(2)" << teamA.getTeamName() << endl;
                                        cout << "(n)one" << endl;
                                        cin >> num;
                                        if(num == "1")
                                        {
                                            cout << "Who exactly?" << endl;
                                            cin >> num;
                                            for(int j = 0; j < teamB.getSize(); j++)
                                            {
                                                if(teamB.players[j].number == num)
                                                {
                                                    teamB.players[j].st.rebound();
                                                    ok = true;
                                                    return ;
                                                }
                                            }
                                        }
                                        else if (num == "2")
                                        {
                                            cout << "Who exactly?" << endl;
                                            cin >> num;
                                            for(int j = 0; j < teamA.getSize(); j++)
                                            {
                                                if(teamA.players[j].number == num)
                                                {
                                                    teamA.players[j].st.rebound();
                                                    teamA.tst.gainPossession();
                                                    teamB.tst.losePossession();
                                                    ok = true;
                                                    return ;
                                                }
                                            }
                                        }
                                        else
                                            return;
                                    }
                                }
                            }
                        }
                        else if(num == "2")
                        {
                            cout << "Who was fouled?" << endl;
                            cin >> num;
                            for(int j = 0; j < teamB.getSize(); j++)
                            {
                                ok = false;
                                if(num == teamB.players[j].number)
                                {
                                    if(teamB.players[j].isActive == false)
                                        throw "This player is on the bench!";
                                    ok = true;
                                    if(teamB.players[j].st.freeThrowTaken()){teamB.tst.freeThrowMade();}
                                    if(teamB.players[j].st.freeThrowTaken() == true)
                                    {
                                        teamB.tst.freeThrowMade();
                                        teamA.tst.gainPossession();
                                        teamB.tst.losePossession();
                                        return ;
                                    }
                                    else
                                    {
                                        cout << "Which team got the rebound?" << endl;
                                        cout << "(1)" << teamB.getTeamName() << endl;
                                        cout << "(2)" << teamA.getTeamName() << endl;
                                        cout << "(n)one" << endl;
                                        cin >> num;
                                        if(num == "1")
                                        {
                                            cout << "Who exactly?" << endl;
                                            cin >> num;
                                            for(int j = 0; j < teamB.getSize(); j++)
                                            {
                                                if(teamB.players[j].number == num)
                                                {
                                                    teamB.players[j].st.rebound();
                                                    ok = true;
                                                    return ;
                                                }
                                            }
                                        }
                                        else if(num == "2")
                                        {
                                            cout << "Who exactly?" << endl;
                                            cin >> num;
                                            for(int j = 0; j < teamA.getSize(); j++)
                                            {
                                                if(teamA.players[j].number == num)
                                                {
                                                    teamA.players[j].st.rebound();
                                                    teamA.tst.gainPossession();
                                                    teamB.tst.losePossession();
                                                    ok = true;
                                                    return ;
                                                }
                                            }
                                        }
                                        else
                                            return ;
                                    }
                                }
                            }
                        }
                        if(num == "3")
                        {
                            cout << "Who was fouled?" << endl;
                            cin >> num;
                            for(int j = 0; j < teamB.getSize(); j++)
                            {
                                ok = false;
                                if(num == teamB.players[j].number)
                                {
                                    ok = true;
                                    if(teamB.players[j].st.freeThrowTaken()){teamB.tst.freeThrowMade();}
                                    if(teamB.players[j].st.freeThrowTaken()){teamB.tst.freeThrowMade();}
                                    if(teamB.players[j].st.freeThrowTaken() == true)
                                    {
                                        teamB.tst.freeThrowMade();
                                        teamB.tst.losePossession();
                                        teamA.tst.gainPossession();
                                        return ;
                                    }
                                    else
                                    {
                                        cout << "Which team got the rebound?" << endl;
                                        cout << "(1)" << teamB.getTeamName() << endl;
                                        cout << "(2)" << teamA.getTeamName() << endl;
                                        cout << "(n)one" << endl;
                                        cin >> num;
                                        if(num == "1")
                                        {
                                            cout << "Who exactly?" << endl;
                                            cin >> num;
                                            for(int j = 0; j < teamB.getSize(); j++)
                                            {
                                                if(teamB.players[j].number == num)
                                                {
                                                    teamB.players[j].st.rebound();
                                                    ok = true;
                                                    return ;
                                                }
                                            }
                                        }
                                        else if(num == "2")
                                        {
                                            cout << "Who exactly?" << endl;
                                            cin >> num;
                                            for(int j = 0; j < teamA.getSize(); j++)
                                            {
                                                if(teamA.players[j].number == num)
                                                {
                                                    teamA.players[j].st.rebound();
                                                    teamA.tst.gainPossession();
                                                    teamB.tst.losePossession();
                                                    ok = true;
                                                    return ;
                                                }
                                            }
                                        }
                                        else
                                            return;

                                    }
                                }
                            }
                        }
                        if(num == "n")
                        {
                            if(teamA.tst.getFls() > 5)
                            {
                                cout << "Who was fouled?" << endl;
                                cin >> num;
                                for(int j = 0; j < teamB.getSize(); j++)
                                {
                                    ok = false;
                                    if(num == teamB.players[j].number)
                                    {
                                        ok = true;
                                        if(teamB.players[j].st.freeThrowTaken()){teamB.tst.freeThrowMade();}
                                        if(teamB.players[j].st.freeThrowTaken() == true)
                                        {
                                            teamB.tst.freeThrowMade();
                                            teamA.tst.gainPossession();
                                            teamB.tst.losePossession();
                                            return ;
                                        }
                                        else
                                        {
                                            cout << "Which team got the rebound?" << endl;
                                            cout << "(1)" << teamB.getTeamName() << endl;
                                            cout << "(2)" << teamA.getTeamName() << endl;
                                            cout << "(n)one" << endl;
                                            cin >> num;
                                            if(num == "1")
                                            {
                                                cout << "Who exactly?" << endl;
                                                cin >> num;
                                                for(int j = 0; j < teamB.getSize(); j++)
                                                {
                                                    if(teamB.players[j].number == num)
                                                    {
                                                        teamB.players[j].st.rebound();
                                                        ok = true;
                                                        return ;
                                                    }
                                                }
                                            }
                                            else if(num == "2")
                                            {
                                                cout << "Who exactly?" << endl;
                                                cin >> num;
                                                for(int j = 0; j < teamA.getSize(); j++)
                                                {
                                                    if(teamA.players[j].number == num)
                                                    {
                                                        teamA.players[j].st.rebound();
                                                        teamA.tst.gainPossession();
                                                        teamB.tst.losePossession();
                                                        ok = true;
                                                        return ;
                                                    }
                                                }
                                            }
                                            else
                                                return;
                                        }

                                    }
                                }
                            }
                        }
                    }
                }
            }
            if(ok == false)
                throw "There is no player with that number";
        }
        catch(char const* a)
        {
            cout << a << endl;
            whatToDo(action);
        }
    }
    if(action == "of")
    {
        try
        {
            bool ok = false;
            //if teamA has the ball
            if(teamA.tst.getPossession() == true)
            {
                string num;
                cout << "Who commited a foul?" << endl;
                cin >> num;
                for(int i = 0; i < teamA.getSize(); i++)
                {
                    if(num == teamA.players[i].number)
                    {
                        if(teamA.players[i].isActive == false)
                            throw "This player is on the bench!";
                        ok = true;
                        teamA.players[i].st.foul();
                        teamA.players[i].st.turnover();
                        teamA.tst.losePossession();
                        teamB.tst.gainPossession();
                        if(teamA.players[i].st.getFls() >= 6)
                        {
                            teamA.players[i].isActive = false;
                            cout << teamA.players[i].getName() << " " << teamA.players[i].getSurname() << " fouled out! Choose a substitution" << endl;
                            cin >> num;
                            for(int j = 0; j < teamA.getSize(); j++)
                            {
                                if(num == teamA.players[j].number)
                                {
                                    if(teamA.players[j].isActive == true)
                                        throw "This player is already on the court!";
                                    if(teamA.players[j].st.getFls() >= 6)
                                        throw "This player is over the foul limit!";
                                    teamA.players[j].isActive = true;
                                    ok = true;
                                    return ;
                                }
                            }
                        }
                        return ;
                    }
                }
            }
            else
            {
                string num;
                cout << "Who commited a foul?" << endl;
                cin >> num;
                for(int i = 0; i < teamB.getSize(); i++)
                {
                    if(num == teamB.players[i].number)
                    {
                        if(teamB.players[i].isActive == false)
                            throw "This player is on the bench!";
                        ok = true;
                        teamB.players[i].st.foul();
                        teamB.players[i].st.turnover();
                        teamB.tst.losePossession();
                        teamA.tst.gainPossession();
                        if(teamB.players[i].st.getFls() >= 6)
                        {
                            teamB.players[i].isActive = false;
                            cout << teamB.players[i].getName() << " " << teamB.players[i].getSurname() << " fouled out! Choose a substitution" << endl;
                            cin >> num;
                            for(int j = 0; j < teamB.getSize(); j++)
                            {
                                if(num == teamB.players[j].number)
                                {
                                    if(teamB.players[j].isActive == true)
                                        throw "This player is already on the court!";
                                    if(teamB.players[j].st.getFls() >= 6)
                                        throw "This player is over the foul limit!";
                                    teamB.players[j].isActive = true;
                                    ok = true;
                                    return ;
                                }
                            }
                        }
                        return ;
                    }
                }
            }
            if(ok == false)
                throw "There is no player with that number";
        }
        catch(const char* a)
        {
            cout << a << endl;
            whatToDo(action);
        }
    }
    if(action == "stl")
    {
        try
        {
            bool ok = false;
            //teamA has the ball
            if(teamA.tst.getPossession() == true)
            {
                string num;
                cout << "Who turned the ball over?" << endl;
                cin >> num;
                for(int i = 0; i < teamA.getSize(); i++)
                {
                    if(num == teamA.players[i].number)
                    {
                        ok = true;
                        if(teamA.players[i].isActive == false)
                            throw "This player is on the bench!";
                        teamA.players[i].st.turnover();
                        teamA.tst.losePossession();
                        teamB.tst.gainPossession();
                        cout << "Who stole the ball?" << endl;
                        cin >> num;
                        for(int j = 0; j < teamB.getSize(); j++)
                        {
                            ok = false;
                            if(teamB.players[j].number == num)
                            {
                                ok = true;
                                if(teamB.players[j].isActive == false)
                                    throw "This player is on the bench!";
                                teamB.players[j].st.steal();
                                return ;
                            }
                        }
                    }
                }
            }
            else
            {
                string num;
                cout << "Who turned the ball over?" << endl;
                cin >> num;
                for(int i = 0; i < teamB.getSize(); i++)
                {
                    if(num == teamB.players[i].number)
                    {
                        ok = true;
                        if(teamB.players[i].isActive == false)
                            throw "This player is on the bench!";
                        teamB.players[i].st.turnover();
                        teamB.tst.losePossession();
                        teamA.tst.gainPossession();
                        cout << "Who stole the ball?" << endl;
                        cin >> num;
                        for(int j = 0; j < teamA.getSize(); j++)
                        {
                            ok = false;
                            if(teamA.players[j].number == num)
                            {
                                ok = true;
                                if(teamA.players[j].isActive == false)
                                    throw "This player is on the bench!";
                                teamA.players[j].st.steal();
                                return ;
                            }
                        }
                    }
                }
            }
            if(ok == false)
                throw "There is no player with that number";
        }
        catch(const char *a)
        {
            cout << a << endl;
            whatToDo(action);
        }
    }
    if(action == "to")
    {
        bool ok = false;
        try
        {
            if(teamA.tst.getPossession() == true)
            {
                string num;
                cout << "Who turned it over?" << endl;
                cin >> num;
                for(int i = 0; i < teamA.getSize(); i++)
                {
                    if(num == teamA.players[i].number)
                    {
                        if(teamA.players[i].isActive == false)
                            throw "This player is on the bench!";
                        ok = true;
                        teamA.players[i].st.turnover();
                        teamA.tst.losePossession();
                        teamB.tst.gainPossession();
                    }
                }
            }
            else
            {
                string num;
                cout << "Who turned it over?" << endl;
                cin >> num;
                for(int i = 0; i < teamB.getSize(); i++)
                {
                    if(num == teamB.players[i].number)
                    {
                        if(teamB.players[i].isActive == false)
                            throw "This player is on the bench!";
                        ok = true;
                        teamB.players[i].st.turnover();
                        teamB.tst.losePossession();
                        teamA.tst.gainPossession();
                    }
                }
            }
            if(ok == false)
                throw "There is no player with that number";
        }
        catch(const char *a)
        {
            cout << a << endl;
            whatToDo(action);
        }
    }
    if(action == "sub")
    {
        bool ok = false;
        try
        {
            cout << "Which team wants a substitution?" << endl;
            cout << "(1)" << teamA.getTeamName() << endl;
            cout << "(2)" << teamB.getTeamName() << endl;
            string num;
            cin >> num;
            if(num == "1")
            {
                cout << "Which player do you want to substitute?" << endl;
                cin >> num;
                for(int i = 0; i < teamA.getSize(); i++)
                {
                    if(num == teamA.players[i].number)
                    {
                        if(teamA.players[i].isActive == false)
                            throw "This player is on the bench!";
                        teamA.players[i].isActive = false;
                        ok = true;
                    }
                }
                if(ok == false)
                        throw "There is no player with that number";
                cout << "Which player do you want to bring in?" << endl;
                cin >> num;
                ok = false;
                for(int i = 0; i < teamA.getSize(); i++)
                {
                    if(num == teamA.players[i].number)
                    {
                        if(teamA.players[i].isActive == true)
                            throw "This player is already on the court!";
                        if(teamA.players[i].st.getFls() >= 6)
                            throw "This player is over the foul limit!";
                        teamA.players[i].isActive = true;
                        ok = true;
                    }
                }
                if(ok == false)
                        throw "There is no player with that number";
            }
            else
            {
                cout << "Which player do you want to substitute?" << endl;
                cin >> num;
                for(int i = 0; i < teamB.getSize(); i++)
                {
                    if(num == teamB.players[i].number)
                    {
                        if(teamB.players[i].isActive == false)
                            throw "This player is on the bench!";
                        teamB.players[i].isActive = false;
                        ok = true;
                    }
                }
                if(ok == false)
                        throw "There is no player with that number";
                cout << "Which player do you want to bring in?" << endl;
                cin >> num;
                ok = false;
                for(int i = 0; i < teamB.getSize(); i++)
                {
                    if(num == teamB.players[i].number)
                    {
                        if(teamB.players[i].isActive == true)
                            throw "This player is already on the court!";
                        if(teamB.players[i].st.getFls() >=6)
                            throw "This player is over the foul limit!";
                        teamB.players[i].isActive = true;
                        ok = true;
                    }
                }
                if(ok == false)
                        throw "There is no player with that number";
            }

        }
        catch(const char* a)
        {
            cout << a << endl;
            whatToDo(action);
        }
    }
    if(action == "blk")
    {
        try
        {
            bool ok = false;
            if(teamA.tst.getPossession() == true)
            {
                string num;
                cout << "Which player blocked a shot?" << endl;
                cin >> num;
                for(int i = 0; i < teamB.getSize(); i++)
                {
                    if(num == teamB.players[i].number)
                    {
                        if(teamB.players[i].isActive == false)
                            throw "This player is on the bench!";
                        teamB.players[i].st.block();
                        cout << "Which team got the rebound?" << endl;
                        cout << "(1)" << teamA.getTeamName() << endl;
                        cout << "(2)" << teamB.getTeamName() << endl;
                        cout << "(n)one" << endl;
                        cin >> num;
                        if(num == "1")
                        {
                            cout << "Who exactly?" << endl;
                            cin >> num;
                            for(int j = 0; j < teamA.getSize(); j++)
                            {
                                if(teamA.players[j].number == num)
                                {
                                    teamA.players[j].st.rebound();
                                    teamA.tst.gainPossession();
                                    teamB.tst.losePossession();
                                    ok = true;
                                    return ;
                                }
                            }
                        }
                        else if(num == "2")
                        {
                            cout << "Who exactly?" << endl;
                            cin >> num;
                            for(int j = 0; j < teamB.getSize(); j++)
                            {
                                if(teamB.players[j].number == num)
                                {
                                    teamB.players[j].st.rebound();
                                    teamB.tst.gainPossession();
                                    teamA.tst.losePossession();
                                    ok = true;
                                    return ;
                                }
                            }


                        }
                        return;
                    }
                }
            }
            else
            {
                string num;
                cout << "Which player blocked a shot?" << endl;
                cin >> num;
                for(int i = 0; i < teamA.getSize(); i++)
                {
                    if(num == teamA.players[i].number)
                    {
                        if(teamA.players[i].isActive == false)
                            throw "This player is on the bench!";
                        teamA.players[i].st.block();
                        cout << "Which team got the rebound?" << endl;
                        cout << "(1)" << teamB.getTeamName() << endl;
                        cout << "(2)" << teamA.getTeamName() << endl;
                        cout << "(n)one" << endl;
                        cin >> num;
                        if(num == "1")
                        {
                            cout << "Who exactly?" << endl;
                            cin >> num;
                            for(int j = 0; j < teamB.getSize(); j++)
                            {
                                if(teamB.players[j].number == num)
                                {
                                    teamB.players[j].st.rebound();
                                    teamB.tst.gainPossession();
                                    teamA.tst.losePossession();
                                    ok = true;
                                    return ;
                                }
                            }
                        }
                        else if(num == "2")
                        {
                            cout << "Who exactly?" << endl;
                            cin >> num;
                            for(int j = 0; j < teamA.getSize(); j++)
                            {
                                if(teamA.players[j].number == num)
                                {
                                    teamA.players[j].st.rebound();
                                    teamA.tst.gainPossession();
                                    teamB.tst.losePossession();
                                    ok = true;
                                    return ;
                                }
                            }


                        }
                        return;
                    }
                }
            }

        }
        catch(const char* a)
        {
            cout << a << endl;
            whatToDo(action);
        }
    }
    if(action == "end")
    {
        quarter++;
        teamA.tst.resetFouls();
        teamB.tst.resetFouls();
    }
    if(action == "switch")
    {
        if(teamA.tst.getPossession() == true)
        {
            teamB.tst.gainPossession();
            teamA.tst.losePossession();
        }
        else
        {
            teamB.tst.losePossession();
            teamA.tst.gainPossession();
        }
    }
}

