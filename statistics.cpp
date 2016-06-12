#include "statistics.h"
#include <iostream>

using namespace std;

Stats :: Stats()
{
    pts = 0;
    rbs = 0;
    ast = 0;
    fls = 0;
    blks = 0;
    stls = 0;
    tos = 0;
    fgm = 0;
    fga = 0;
    tpm = 0;
    tpa = 0;
    ftm = 0;
    fta = 0;
}
int Stats :: getPts()
{
    return pts;
}
int Stats :: getRbs()
{
    return rbs;
}
int Stats :: getAst()
{
    return ast;
}
int Stats :: getFls()
{
    return fls;
}
int Stats :: getBlks()
{
    return blks;
}
int Stats :: getStls()
{
    return stls;
}
int Stats :: getTos()
{
    return tos;
}
int Stats :: getFgm()
{
    return fgm;
}
int Stats :: getFga()
{
    return fga;
}
int Stats :: getTpm()
{
    return tpm;
}
int Stats :: getTpa()
{
    return tpa;
}
int Stats :: getFtm()
{
    return ftm;
}
int Stats :: getFta()
{
    return fta;
}
double Stats :: getFgPrct()
{
    double percentage = 0;
    if(fga != 0)
        percentage = (double)fgm / (double)fga * 100.0;

    return percentage;
}
double Stats :: getTpPrct()
{
    double percentage = 0;
    if(tpa != 0)
        percentage = (double)tpm / (double)tpa * 100.0;

    return percentage;
}
double Stats :: getFtPrct()
{
    double percentage = 0;
    if(fta != 0)
        percentage = (double)ftm / (double)fta * 100.0;

    return percentage;
}
bool Stats :: twoPointShotTaken()
{
    char isMade;
    cout << "Is it made?" << endl;
    isMade = getchar();
    isMade = getchar();

    if(isMade == 'y')
    {
        fgm++;
        fga++;
        pts += 2;
        return true;
    }
    else
    {
        fga++;
        return false;
    }
}

bool Stats :: threePointShotTaken()
{
    char isMade;
    cout << "Is it made?" << endl;
    isMade = getchar();
    isMade = getchar();

    if(isMade == 'y')
    {
        fgm++;
        fga++;
        tpm++;
        tpa++;
        pts += 3;
        return true;
    }
    else
    {
        tpa++;
        fga++;
        return false;
    }
}
bool Stats :: freeThrowTaken()
{
    char isMade;
    cout << "Is it made?" << endl;
    isMade = getchar();
    isMade = getchar();
    if(isMade == 'y')
    {
        ftm++;
        fta++;
        pts++;
        return true;
    }
    else
    {
        fta++;
        return false;
    }
}

void Stats :: rebound()
{
    rbs++;
}
void Stats :: assist()
{
    ast++;
}
void Stats :: foul()
{
    fls++;
}
void Stats :: turnover()
{
    tos++;
}
void Stats :: steal()
{
    stls++;
}
void Stats :: block()
{
    blks++;
}

TeamStats :: TeamStats()
{
    pts = 0;
    rbs = 0;
    ast = 0;
    fls = 0;
    blks = 0;
    stls = 0;
    tos = 0;
    fgm = 0;
    fga = 0;
    tpm = 0;
    tpa = 0;
    ftm = 0;
    fta = 0;
    possession = false;
}
bool TeamStats :: getPossession()
{
    return possession;
}
void TeamStats :: gainPossession()
{
    possession = true;
}
void TeamStats :: losePossession()
{
    possession = false;
}
void TeamStats :: twoPointShotMade()
{
    pts += 2;
}
void TeamStats :: threePointShotMade()
{
    pts += 3;
}
void TeamStats :: freeThrowMade()
{
    pts++;
}
void TeamStats :: resetFouls()
{
    fls = 0;
}


