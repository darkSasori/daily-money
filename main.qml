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
            manager.today.newItem(desc.text, parseFloat(value.text))
        }
    }

    footer: RowLayout {
        Layout.fillWidth: true
        Label {
            id: date
            text: manager.today.date.toLocaleDateString(Qt.locale("pt_BR"), "dd/MM/yyyy")
            Layout.fillWidth: true
            Layout.leftMargin: 10
            Layout.bottomMargin: 5
        }
        Label {
            id: balance
            Layout.rightMargin: 10
            Layout.bottomMargin: 5
            text: "R$ " + manager.today.balance
        }
    }

    StackView {
        id: stackView
        anchors.fill: parent

        initialItem: Daily {
            id: daily
            anchors.fill: parent
            model: manager.today.list
            obj: manager.today
        }
    }

    Drawer {
        id: drawer
        width: Math.min(main.width, main.height) / 3 * 2
        height: main.height
        dragMargin: stackView.depth > 1 ? 0 : undefined

        ColumnLayout {
            anchors.fill: parent

            ListView {
                id: listView

                focus: true
                width: parent.width
                Layout.fillHeight: true

                delegate: ItemDelegate {
                    width: parent.width
                    text: modelData.date.toLocaleDateString(Qt.locale("pt_BR"), "dd/MM/yyyy")
                    highlighted: ListView.isCurrentItem
                    onClicked: {
                        if (listView.currentIndex == index) {
                            drawer.close()
                            return;
                        }

                        modelData.init()
                        balance.text = "R$ " + modelData.balance
                        date.text = modelData.date.toLocaleDateString(Qt.locale("pt_BR"), "dd/MM/yyyy")
                        daily.model = modelData.list
                        daily.obj = modelData

                        listView.currentIndex = index
                        drawer.close()
                    }
                }

                model: manager.list
            }

            ItemDelegate {
                Layout.fillWidth: true
                text: "Config"
                onClicked: Qt.quit();
            }

            ItemDelegate {
                Layout.fillWidth: true
                text: "Exit"
                onClicked: Qt.quit();
            }

        }
    }
}
