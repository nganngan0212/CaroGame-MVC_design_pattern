#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player
{
public:
    explicit Player(QString name = "", int numWin = 0, int numLose = 0, int numDraw = 0);
    Player(const Player &t);

    QString getName() const;
    bool setName(const QString &in_name);

    void addNumWin();
    int getNumWin() const;

    void addNumLose();
    int getNumLose() const;

    void addNumDraw();
    int getNumDraw() const;

    void setNumWin(const int &in_win);
    void setNumLose(const int &in_lose);
    void setNumDraw(const int &in_draw);

signals:

public slots:

private:
    QString p_name;
    int numWin;
    int numLose;
    int numDraw;
};

#endif // PLAYER_H
