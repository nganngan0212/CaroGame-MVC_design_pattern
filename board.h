#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QAbstractListModel>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <cmath>

class Position{

public:

    explicit Position(QString s = ""): p_state(s){
    }

    bool setState(const QString &state)
    {
        if(p_state == "X" || p_state== "O")
        {
            return false;
        }
        p_state = state;
        return true;
    }
    QString setReset(){
        p_state = "";
        return p_state;
    }
    QString getState() const
    {
        return p_state;
    }
private:
    QString p_state;
    // int state
};

class Board : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit Board(QQmlApplicationEngine *m_engine,QObject *parent = nullptr);

    ~Board();
    const static int dimension = 10;

    enum BoardRoles{
        DisplayTypeRole = Qt::UserRole + 1
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    QHash<int, QByteArray> roleNames() const override;

    bool setBoardState(const int &index, const QString &displayType);
    QString getBoardState(const int &index);
    void reset();
    bool checkWin(const int &index);
    void createNewBoard();
    bool isFullBoard();
    void replayStep(const int &pos, const QString &type);

signals:
    void newStepChanged(bool isDone = false);
    void returnWin(QString type);


private:
//    QList<Position> boardGame;

    Position boardGame[dimension*dimension];
    QQmlApplicationEngine *engine;
};

#endif // BOARD_H
