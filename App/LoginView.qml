import QtQuick 2.7
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.1
import Qt.labs.settings 1.0
import QtQuick.Window 2.3

Item{
    id: root

    Settings{
        property alias serverURL: loginServerUrl.text
        property alias serverPort: loginServerPort.text
    }

    Dialog{
        id: loginFailedDialog
        x: parent.width / 2 - width / 2
        y: parent.height / 2 - height / 2
        property alias text: label.text
        Label{
            id: label
            text: qsTr("Login failed! Try again!");
        }
        modal: true
        closePolicy: Popup.NoAutoClose
        visible: false
        standardButtons: Dialog.Ok
    }

    Connections{
        target: $service
        onRemoteConnected:{
            //$app.stackView.push("qrc:/PrinterListView.qml");
            console.log("connect to server !");
            $app.busy = false;
        }
        onConnectTimeout:{
            $app.busy = false;
            loginFailedDialog.visible = true;
        }
    }

    Label{
        id: loginTitle
        width: 200
        height: 50
        anchors{top: parent.top; horizontalCenter: parent.horizontalCenter; topMargin: 20}
        font.pixelSize: 20
        text: qsTr("Connect")
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    Frame{
        id: loginInfoFrame
        anchors{top: loginTitle.bottom; topMargin: 20; left: parent.left; right: parent.right; margins: 40}
        height: 200
        GridLayout{
            id: loginInfoGridLayout
            columns: 2
            anchors.fill: parent
            columnSpacing: 20
            Label{
                id: loginServerURLLabel
                text: qsTr("Server:")
                width: 80
                height: 50
                verticalAlignment: Text.AlignVCenter
            }

            TextField{
                id: loginServerUrl
                placeholderText: qsTr("Input the server URL...")
                Layout.fillWidth: true
            }

            Label{
                id: loginServerPortLabel
                text: qsTr("Port:")
                width: 80
                height: 50
                verticalAlignment: Text.AlignVCenter
            }

            TextField{
                id: loginServerPort
                placeholderText: qsTr("Input the server port...")
                Layout.fillWidth: true
                validator: IntValidator{bottom: 1; top: 65535;}
            }
        }
    }

    Connections{
        target: $service
        onInfo:{
            console.log("---------------");
            console.log(msg);
            console.log("---------------");
            debugInfo.text = msg;
        }
    }

    Button{
        id: connectBtn
        anchors{top: loginInfoFrame.bottom; topMargin: 10; horizontalCenter: parent.horizontalCenter}
        text: qsTr("Connect")
        onClicked: {
            $app.busy = true;
            $service.connectRemote(loginServerUrl.text, parseInt(loginServerPort.text));
        }
    }

    Label{
        id: debugInfo
        anchors{left: parent.left; right: parent.right; bottom: parent.bottom; margins: 5}
    }
}
