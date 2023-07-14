#ifndef LISTPLAYER_H
#define LISTPLAYER_H

#include <QObject>
#include <QAbstractListModel>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QVector>
#include <QDebug>
#include <QtCore>
#include <QtXml>
#include "player.h"

class ListPlayer : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ListPlayer(QQmlApplicationEngine *m_engine,QObject *parent = nullptr);
    ~ListPlayer();

    enum PlayerRoles{
        NameRole = Qt::UserRole + 1,
        WinRole,
        LoseRole,
        DrawRole
    };

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    QHash<int, QByteArray> roleNames() const override;

    void appendNewPlayer(const QString &newPlayerName);

    void setWin(const QString &nameWinner);
    void setLose(const QString &nameLoser);
    void setDraw(const QString &name1, const QString &name2);
    void sortPlayer();

    void readFileXML();
    void writeFileXML();
signals:

private:
    QVector<Player> listPlayer;
    QQmlApplicationEngine *engine;

    QString fileName;

};

#endif // LISTPLAYER_H
