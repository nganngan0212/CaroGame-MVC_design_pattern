#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <QDebug>
#include "player.h"
#include "board.h"

class Control : public QObject
{
    Q_OBJECT
public:
    explicit Control(QObject *parent = nullptr);
    Q_INVOKABLE void reset();
    Q_INVOKABLE QString getTurn(const int &x, const int &y);


signals:
    void newStep(const int &x, const int &y);
    void isWin(const int &x, const int &y);

public slots:
    void makeStep(const int &x, const int &y);

private:
    Board *boardGame;
    Player *player;
    bool currentTurn;
};

#endif // CONTROL_H
