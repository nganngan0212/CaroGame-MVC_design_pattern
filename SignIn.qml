import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQml 2.12

Item {
    id: signIn_window
    anchors.centerIn: parent
    visible: true
    Text {
        id: game
        text: qsTr("Caro Game")
        font.bold: true
        font.pixelSize: 65
        font.family: "Comic Sans"
        color: "red"
        anchors.bottom: sign_rect.top
        anchors.bottomMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Column{
        id: sign_rect
        spacing: 13
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        Rectangle{
            width: 280; height: 50
            color: "#FBFACD"
            radius: 20

            TextField{
                id: user_1
                anchors.fill: parent
                anchors.leftMargin: 5
                background: parent
                wrapMode: Text.WordWrap
                font.pixelSize: 16
                placeholderText: qsTr("Enter the name of player 1")
                placeholderTextColor: "#DEBACE"
                color: "#7F669D"
                onEditingFinished: {
                    console.log("Entered the username 1")
                }
            }
        }
        Rectangle{
            width: 280; height: 50
            color: "#FBFACD"
            radius: 20

            TextField{
                id: user_2
                anchors.fill: parent
                anchors.leftMargin: 5
                background: parent
                wrapMode: Text.WordWrap
                font.pixelSize: 16
                placeholderText: qsTr("Enter the name of player 2")
                placeholderTextColor: "#DEBACE"
//                echoMode: TextInput.Password
//                passwordMaskDelay: 1000
                color: "#7F669D"
                onEditingFinished: {
                    console.log("Entered the username 2")
                }
            }
        }
    }

    RoundButton{
        id: signIn_button
        width: 75; height: 35
        anchors.top: sign_rect.bottom
        anchors.topMargin: 15
        anchors.horizontalCenter: parent.horizontalCenter
        radius: 10
        palette{
            button: "#BA90C6"
        }

        Text {
            text: qsTr("OK")
            anchors.centerIn: parent
        }

        onClicked: {
//                console.log("Button signIn clicked"),
            player_1 = myController.checkValidName_user1(user_1.text)
            player_2 = myController.checkValidName_user2(user_2.text)
            myController.addPlayer(player_1,player_2)
        }
    }


    Item {
        id: languageButton
        anchors.top: signIn_button.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter

        Row{
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 5
            Button{
                id: engButton
                background: Rectangle{
                    id:background_engBut
                    width: 35
                    height: 25
                    color: "#92BA92"
                    radius: 8
                }

                text: "Eng"
                 onClicked: {
                     background_engBut.color= "#F1DDBF"
                     background_vieBut.color= "#92BA92"
                 }
            }
            Button{
                id: vieButton
                background: Rectangle{
                    id:background_vieBut
                    width: 35
                    height: 25
                    color: "#92BA92"
                    radius: 8
                }

                text: "Vie"
                 onClicked: {
                     background_engBut.color= "#92BA92"
                     background_vieBut.color= "#F1DDBF"
                 }
            }
        }
    }
}
