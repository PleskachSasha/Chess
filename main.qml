import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import FigureArr 1.0
Window {
    id: window
    width: 1000

    height: 1000
    minimumHeight: 500
    minimumWidth: 500
    visible: true
    color: "#D1BB9E"
    Component.onCompleted: {
            console.log("Figures object:", figures)
        }
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
                        color: "transparent"
                    }
                    color: "#D1BB9E"
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
                        color: "transparent"
                    }
                    color: "#D1BB9E"
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
                        color: "transparent"
                    }
                    color: "#D1BB9E"
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
                        color: "transparent"
                    }
                    color: "#D1BB9E"
                }
            }
        }

        Grid {
            id: grid
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
                    color: (index + Math.floor(index / 8)) % 2 ? "#EAD8C0" : "#A79277"

                    Image {
                        source: figures_arr.callImage(index % grid.columns, Math.floor(index / grid.columns));
                        anchors.centerIn: parent
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            figures_arr.moveTo(index % grid.columns, Math.floor(index / grid.columns));
                        }
                    }
                }
            }
        }
    }
}
