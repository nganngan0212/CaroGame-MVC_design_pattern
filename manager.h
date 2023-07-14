#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "player.h"

class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QObject *parent = nullptr);

signals:

private:

    Player player1;
    Player player2;
};

#endif // MANAGER_H
