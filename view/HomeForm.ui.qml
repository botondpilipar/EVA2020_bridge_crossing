import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Shapes 1.14

Page {
    width: 1200
    height: 900
    contentWidth: 0

    title: qsTr("Home")

    Image {
        id: image
        x: 0
        y: 0
        width: parent.width
        height: parent.height
        source: "../media/bridge"
        fillMode: Image.PreserveAspectFit

        Button {
            id: crossButton
            x: 715
            y: 476
            text: "Mehet"
        }

        Flow {
            id: crossingSide
            x: 23
            y: 583
            width: 461
            height: 202
        }

        Flow {
            id: crossSelection
            x: 206
            y: 505
            width: 194
            height: 67
        }

        Flow {
            id: returnSelection
            x: 658
            y: 212
            width: 194
            height: 67
        }

        Flow {
            id: returningSide
            x: 867
            y: 112
            width: 315
            height: 301
        }

        Button {
            id: button
            x: 175
            y: 8
            width: 157
            height: 101
            text: qsTr("Button")
        }

        Label {
            id: label
            x: 892
            y: 46
            width: 114
            height: 26
            text: qsTr("Lorem ipsum")
        }

        Button {
            id: button1
            x: 386
            y: 8
            width: 157
            height: 101
            text: qsTr("Button")
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.8999999761581421}
}
##^##*/

