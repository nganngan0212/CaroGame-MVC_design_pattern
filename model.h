#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QTimer>
#include "board.h"
#include "listplayer.h"

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QQmlApplicationEngine *m_engine,QObject *parent = nullptr);
    ~Model();

    Q_INVOKABLE void inGamePlayer(const QString &player1, const QString &player2);
    Q_INVOKABLE void makeStep(const int &index);

    Q_INVOKABLE void resetBoard();

    Q_INVOKABLE QString getCurrentType() const;
    QString getDisplayType(int index) const;
    void setWinGame(const QString &winType, const QString &namePlayerX, const QString &namePlayerY);

    void appendSaveBoard(const int &position, const QString &state);
    void replaySaveBoard();
    void resetSaveBoard(); // when call reset() fcn

signals:
    void annouceWinner(QString type);

public slots:
    void makedNewStep(bool newStepIsDone);
    void getWinnerType(QString type); //connect to myGameBoard::SIGNAL(returnWin(QString))

private:
    Board *myGameBoard;
    ListPlayer *myListPlayer;
    QQmlApplicationEngine *engine;

    bool currentTurn;
    Player* player1;
    Player* player2;

    QMap<int,QString> saveBoard;
};

#endif // MODEL_H
