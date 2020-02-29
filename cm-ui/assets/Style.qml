pragma Singleton
import QtQuick 2.12

Item {
    readonly property color colorBackground: "#efefef"

    property alias fontAwesome: fontAwesomeLoader.name
    FontLoader {
        id: fontAwesomeLoader
        source: "qrc:/assets/fontawesome.ttf"
    }
}
