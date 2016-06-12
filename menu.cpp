#include <iostream>
#include "menu.h"
#include "game.h"


using namespace std;

void controls()
{
    system("clear");
    int a;
    cout << "In order to modify statistics, you need to type in one of these commands: " << endl;
    cout << "'2p' - a two point shot was taken by a team that has possession of the ball. You will be asked about a shooter, whether he made the shot or not, ";
    cout << "and if neccessary: an assist man or a rebounder";
    cout << endl;
    cout << "'3p' - a three point shot was taken by a team that has possession of the ball. You will be asked about a shooter, whether he made the shot or not, ";
    cout << "and if neccessary: an assist man or a rebounder";
    cout << endl;
    cout << "'df' - a defensive foul occured. You will be asked who committed it, whether it was a shooting situation or not and if so, who was fouled";
    cout << endl;
    cout << "'of' - an offensive foul occured. You will be asked who commited it";
    cout << endl;
    cout << "'to' - a turnover occured. You will be asked who commited it";
    cout << endl;
    cout << "'stl' - a steal occured. You will be asked who turned the ball over and who stole it";
    cout << endl;
    cout << endl;
    cout << "Press enter to go back";
    a = getchar();
    a = getchar();

}
void mainMenu()
{
    int choice;

    while(1)
    {
        system("clear");
        cout << "(1)Start new game" << endl;
        cout << "(2)View controls" << endl;
        cout << "(3)View all teams" << endl;
        cout << "(4)Exit" << endl;
        choice = getchar();
        switch(choice)
        {
            case '1':
            {
                Game g;
                g.selectTeams();
                break;
            }
            case '2':
            {
                controls();
                break;
            }
            case '3':
            {
                Database d;
                d.downloadData();
                showTeams(d);
                break;
            }
            case '4':
            {
                return ;
                break;
            }
        }
    }
}


