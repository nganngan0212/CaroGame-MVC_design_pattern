#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "model.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QQmlApplicationEngine *m_engine, QObject *parent = nullptr);
    ~Controller();

    Q_PROPERTY(QString sourceScreen READ sourceScreen WRITE setSourceScreen NOTIFY sourceScreenChanged)

    Q_INVOKABLE void addPlayer(const QString &namePlayer1, const QString &namePlayer2);
    Q_INVOKABLE void setStep(const int &index);
//    Q_INVOKABLE void resetGameBoard();
    Q_INVOKABLE QString getText(const int &index);
    Q_INVOKABLE void resetGameBoard();
    Q_INVOKABLE void setWinner(const QString &winType, const QString &namePlayerX, const QString &namePlayerY);

    Q_INVOKABLE QString checkValidName_user1(const QString &inName);
    Q_INVOKABLE QString checkValidName_user2(const QString &inName);

    Q_INVOKABLE void replayGame();

    Q_INVOKABLE void switchToViewPlayer();
    Q_INVOKABLE void switchToBoardGame();
    Q_INVOKABLE void switchToSignIn();

    const QString &sourceScreen() const;
    void setSourceScreen(const QString &newSourceScreen);

signals:
    QString winnerSignal(QString win_type);
    void drawSignal(QString str);

    void sourceScreenChanged();

public slots:
    QString getWinner(QString name); // connect to Model::annouceWin
private:
    Model *myModel;
    QQmlApplicationEngine *engine;

    bool isEndGame;
    QString m_sourceScreen;
};

#endif // CONTROLLER_H
