import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQml 2.12

Item {
    id: viewPlayer_window
    anchors.fill: parent

    Text {
        id: game
        text: qsTr("Ranking")
        font.bold: true
        font.pixelSize: 50
        color: "red"
        anchors.bottom: playerList.top
        anchors.bottomMargin: 60
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Item {
        id: header_list
        anchors.left: playerList.left
        anchors.bottom: playerList.top
        anchors.bottomMargin: 10
        height: 21
        Text {
            id: name_head
            width: 60; height: parent.height
            anchors.left: parent.left
            anchors.leftMargin: 60
            text: qsTr("Name")
            font.pixelSize: 20
            color: "#ECA869"
        }

        Text {
            id: num_win_head
            width: 60; height: parent.height
            anchors.left: name_head.right
            anchors.leftMargin: 70
            text: qsTr("Win")
            font.pixelSize: 20
            color: "#ECA869"
        }

        Text {
            id: num_lose_head
            width: 60; height: parent.height
            anchors.left: num_win_head.right
            anchors.leftMargin: 50
            text: qsTr("Lose")
            font.pixelSize: 20
            color: "#ECA869"
        }

        Text {
            width: 60; height: parent.height
            anchors.left: num_lose_head.right
            anchors.leftMargin: 50
            text: qsTr("Draw")
            font.pixelSize: 20
            color: "#ECA869"
        }
    }

    ListView{
        id: playerList
        anchors.centerIn: parent
        width: 500
        height: 300
        model: myListPlayer
        spacing: 10

//        header:

        delegate: Rectangle{
            width: parent.width
            anchors.bottomMargin: 10
            height: 40
            radius: 20
            color: "#FFEAD2"

            Rectangle{
                id: name
                width: 60
                height: parent.height
                color: "#FFEAD2"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 60
                Text {
                    anchors.centerIn: parent
                    text: PlayerName
                    font.pixelSize: 20
                    color: "#8294C4"
                }
            }

            Rectangle{
                id: num_win
                width: 20
                height: parent.height
                color: "#FFEAD2"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: name.right
                anchors.leftMargin: 65
                Text {
                    anchors.centerIn: parent
                    text: NumWin
                    font.pixelSize: 20
                    color: "#8294C4"
                }
            }

            Rectangle{
                id: num_lose
                width: 20
                height: parent.height
                color: "#FFEAD2"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: num_win.right
                anchors.leftMargin: 105
                Text {
                    anchors.centerIn: parent
                    text: NumLose
                    font.pixelSize: 20
                    color: "#8294C4"
                }
            }

            Rectangle{
                id: num_draw
                width: 20
                height: parent.height
                color: "#FFEAD2"
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: num_lose.right
                anchors.leftMargin: 105
                Text {
                    anchors.centerIn: parent
                    text: NumDraw
                    font.pixelSize: 20
                    color: "#8294C4"
                }
            }
        }
    }

    Item{
        anchors.horizontalCenter: playerList.horizontalCenter
        anchors.top: playerList.bottom
        anchors.topMargin: 50

        Row{
            spacing: 25
            RoundButton{
                width: 70; height: 30
                background: Rectangle{
                    anchors.fill: parent
                    radius: 10
                    color: "#FFD966"
                }
                Text {
                    anchors.centerIn: parent
                    text: qsTr("Back")
                }
                onClicked: {
//                    window.source = "BoardGame.qml"
//                    viewPlayer_window.visible = false;
                    myController.switchToBoardGame()
                }
            }

            RoundButton{
                width: 70; height: 30
                background: Rectangle{
                    anchors.fill: parent
                    radius: 10
                    color: "#FFD966"
                }
                Text {
                    anchors.centerIn: parent
                    text: qsTr("New Game")
                }
                onClicked: {
                    myController.resetGameBoard()
//                    window.source = "SignIn.qml"
//                    viewPlayer_window.visible = false;
                    myController.switchToSignIn()
                }
            }
        }
    }
}
