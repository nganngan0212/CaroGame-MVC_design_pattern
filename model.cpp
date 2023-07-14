#include "model.h"

Model::Model(QQmlApplicationEngine *m_engine,QObject *parent) : QObject(parent)
{
    currentTurn = 0;
    engine = m_engine;
    myGameBoard = new Board(engine);

    // check null truoc khi su dung con tro
    myGameBoard->createNewBoard();

    myListPlayer = new ListPlayer(engine);
//    m_engine->rootContext()->setContextProperty("GameModel",this);
    QObject::connect(myGameBoard, SIGNAL(newStepChanged(bool)), this, SLOT(makedNewStep(bool)));
    QObject::connect(myGameBoard, SIGNAL(returnWin(QString)), this, SLOT(getWinnerType(QString)));

}

Model::~Model()
{
    delete(myGameBoard);
    myGameBoard = nullptr;

    delete(myListPlayer);
    myListPlayer = nullptr;
}

void Model::inGamePlayer(const QString &player1, const QString &player2)
{
    myListPlayer->appendNewPlayer(player1);
    myListPlayer->appendNewPlayer(player2);
}

void Model::makeStep(const int &index)
{
    qDebug()<< "In Model::makeStep() "<< index;
    appendSaveBoard(index, getCurrentType());
    myGameBoard->setBoardState(index, getCurrentType());
}

void Model::resetBoard()
{
    myGameBoard->reset();
    currentTurn = 0;

    resetSaveBoard();
}

void Model::makedNewStep(bool newStepIsDone)  // slot
{
    if(newStepIsDone)
    {
        currentTurn = !currentTurn;
    }
}

void Model::getWinnerType(QString type)
{
    emit annouceWinner(type); // connect to controller
}

QString Model::getCurrentType() const
{
    if(currentTurn == 0)
    {
        return "X";
    }
    else{
        return "O";
    }
}

QString Model::getDisplayType(int index) const
{
    return myGameBoard->getBoardState(index);
}

void Model::setWinGame(const QString &winType, const QString &namePlayerX, const QString &namePlayerO)
{
    qDebug()<< "On Model::setWinGame() win is"<< winType;
    if(winType == "X")
    {
        myListPlayer->setWin(namePlayerX);
        myListPlayer->setLose(namePlayerO);
    }
    if(winType == "O")
    {
        myListPlayer->setWin(namePlayerO);
        myListPlayer->setLose(namePlayerX);
    }
    if(winType == "")
    {
        myListPlayer->setDraw(namePlayerO, namePlayerX);
    }
    myListPlayer->sortPlayer();
    // call write to XML function here
    myListPlayer->writeFileXML();
}

void Model::appendSaveBoard(const int &position,const QString &state)
{
    saveBoard.insert(position,state);
}

void Model::replaySaveBoard()
{
    qDebug() << "Total steps: "<< saveBoard.size();
    myGameBoard->reset();

//    QTimer* replayTimer = new QTimer(this);
//    replayTimer->setInterval(1000);
//    connect(replayTimer, &QTimer::timeout, myGameBoard, &Board::replayStep);


    for (QMap<int, QString>::const_iterator it = saveBoard.constBegin(); it != saveBoard.constEnd(); it++)
    {
//        replayTimer->start();
        // get data
        int currentPos = it.key();
        QString currentType = it.value();

        qDebug()<< "Position "<< currentPos<< "type "<< currentType;
        myGameBoard->replayStep(currentPos,currentType);

//        replayTimer->stop();
    }


}

void Model::resetSaveBoard()
{
    saveBoard.clear();
}

