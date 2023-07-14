import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQml 2.12

Window {
    width: 720
    height: 680
    color: "#FDFAF6"
    visible: true
    title: qsTr("Caro Game")

    property string player_1: ""
    property string player_2: ""

    Loader{
        id: window
        anchors.centerIn: parent
        source: myController.sourceScreen
    }
}
