import QtQuick
import QtQuick.Controls

Window {
    id: root
    width: 500
    height: 300
    visible: true
    title: "Валидация номера телефона"
    color: "#f5f5f5"

    Column {
        anchors.centerIn: parent
        spacing: 20

        Text {
            text: "Введите номер телефона в формате +11111111111:"
            font.pointSize: 12
            anchors.horizontalCenter: parent
        }

        // Поле  ввода текста
        TextField {
            id: phoneInput
            width: 300
            font.pointSize: 14
            placeholderText: "+79991234567"
            anchors.horizontalCenter: parent

            // Настройка регулярного выражения для проверки
            validator: RegularExpressionValidator {
                regularExpression: /^\+[0-9]{11}$/
            }
        }

        // Цветная надпись состояния проверки
        Text {
            id: statusText
            // Если ввод корректен, пишем "Ok", иначе "Not Ok"
            text: phoneInput.acceptableInput ? "Ok" : "Not Ok"
            // Если ввод корректен — зеленый цвет, иначе — красный
            color: phoneInput.acceptableInput ? "green" : "red"
            font.pointSize: 20
            font.bold: true
            anchors.horizontalCenter: parent
        }
    }
}
