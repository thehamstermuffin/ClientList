import QtQuick 2.12
import QtQuick.Controls 2.12
import CM 1.0
import assets 1.0
import components 1.0

Item {
    property Client selectedClient

    Component.onCompleted: masterController.ui_commandController.setSelectedClient(selectedClient)

    Rectangle {
        anchors.fill: parent
        color: Style.colorBackground
    }

    ScrollView {
        id: scrollView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: commandBar.top
        anchors.margins: Style.sizeScreenMargin
        clip: true

        Column {
            spacing: Style.sizeScreenMargin
            width: scrollView.width

            Panel {
                headerText: "Client Details"
                contentComponent:
                    Column {
                    spacing: Style.sizeControlSpacing

                    StringEditorSingleLine {
                        stringDecorator: selectedClient.ui_reference
                        anchors.left: parent.left
                        anchors.right: parent.right
                    }

                    StringEditorSingleLine {
                        stringDecorator: selectedClient.ui_name
                        anchors.left: parent.left
                        anchors.right: parent.right
                    }
                }
            }

            AddressEditor {
                address: selectedClient.ui_supplyAddress
                headerText: "Supply Address"
            }

            AddressEditor {
                address: selectedClient.ui_billingAddress
                headerText: "Billing Address"
            }
        }
    }

    CommandBar {
        id: commandBar
        commandList: masterController.ui_commandController.ui_editClientViewContextCommands
    }
}
