#include "board.h"
#include <QDebug>

Board::Board(QQmlApplicationEngine *m_engine, QObject *parent) : QAbstractListModel(parent)
{
    engine = m_engine;

    engine->rootContext()->setContextProperty("MyGameBoard",this);
}

Board::~Board()
{

}

int Board::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
//    qDebug()<< "Row Count"<< boardGame.size();
//    return boardGame.size();
    return dimension*dimension;
}

QVariant Board::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }

    const Position &item = boardGame[index.row()];

    switch (role) {

    case DisplayTypeRole:
        return item.getState();

    default:
        return QVariant();
    }
}

bool Board::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
    {
        return false;
    }

    switch (role) {

    case DisplayTypeRole:
    {
        boardGame[index.row()].setState(value.toString());
        return true;
    }
    default:
        return false;
    }
}

QHash<int, QByteArray> Board::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DisplayTypeRole] = "displayType";

    return roles;
}


void Board::createNewBoard()
{
    for(int i=0; i<(dimension*dimension); i++)
    {
        beginInsertRows(QModelIndex(),rowCount(),rowCount());
        boardGame[i] = Position("");

//        qDebug()<< "Created new cell"<< i;
        endInsertRows();
    }
}

bool Board::isFullBoard()
{
    for(int i=0; i<(dimension*dimension); i++)
    {
        if(boardGame[i].getState() != "X" || boardGame[i].getState() != "O")
        {
            return false;
        }
    }
    return true;
}

void Board::replayStep(const int &pos, const QString &type)
{
    boardGame[pos].setState(type);
}

bool Board::setBoardState(const int &index, const QString &displayType)
{
    if(boardGame[index].getState() != "")
    {
        return false;
    }
    else{
        boardGame[index].setState(displayType);
        qDebug()<< "In Board::setBoardState()"<< displayType;
        emit newStepChanged(true);
        if(checkWin(index))
        {
            // emit signal for winner
            qDebug()<< "Emit signal for winner";
            emit returnWin(displayType);
        }
        if(isFullBoard())
        {
            emit returnWin("");
        }
        return true;
    }
}

QString Board::getBoardState(const int &index)
{
    return boardGame[index].getState();
}

void Board::reset()
{
//    qDebug() << "Size of QList::boardGame" << boardGame.size();

    beginResetModel();  // Bắt đầu đặt lại mô hình
//    boardGame.clear();  // Xóa tất cả các phần tử trong boardGame
    createNewBoard();   // Tạo lại bảng

    endResetModel();    // Kết thúc đặt lại mô hình

}

