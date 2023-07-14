import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQml 2.12

Item {
    id: game_window
    anchors.fill: parent
    visible: true

    Row{
        x: gameTable.x; y: gameTable.y - 40
        spacing: 25
        Text {
            id: player1
            color: "#874C62"
            text: qsTr(player_1+"<"+"X"+">")
            font.pointSize: 15
        }

        Text {
            id: player2
            color: "#874C62"
            text: qsTr(player_2+"<"+"O"+">")
            font.pointSize: 15
        }
    }

    GridView {
        id: gameTable
        width: 500
        height: 500
        cellWidth: 50
        cellHeight: 50

        model: MyGameBoard
        anchors.centerIn: parent

        delegate: Rectangle {
            width: 50
            height: 50
            border.color: "#8294C4"
            color: "#EEEEEE"
            radius: 5
            MouseArea {
                id: cellClick
                anchors.fill: parent
                onClicked: {
                    // handle click event
                    var row = Math.floor(index / 10)
                    var col = index % 10
                    console.log("Clicked on cell [" + row + ", " + col + "]")
                    myController.setStep(index)
                    displayXO.text = myController.getText(index)
                }
            }

            Text {
                id: displayXO
                text: myController.getText(index)
                color: "red"
                font.pointSize: 15
                anchors.centerIn: parent
            }
        }
    }

    Item {
//        id: name
        anchors.horizontalCenter: gameTable.horizontalCenter
        anchors.top: gameTable.bottom
        anchors.topMargin: 20

        Row{
            anchors.centerIn: parent
            spacing: 50
            RoundButton{
                id: resetButton
                width: 90; height: 30
                background: Rectangle{
                    anchors.fill: parent

                    radius: 10
                    color: "#FFD966"
                }
                Text {
                    anchors.centerIn: parent
                    text: qsTr("Reset Board")
                }
                onClicked: {
                    console.log("On reset button")
                    myController.resetGameBoard()
                    announceWinner.visible = false;
                }
            }

            RoundButton{
                id: viewPlayers
                width: 150; height: 30
                background: Rectangle{
                    anchors.fill: parent

                    radius: 10
                    color: "#FFD966"
                }
                Text {
                    anchors.centerIn: parent
                    text: qsTr("View player info")
                }
                onClicked: {
                    console.log("On view player info button")
//                    game_window.visible = false
//                    window.source = "ViewPlayer.qml"
                    myController.switchToViewPlayer()
                }
            }

            RoundButton{
                id: replay
                width: 150; height: 30
                background: Rectangle{
                    anchors.fill: parent

                    radius: 10
                    color: "#FFD966"
                }
                Text {
                    anchors.centerIn: parent
                    text: qsTr("Replay")
                }
                onClicked: {
                    console.log("On replay button")
                    myController.replayGame()
                    announceWinner.visible = false
                }
            }
        }
    }

    Item {
        id: announceWinner
        visible: false
        property string winner_name: ""
        anchors.centerIn: parent

        Connections{
            target: myController

            onWinnerSignal: {
                console.log("On winner signal in QML")
                announceWinner.winner_name = win_type
                announceWinner.visible = true
                myController.setWinner(win_type, player_1, player_2)
            }

            onDrawSignal: {
                console.log("On draw signal in QML")
                winnerDisplay.text = qsTr("Draw game!!!")
                announceWinner.visible = true;
                myController.setWinner("", player_1, player_2)
            }
        }

        Rectangle{
            id: annouceRect
//            color: Qt.rgba(255,228,225,200)
            radius: 20
            width: winnerDisplay.width + 100
            height: 100
            opacity: 50

            anchors.centerIn: parent
            Text {
                anchors.centerIn: parent
                id: winnerDisplay
                color: "red"
                font.pixelSize: 25
                text: (qsTr("Game over! ") + announceWinner.winner_name + qsTr(" is winner"))
            }
        }
    }

}
