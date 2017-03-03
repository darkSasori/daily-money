import QtQuick 2.6
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.1

Dialog {
    property variant obj: null
    property alias desc: desc
    property alias value: value
    x: (parent.width - width) / 2
    y: (parent.height - height) / 2
    parent: ApplicationWindow.overlay

    focus: true
    modal: true
    standardButtons: Dialog.Save | Dialog.Cancel

    ColumnLayout {
        spacing: 20
        anchors.fill: parent
        TextField {
            id: desc
            focus: true
            placeholderText: "Desc"
            Layout.fillWidth: true
        }
        TextField {
            id: value
            placeholderText: "Value"
            Layout.fillWidth: true
        }
    }

    onClosed: {
        desc.text = ""
        value.text = ""
    }
}
