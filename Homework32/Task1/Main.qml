import QtQuick

Window {
    id: root
    width: 600
    height: 400
    visible: true
    title: "Перемещение круга по холсту"
    color: "white"

    // Добавляем корневой элемент Item для поддержки states и transitions в Qt 6
    Item {
        id: content
        anchors.fill: parent
        state: "InitialState"

        // Левый квадрат (кнопка move)
        Rectangle {
            id: rectLeft
            x: 80
            y: 120
            width: 150
            height: 150
            color: "#d3d3d3"
            border.color: "black"
            border.width: 3
            radius: 10

            Text {
                anchors.centerIn: parent
                text: "move"
                font.pointSize: 14
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (ball.x + 30 >= rectRight.x) {
                        content.state = "InitialState"
                    } else {
                        content.state = "OtherState"
                        ball.x += 30
                    }
                }
            }
        }

        // Правый квадрат (кнопка return)
        Rectangle {
            id: rectRight
            x: 370
            y: 120
            width: 150
            height: 150
            color: "#d3d3d3"
            border.color: "black"
            border.width: 3
            radius: 10

            Text {
                anchors.centerIn: parent
                text: "return"
                font.pointSize: 14
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    content.state = "InitialState"
                }
            }
        }

        // Зеленый круг
        Rectangle {
            id: ball
            width: rectLeft.width - rectLeft.border.width * 2
            height: rectLeft.height - rectLeft.border.width * 2
            radius: width / 2
            color: "green"
            z: 2
        }

        // Перенесли блок состояний внутрь Item
        states: [
            State {
                name: "InitialState"
                PropertyChanges {
                    target: ball
                    x: rectLeft.x + rectLeft.border.width
                    y: rectLeft.y + rectLeft.border.width
                }
            },
            State {
                name: "OtherState"
                PropertyChanges {
                    target: ball
                    x: ball.x
                    y: ball.y
                }
            }
        ]

        // Перенесли блок анимации внутрь Item
        transitions: [
            Transition {
                from: "OtherState"
                to: "InitialState"

                NumberAnimation {
                    properties: "x,y"
                    duration: 1000
                    easing.type: Easing.OutBounce
                }
            }
        ]
    }
}