bool Board::checkWin(const int &index)
{
    qDebug()<< "In Board::checkWin() function";
    qDebug()<< "Checking at position "<< index;

    const int row = std::floor(index/dimension); // 0 to 9
    const int col = index%dimension;

    QString thisType = boardGame[index].getState();
    QString otherType;

    if(thisType == "X")
    {
        otherType = "O";
    }
    if(thisType == "O")
    {
        otherType = "X";
    }

    // tim theo chieu ngang
    int count = 0;
    bool left = false;
    bool right = false;
    int s_row = row;
    int s_col = col;
//    qDebug()<< "Checking through horizontial";
    while (s_col<(dimension-1) && !right) {
        s_col = s_col+1;
        int currentIdx = (s_row*dimension)+s_col;
//        qDebug()<< "Checking at "<< currentIdx;
        if(boardGame[currentIdx].getState() == "")
        {
            break;
        }
        if(boardGame[currentIdx].getState()==thisType && currentIdx != index)
        {
            count++;
            continue;
        }
        if(boardGame[currentIdx].getState()==otherType)
        {
            right = true;
            break;
        }
    }
    s_row = row;
    s_col = col;
    while (s_col>0 && !left) {
        s_col = s_col-1;
        int currentIdx = (s_row*dimension)+s_col;
//        qDebug()<< "Checking at "<< currentIdx;
        if(boardGame[currentIdx].getState() == "")
        {
            break;
        }
        if(boardGame[currentIdx].getState()==thisType && currentIdx != index)
        {
            count++;
            continue;
        }
        if(boardGame[currentIdx].getState()==otherType)
        {
            right = true;
            break;
        }
    }

//    qDebug()<< "Count "<< count<< "left blocked "<< left<< "rigth blocked "<< right;

    if(count==4 && (!left || !right))
    {
        return true;
    }
    if(count==3 && !left && !right)
    {
        return true;
    }

    // tim theo chieu doc
    count = 0;
    left = false;
    right = false;
    s_row = row;
    s_col = col;
//    qDebug()<< "Checking through vertical";
    while (s_row<(dimension-1) && !right) {
        s_row = s_row+1;
        int currentIdx = (s_row*dimension)+s_col;
//        qDebug()<< "Checking at "<< currentIdx;
        if(boardGame[currentIdx].getState() == "")
        {
            break;
        }
        if(boardGame[currentIdx].getState()==thisType && currentIdx != index)
        {
            count++;
            continue;
        }
        if(boardGame[currentIdx].getState()==otherType)
        {
            right = true;
            break;
        }
    }
    s_row = row;
    s_col = col;
    while (s_row>0 && !left) {
        s_row = s_row-1;
        int currentIdx = (s_row*dimension)+s_col;
//        qDebug()<< "Checking at "<< currentIdx;
        if(boardGame[currentIdx].getState() == "")
        {
            break;
        }
        if(boardGame[currentIdx].getState()==thisType && currentIdx != index)
        {
            count++;
            continue;
        }
        if(boardGame[currentIdx].getState()==otherType)
        {
            right = true;
            break;
        }
    }

//    qDebug()<< "Count "<< count<< "left blocked "<< left<< "rigth blocked "<< right;

    if(count==4 && (!left || !right))
    {
        return true;
    }
    if(count==3 && !left && !right)
    {
        return true;
    }

    // tim theo cheo phai
    count = 0;
    left = false;
    right = false;
    s_row = row;
    s_col = col;
//    qDebug()<< "Checking through secondary diagonal";
    while (s_col<(dimension-1) && s_row>0 && !right) {
        s_row = s_row-1;
        s_col = s_col+1;
        int currentIdx = (s_row*dimension)+s_col;
//        qDebug()<< "Checking at "<< currentIdx;
        if(boardGame[currentIdx].getState() == "")
        {
            break;
        }
        if(boardGame[currentIdx].getState()==thisType && currentIdx != index)
        {
            count++;
            continue;
        }
        if(boardGame[currentIdx].getState()==otherType)
        {
            right = true;
            break;
        }
    }
    s_row = row;
    s_col = col;
    while (s_col>0 && s_row<(dimension-1) && !left) {
        s_row = s_row+1;
        s_col = s_col-1;
        int currentIdx = (s_row*10)+s_col;
//        qDebug()<< "Checking at "<< currentIdx;
        if(boardGame[currentIdx].getState() == "")
        {
            break;
        }
        if(boardGame[currentIdx].getState()==thisType && currentIdx != index)
        {
            count++;
            continue;
        }
        if(boardGame[currentIdx].getState()==otherType)
        {
            right = true;
            break;
        }
    }

//    qDebug()<< "Count "<< count<< "left blocked "<< left<< "rigth blocked "<< right;

    if(count==4 && (!left || !right))
    {
        return true;
    }
    if(count==3 && !left && !right)
    {
        return true;
    }

    // tim theo cheo trai
    count = 0;
    left = false;
    right = false;
    s_row = row;
    s_col = col;
//    qDebug()<< "Checking through main diagonal";
    while (s_col>0 && s_row>0 && !right) {
        s_row = s_row-1;
        s_col = s_col-1;
        int currentIdx = (s_row*dimension)+s_col;
//        qDebug()<< "Checking at "<< currentIdx;
        if(boardGame[currentIdx].getState() == "")
        {
            break;
        }
        if(boardGame[currentIdx].getState()==thisType && currentIdx != index)
        {
            count++;
            continue;
        }
        if(boardGame[currentIdx].getState()==otherType)
        {
            right = true;
            break;
        }
    }
    s_row = row;
    s_col = col;
    while (s_col<(dimension-1) && s_row<(dimension-1) && !left) {
        s_row = s_row+1;
        s_col = s_col+1;
        int currentIdx = (s_row*dimension)+s_col;
//        qDebug()<< "Checking at "<< currentIdx;
        if(boardGame[currentIdx].getState() == "")
        {
            break;
        }
        if(boardGame[currentIdx].getState()==thisType && currentIdx != index)
        {
            count++;
            continue;
        }
        if(boardGame[currentIdx].getState()==otherType)
        {
            right = true;
            break;
        }
    }

//    qDebug()<< "Count "<< count<< "left blocked "<< left<< "rigth blocked "<< right;

    if(count==4 && (!left || !right))
    {
        return true;
    }
    if(count==3 && !left && !right)
    {
        return true;
    }

    qDebug()<< "return false in Board::checkWin() function";
    // default
    return false;
}



