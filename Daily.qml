import QtQuick 2.7
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.1

ListView {
    id: listDaily
    property variant obj: null
    anchors.fill: parent
    focus: true
    delegate: ItemDelegate {
        width: parent.width

        onPressAndHold: {
            formDialy.obj = modelData
            formDialy.desc.text = modelData.desc
            formDialy.value.text = modelData.value
            formDialy.open();
        }

        onDoubleClicked: {
            remove.index = index
            remove.open();
        }

        RowLayout {
            anchors.fill: parent

            Label {
                Layout.leftMargin: 10
                text: modelData.desc
            }

            Item {
                Layout.fillWidth: true
            }

            Label {
                Layout.rightMargin: 10
                text: Number(modelData.value).toLocaleString(Qt.locale("pt_BR"))
            }
        }
    }

    FormDaily {
        id: formDialy
        onAccepted: {
            obj.desc = desc.text
            obj.value = value.text
        }
    }

    Dialog {
        id: remove
        property int index: -1
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        parent: ApplicationWindow.overlay

        focus: true
        modal: true
        title: "Do yo want remove?"
        standardButtons: Dialog.Ok | Dialog.Cancel

        onAccepted: {
            obj.remove(index)
        }
    }
}
