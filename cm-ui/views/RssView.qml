import QtQuick 2.12
import assets 1.0
import components 1.0

Item {
    Rectangle {
        anchors.fill: parent
        color: Style.colorBackground

        ListView {
            id: itemsView
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: commandBar.top
            anchors.margins: Style.sizeScreenMargin
            clip: true
            model: masterController.ui_rssChannel ? masterController.ui_rssChannel.ui_items : 0
            delegate: RssItemDelegate {
                rssItem: modelData
            }
        }
    }

    CommandBar {
        id: commandBar
        commandList: masterController.ui_commandController.ui_rssViewContextCommands
    }
}
