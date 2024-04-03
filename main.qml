import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    id: window
    width: 1000

    height: 1000
    minimumHeight: 500
    minimumWidth: 500
    visible: true
    color: "#A52A2A"

    Rectangle {
        id: board
        width: parent.width
        height: parent.height

        Row{
            x:0; y:0;
            Repeater {
                model: 10
                Rectangle {
                    width:  board.width/10
                    height: board.height/10
                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: 32
                        text: (index === 9 || index === 0) ? "" : String.fromCharCode(65 + index - 1)
                    }
                    color: "#A52A2A"
                }
            }
        }

        Row{
            x: 0
            y: board.height - board.height/10;
            Repeater {
                model: 10
                Rectangle {
                    width:  board.width/10
                    height: board.height/10
                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: 32
                        text: (index === 9 || index === 0) ? "" : String.fromCharCode(65 + index - 1)
                    }
                    color: "#A52A2A"
                }
            }
        }

        Column{
            x: board.width - board.width/10
            y: 0;
            Repeater {
                model: 10
                Rectangle {
                    width:  board.width/10
                    height: board.height/10
                    Text {
                        anchors.centerIn: parent
                        text: (index === 9 || index === 0) ? "" : (10 - index - 1)
                        font.pixelSize: 32
                    }
                    color: "#A52A2A"
                }
            }
        }
        Column{
            x: 0; y:0;
            Repeater {
                model: 10
                Rectangle {
                    width:  board.width/10
                    height: board.height/10
                    Text {
                        anchors.centerIn: parent
                        text: (index === 9 || index === 0) ? "" : (10 - index - 1)
                        font.pixelSize: 32
                    }
                    color: "#A52A2A"
                }
            }
        }

        Grid {
            x: board.width/10
            y: board.height/10
            rows: 8
            columns: 8

            Repeater {
                model: 64

                Rectangle {
                    id: rect
                    width: board.width/10
                    height: board.height/10
                    color: (index + Math.floor(index / 8)) % 2 ? "#8B4513" : "#654321"

                    // MouseArea {
                    //     anchors.fill: parent
                    //     onClicked: {
                    //         rect.color = "red"
                    //     }
                    // }
                }
                Rectangle {
                    width: board.width / 10
                    height: board.height / 10
                    color: "white"
                    Image {
                        source: whitePieces.get(index).image_path
                        anchors.centerIn: parent
                        fillMode: Image.PreserveAspectFit
                    }
                }
            }
        }
    }
}
