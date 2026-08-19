import QtQuick
import QtQuick.Controls

Window {
    id: window
    width: 750
    height: 450
    visible: true
    title: "видеопроигрыватель"
    color: "#1e1e1e" //темный фон окна

    //разделение окна на верх и низ
    Column {
        anchors.fill: parent
        spacing: 0

        // Экран проигрывателя
        Rectangle {
            width: parent.width
            height: parent.height - 80 //  80 пикселей снизу для панели управления
            color: "#000000" // Черный экран видео

            // имитация воспроизведение видео
            Text {
                anchors.centerIn: parent
                text: "🎬 [Экран воспроизведения видео]"
                color: "#555555"
                font.pixelSize: 20
                font.bold: true
            }
        }

        // управление воспроизведением
        Rectangle {
            width: parent.width
            height: 80
            color: "#2c2c2c" // Серый фон нижней панели

            // строка элементов
            Row {
                anchors.fill: parent
                anchors.margins: 15
                spacing: 10
                anchors.verticalCenter: parent.verticalCenter


                // Кнопка плей
                Button {
                    text: "▶️"
                    font.pixelSize: 16
                    width: 50
                    height: 40
                }

                // Кнопка паузы
                Button {
                    text: "⏸️"
                    font.pixelSize: 16
                    width: 50
                    height: 40
                }

                // Кнопка стоп
                Button {
                    text: "⏹"
                    font.pixelSize: 16
                    width: 50
                    height: 40
                }

                // Перемотка
                Button {
                    text: "⏪️"
                    font.pixelSize: 16
                    width: 50
                    height: 40
                }

                // Быстрое воспроизведение
                Button {
                    text: "⏩️"
                    font.pixelSize: 16
                    width: 50
                    height: 40
                }

                // Горизонтальный ползунок

                ProgressBar {
                    id: playbackProgress
                    width: parent.width - (5 * 50) - (5 * 10) - 20
                    height: 10
                    anchors.verticalCenter: parent.verticalCenter

                    from: 0
                    to: 100
                    value: 40
                }
            }
        }
    }
}
