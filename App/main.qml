import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    visibility: Window.FullScreen

    StackView{
        id: stackView
        anchors.fill: parent
        initialItem: LoginView{}
        Component.onCompleted:{
            $app.stackView = stackView;
        }
    }

    Rectangle{
        id: busyLayer
        anchors.fill: parent
        visible: $app.busy
        color: Qt.rgba(0.2, 0.2, 0.2, 0.2)

        BusyIndicator {
            running: $app.busy
            anchors.centerIn: parent
        }
    }
}
