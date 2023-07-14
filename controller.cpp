#include "controller.h"

Controller::Controller(QQmlApplicationEngine *m_engine, QObject *parent) : QObject(parent)
{
    engine = m_engine;
    myModel = new Model(engine);
    engine->rootContext()->setContextProperty("myController",this);
    QObject::connect(myModel, SIGNAL(annouceWinner(QString)), this, SLOT(getWinner(QString)));

    setSourceScreen("SignIn.qml");
}

Controller::~Controller()
{
    delete(myModel);
    myModel = nullptr;
}

void Controller::addPlayer(const QString &namePlayer1,const QString &namePlayer2)
{
    myModel->inGamePlayer(namePlayer1, namePlayer2);
    switchToBoardGame();
}

void Controller::setStep(const int &index)
{
    if(!isEndGame)
    {
        qDebug() << "In Controller::setStep"<< index;
        myModel->makeStep(index);
    }
    else{
        qDebug()<< "Game ended! Can not make any step";
    }

}

QString Controller::getText(const int &index)
{
    return myModel->getDisplayType(index);
}

void Controller::resetGameBoard()
{
    myModel->resetBoard();
    isEndGame = false;
}

void Controller::setWinner(const QString &winType, const QString &namePlayerX,const QString &namePlayerO)
{
    qDebug()<< "On Controller::setWinner()";
    myModel->setWinGame(winType,namePlayerX,namePlayerO); // function
}

QString Controller::checkValidName_user1(const QString &inName)
{
    if(inName == "")
    {
        return "Player1";
    }
    return inName;
}

QString Controller::checkValidName_user2(const QString &inName)
{
    if(inName == "")
    {
        return "Player2";
    }
    return inName;
}

void Controller::replayGame()
{
    myModel->replaySaveBoard();
}

void Controller::switchToViewPlayer()
{
    setSourceScreen("ViewPlayer.qml");
}

void Controller::switchToBoardGame()
{
    setSourceScreen("BoardGame.qml");
}

void Controller::switchToSignIn()
{
    setSourceScreen("SignIn.qml");
}

QString Controller::getWinner(QString name)
{
    qDebug()<< "Game over! "<< name<< "is winner";
    isEndGame = true;
    if(name != "X" && name != "O")
    {
        emit drawSignal("Draw game");
    }
    else{
        emit winnerSignal(name);
    }

    return name;
}

const QString &Controller::sourceScreen() const
{
    return m_sourceScreen;
}

void Controller::setSourceScreen(const QString &newSourceScreen)
{
    if (m_sourceScreen == newSourceScreen)
        return;
    m_sourceScreen = newSourceScreen;
    emit sourceScreenChanged();
}
