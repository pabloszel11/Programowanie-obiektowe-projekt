#include <iostream>
#ifndef STATISTICS_H
#define STATISTICS_H

using namespace std;


class Stats
{
protected:
    int pts,rbs,ast,fls,blks,stls,tos,fgm,fga,tpm,tpa,ftm,fta;
    /*
    * pts - points
    * rbs - rebounds
    * ast - assists
    * fls - fouls
    * blks - blocks
    * stls - steals
    * tos - turnovers
    * fgm - field goals made
    * fga - field goals attempted
    * tpm - three pointers made
    * tpa - three pointers attempted
    * ftm - free throws made
    * fta - free throws attempted
    */
public:
    Stats();
    //getters
    int getPts();
    int getRbs();
    int getAst();
    int getFls();
    int getBlks();
    int getStls();
    int getTos();
    int getFgm();
    int getFga();
    int getTpm();
    int getTpa();
    int getFta();
    int getFtm();
    double getFgPrct();
    double getTpPrct();
    double getFtPrct();

    //stat modifiers
    bool twoPointShotTaken();
    bool threePointShotTaken();
    void rebound();
    void turnover();
    void steal();
    void assist();
    void foul();
    void block();
    bool freeThrowTaken();

};

class TeamStats : public Stats
{
    bool possession;

public:
    TeamStats();
    bool getPossession();
    void gainPossession();
    void losePossession();
    void twoPointShotMade();
    void threePointShotMade();
    void freeThrowMade();
    void resetFouls();
};

#endif
