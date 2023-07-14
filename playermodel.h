#ifndef PLAYERMODEL_H
#define PLAYERMODEL_H

#include <QObject>
#include <QAbstractListModel>

class PlayerModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PlayerModel(QObject *parent = nullptr): QAbstractListModel(parent);

signals:

private:


};

#endif // PLAYERMODEL_H
