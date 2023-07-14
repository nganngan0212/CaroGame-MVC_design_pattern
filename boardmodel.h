#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QObject>
#include <QAbstractListModel>

class BoardModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit BoardModel(QObject *parent = nullptr): QAbstractListModel(parent);

signals:

};

#endif // BOARDMODEL_H
