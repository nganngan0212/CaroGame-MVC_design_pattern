#include "listplayer.h"

ListPlayer::ListPlayer(QQmlApplicationEngine *m_engine, QObject *parent) : QAbstractListModel(parent)
{
    engine = m_engine;
    engine->rootContext()->setContextProperty("myListPlayer", this);

    fileName = "C:/Users/nganu/OneDrive/Desktop/Qt_C++/Qt/Mock_1_CaroGame/xml/player_data.xml";
    readFileXML();
}

ListPlayer::~ListPlayer()
{

}

int ListPlayer::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return listPlayer.size();
}

QVariant ListPlayer::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
    {
        return QVariant();
    }

    const Player &item = listPlayer[index.row()];

    switch (role) {
        case NameRole:
            return item.getName();
        case WinRole:
            return item.getNumWin();
        case LoseRole:
            return item.getNumLose();
        case DrawRole:
            return item.getNumDraw();
        default:
            return QVariant();
    }
}

bool ListPlayer::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid())
    {
        return false;
    }

    Player &item = listPlayer[index.row()];

    switch (role) {
        case NameRole:
            return item.setName(value.toString());
        case WinRole:
        {
            item.addNumWin();
            return true;
        }
        case LoseRole:
        {
            item.addNumLose();
            return true;
        }
        case DrawRole:
        {
            item.addNumDraw();
            return true;
        }
        default:
            return false;
    }

}

QHash<int, QByteArray> ListPlayer::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "PlayerName";
    roles[WinRole] = "NumWin";
    roles[LoseRole] = "NumLose";
    roles[DrawRole] = "NumDraw";

    return roles;
}

void ListPlayer::appendNewPlayer(const QString &newPlayerName)
{
    Player newPlayer = Player(newPlayerName);

    for(int i=0; i<rowCount(); i++)
    {
        if(listPlayer[i].getName() == newPlayerName)
        {
            return;
        }
    }

    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    listPlayer.append(newPlayer);
    endInsertRows();

    return;
}

void ListPlayer::setWin(const QString &nameWinner)
{
    qDebug()<< "In ListPlayer::setWin() "<< nameWinner;
    for(int i=0; i<rowCount(); i++)
    {
        if(listPlayer[i].getName() == nameWinner)
        {
            qDebug()<< "Increment lose for "<< nameWinner;
            listPlayer[i].addNumWin();
            return;
        }
    }
    return;
}

void ListPlayer::setLose(const QString &nameLoser)
{
    qDebug()<< "In ListPlayer::setLose() "<< nameLoser;
    for(int i=0; i<rowCount(); i++)
    {
        if(listPlayer[i].getName() == nameLoser)
        {
            qDebug()<< "Increment lose for "<< nameLoser;
            listPlayer[i].addNumLose();
            return;
        }
    }
    return;
}

void ListPlayer::setDraw(const QString &name1, const QString &name2)
{
    for(int i=0; i<rowCount(); i++)
    {
        if(listPlayer[i].getName() == name1)
        {
            qDebug()<< "Increment draw for "<< name1;
            listPlayer[i].addNumDraw();
            continue;
        }
        if(listPlayer[i].getName() == name2)
        {
            qDebug()<< "Increment draw for "<< name2;
            listPlayer[i].addNumDraw();
            continue;
        }
    }
}

void ListPlayer::sortPlayer()
{
    for(int i=0; i<rowCount(); i++)
    {
        for(int j=i+1; j<rowCount(); j++)
        {
            if(listPlayer[i].getNumWin()<listPlayer[j].getNumWin() || (listPlayer[i].getNumWin()==listPlayer[j].getNumWin() && listPlayer[i].getNumLose()>listPlayer[j].getNumLose()))
            {
                qDebug()<< "In ListPlayer::sortPlayer() sorting";
                Player temp = listPlayer[i];
                listPlayer[i] = listPlayer[j];
                listPlayer[j] = temp;
            }
        }
    }
}

void ListPlayer::readFileXML()
{
    QDomDocument document;

    //load the xml file
    QFile file(fileName);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        document.setContent(&file);
        file.close();
    }

    //get the xml root element
    QDomElement xmlroot = document.firstChildElement();

    //read the players
    QDomNodeList players = xmlroot.elementsByTagName("Player");
    for(int i = 0; i < players.count(); i++)
    {
        QDomElement player = players.at(i).toElement();

        Player newPlayer;
        newPlayer.setName(player.attribute("Name"));
        newPlayer.setNumWin(player.attribute("Win").toInt());
        newPlayer.setNumLose(player.attribute("Lose").toInt());
        newPlayer.setNumDraw(player.attribute("Draw").toInt());

        listPlayer.append(newPlayer);
    }
}

void ListPlayer::writeFileXML()
{
    //Write XML
    QDomDocument document;

    //Make the root element
    QDomElement root = document.createElement("Players");

    //Add it to the document
    document.appendChild(root);

    //Add some elements

    for(int i=0; i<rowCount(); i++)
    {
        QDomElement player = document.createElement("Player");
        player.setAttribute("Name", listPlayer[i].getName());
        player.setAttribute("Win", listPlayer[i].getNumWin());
        player.setAttribute("Lose", listPlayer[i].getNumLose());
        player.setAttribute("Draw", listPlayer[i].getNumDraw());
        root.appendChild(player);
    }

    //Write to file
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file for writting";
        return;
    }
    else
    {
        QTextStream stream(&file);
        stream << document.toString();
        file.close();
        qDebug() << "Finished";
    }
}
