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
            options.index = index
            options.obj = modelData
            options.open()
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
                text: modelData.value
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
        title: "Do you want remove?"
        DialogButtonBox {
            Button {
                text: qsTr("Ok")
                onClicked: {
                    obj.remove(remove.index)
                    remove.index = -1
                    remove.close()
                }
            }
            Button {
                text: qsTr("Cancel")
                onClicked: {
                    remove.index = -1
                    remove.close()
                }
            }
        }
    }

    Dialog {
        property variant obj: null
        property int index: -1
        id: options
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2
        parent: ApplicationWindow.overlay

        focus: true
        modal: true
        DialogButtonBox {
            Button {
                text: qsTr("Edit")
                onClicked: {
                    options.close()
                    formDialy.obj = options.obj
                    formDialy.desc.text = options.obj.desc
                    formDialy.value.text = options.obj.value
                    formDialy.open();
                }
            }
            Button {
                text: qsTr("Remove")
                onClicked: {
                    remove.index = options.index
                    options.close()
                    remove.open()
                    options.index = -1
                }
            }
        }
    }
}
