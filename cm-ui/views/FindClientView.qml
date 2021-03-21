import QtQuick 2.12
import assets 1.0
import CM 1.0
import components 1.0

Item {
    property ClientSearch clientSearch: masterController.ui_clientSearch

    Rectangle {
        anchors.fill: parent
        color: Style.colorBackground

        Panel {
            id: searchPanel
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: Style.sizeScreenMargin
            headerText: "Find Clients"
            contentComponent:
                StringEditorSingleLine {
                stringDecorator: clientSearch.ui_searchText
                anchors.left: parent.left
                anchors.right: parent.right
            }
        }

        ListView {
            id: itemsView
            anchors.top: searchPanel.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.margins: Style.sizeScreenMargin
            clip: true
            model: clientSearch.ui_searchResults
            delegate:
                Text {
                text: modelData.ui_reference.ui_label + ": " + modelData.ui_reference.ui_value
                font.pixelSize: Style.pixelSizeDataControls
                color:  Style.colourPanelFont
            }
        }
    }

    CommandBar {
        commandList: masterController.ui_commandController.ui_findClientViewContextCommands
    }
}
