import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.2
import assets 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Client Management")

    Text {
        text: masterController.ui_welcomeMessage
    }

    Connections {
        target: masterController.ui_navigationController
        onGoCreateClientView: contentFrame.replace("qrc:/views/CreateClientView.qml")
        onGoDashboardView: contentFrame.replace("qrc:/views/DashboardView.qml")
        onGoEditClientView: contentFrame.replace("qrc:/views/EditClientView.qml",
                                                 {selectedClient: client})
        onGoFindClientView: contentFrame.replace("qrc:/views/FindClientView.qml")
    }

    StackView {
        id: contentFrame
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            left: navigationBar.right
        }

        initialItem: "qrc:/views/SplashView.qml"
    }

    Rectangle {
        id: navigationBar
        anchors {
            top: parent.top
            bottom: parent.bottom
            left: parent.left
        }
        width: 100
        color: "#000000"

        FontLoader {
            source: "../assets/fontawesome-webfont.ttf"
        }

        Column {
            Text {
                font {
                    family: Style.fontAwesome
                    pixelSize: 42
                }
                color: "#ffffff"
                text: "\uf0c9"
            }
            Text {
                font {
                    family: Style.fontAwesome
                    pixelSize: 42
                }
                color: "#ffffff"
                text: "\uf015"
            }
            Text {
                font {
                    family: Style.fontAwesome
                    pixelSize: 42
                }
                color: "#ffffff"
                text: "\uf234"
            }
            Text {
                font {
                    family: Style.fontAwesome
                    pixelSize: 42
                }
                color: "#ffffff"
                text: "\uf002"
            }

        }

        //            Button {
        //                text: "Dashboard"
        //                onClicked: masterController.ui_navigationController.goDashboardView()
        //            }

        //            Button {
        //                text: "New Client"
        //                onClicked: masterController.ui_navigationController.goCreateClientView()
        //            }

        //            Button {
        //                text: "Find Client"
        //                onClicked: masterController.ui_navigationController.goFindClientView()
        //            }

        //            Button {
        //                text: "Create Client"
        //                onClicked: contentFrame.replace("qrc:/views/CreateClientView.qml")
        //            }
    }

    Component.onCompleted: contentFrame.replace("qrc:/views/DashboardView.qml")
}
