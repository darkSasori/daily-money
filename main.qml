import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: main
    visible: true
    width: 640
    height: 480
    title: qsTr("Daily Money")

    header: ToolBar {
        RowLayout {
            spacing: 20
            anchors.fill: parent

            ToolButton {
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: stackView.depth > 1 ? "images/back.png" : "images/drawer.png"
                }
                onClicked: {
                    if (stackView.depth > 1) {
                        stackView.pop()
                        listView.currentIndex = -1
                    } else {
                        drawer.open()
                    }
                }
            }

            Label {
                id: titleLabel
                text: main.title
                font.pixelSize: 20
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
            }

            ToolButton {
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "images/add.png"
                }
                onClicked: {
                    formDialy.open();
                }
            }
        }
    }

    FormDaily {
        id: formDialy
        onAccepted: {
            today.newItem(desc.text, parseFloat(value.text))
        }
    }

    footer: RowLayout {
        Layout.fillWidth: true
        Label {
            id: date
            text: today.date.toLocaleDateString(Qt.locale("pt_BR"), "dd/MM/yyyy")
            Layout.fillWidth: true
            Layout.leftMargin: 10
            Layout.bottomMargin: 5
        }
        Label {
            id: balance
            Layout.rightMargin: 10
            Layout.bottomMargin: 5
            text: "R$ " + today.balance
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent

        initialItem: Daily {
            id: daily
            anchors.fill: parent
            model: today.list
            obj: today
        }
    }

    Drawer {
        id: drawer
        width: Math.min(main.width, main.height) / 3 * 2
        height: main.height
        dragMargin: stackView.depth > 1 ? 0 : undefined

        ListView {
            id: listView

            focus: true
            currentIndex: -1
            anchors.fill: parent

            delegate: ItemDelegate {
                width: parent.width
                text: model.title
                highlighted: ListView.isCurrentItem
                onClicked: {
                    listView.currentIndex = index
                    drawer.close()
                }
            }

            model: ListModel {
            }
        }
    }
}
