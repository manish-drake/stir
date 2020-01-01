import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import com.drake.timer 1.0

Window {
    id: win
    property bool state: false
    flags: Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint | Qt.BypassWindowManagerHint
    visible: true
    width: ctrl.width
    height: ctrl.height
    title: qsTr("Hello World")
    Rectangle{
        id: rect
        height: ctrl.height
        width: ctrl.width
        color: Qt.rgba(ctrl.R, ctrl.G, ctrl.B, 1)
        ColumnLayout{
            width: 400
            anchors.centerIn: parent
            Text {
                id: working
                text: qsTr("Working:")
            }
            Text {
                id: active
                text: qsTr("Active:")
            }
            Text {
                id: inactive
                text: qsTr("Inactive:")
            }
        }

        MouseArea{
            anchors.fill: parent
            onClicked: ctrl.moveStage()
        }
    }
    Controller{
        id: ctrl
        onUpdateColor: {
            rect.color = Qt.rgba(R, G, B, 1)
        }
        onUpdateSize: {
            rect.height = height;
            rect.width = width;
            win.height = height;
            win.width = width;
            setX(Screen.width/ctrl.pos - ctrl.width/ctrl.pos);
            setY(Screen.height/ctrl.pos - ctrl.bottomMargin - ctrl.height/ctrl.pos);
            working.text = ctrl.working;
            active.text = ctrl.active;
            inactive.text = ctrl.inactive;
        }
    }
    onVisibilityChanged: {
        console.log("something happened!")
    }
}
