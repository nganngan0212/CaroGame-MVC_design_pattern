#include "player.h"

Player::Player(QString name, int in_numWin, int in_numLose, int in_numDraw)
{
    p_name = name;
    numWin = in_numWin;
    numLose = in_numLose;
    numDraw = in_numDraw;
}

Player::Player(const Player &t)
{
    p_name = t.getName();
    numWin = t.getNumWin();
    numLose = t.getNumLose();
    numDraw = t.getNumDraw();
}

QString Player::getName() const
{
    return p_name;
}

bool Player::setName(const QString &name)
{
    if(p_name == name){
        return false;
    }
    p_name = name;
    return true;
}

void Player::addNumWin()
{
    numWin++;
}

int Player::getNumWin() const
{
    return numWin;
}

void Player::addNumLose()
{
    numLose ++;
}

int Player::getNumLose() const
{
    return numLose;
}

void Player::addNumDraw()
{
    numDraw ++;
}

int Player::getNumDraw() const
{
    return numDraw;
}

void Player::setNumWin(const int &in_win)
{
    numWin = in_win;
}

void Player::setNumLose(const int &in_lose)
{
    numLose = in_lose;
}

void Player::setNumDraw(const int &in_draw)
{
    numDraw = in_draw;
}





