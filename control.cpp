#include "control.h"

Control::Control(QObject *parent) : QObject(parent)
{
    currentTurn = 0;
}

void Control::reset()
{
    boardGame->reset();
}

QString Control::getTurn(const int &x, const int &y)
{
    return boardGame->getBoardState(x,y);
}

void Control::makeStep(const int &x, const int &y)
{
    bool isAdded = 0;
    if(currentTurn == 0)
    {
        isAdded = boardGame.setState(x,y,player1.getType());
        qDebug()<< "Added an new step X at position: "<< x<< ","<< y;
    }
    else{
        isAdded = boardGame.setState(x,y,player2.getType());
        qDebug()<< "Added an new step O at position: "<< x<< ","<< y;
    }
    if(isAdded)
    {
        currentTurn = !currentTurn;
    }
}
