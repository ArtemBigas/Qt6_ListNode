import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import nodes

Window {
    width: 800
    height: 600
    visible: true
    title: qsTr("Test task — Сериализация / Десериализация")

    Nodes { id: nodesobj }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 12

        ColumnLayout {
            anchors.margins: 12
            spacing: 12

            // Описание
            Text {
                x:10
                y:10
                text: "Описание:\n"
                    + "Раздел Сериализации содержит поле для ввода названия файла\n"
                    + "(по умолчанию inlet.in) рядом с exe файлом и кнопку «Запуск Сериализации».\n"
                    + "Раздел Десериализации содержит поле для ввода названия бинарного файла\n"
                    + "(по умолчанию outlet.out) и кнопку «Запуск Десериализации».\n"
                    + "Результат Десериализации будет написан ниже."
                font.pointSize: 10
                wrapMode: Text.Wrap
                //Layout.fillWidth: true
            }

            ColumnLayout {
                spacing: 6
                Text {
                    text: qsTr("Вывод Десериализации:")
                    font.pointSize: 12
                    font.bold: true
                    horizontalAlignment: Text.AlignLeft
                }
                ScrollView {

                       Layout.fillWidth: true
                       Layout.preferredHeight: 300
                Text {
                    text: nodesobj.fullText_qml
                    font.pointSize: 13
                    wrapMode: Text.Wrap
                    horizontalAlignment: Text.AlignLeft
                    Layout.fillWidth: true
                    Layout.preferredHeight: 300
                }}
            }
        }

        ColumnLayout {
            spacing: 40

            ColumnLayout {
                Text {
                    text: qsTr("Раздел Сериализации")
                    font.pointSize: 13
                    font.bold: true
                    horizontalAlignment: Text.AlignLeft
                }
                RowLayout {
                    TextEdit {
                        text: nodesobj.inlet_qml
                        onTextChanged: nodesobj.inlet_qml = text
                        font.pointSize: 12
                        wrapMode: TextEdit.Wrap
                    }
                    Button {
                        text: qsTr("Запуск Сериализации")
                        font.pointSize: 12
                        onClicked: {nodesobj.serialize();}
                    }
                }
            }

            ColumnLayout {
                Text {
                    text: qsTr("Раздел Десериализации")
                    font.pointSize: 13
                    font.bold: true
                    horizontalAlignment: Text.AlignLeft
                }
                RowLayout {
                    TextEdit {
                        text: nodesobj.outlet_qml
                        onTextChanged: nodesobj.outlet_qml = text
                        font.pointSize: 12
                        wrapMode: TextEdit.Wrap
                    }
                    Button {
                        text: qsTr("Запуск Десериализации")
                        font.pointSize: 12
                        onClicked: nodesobj.deserialize()
                    }
                }
            }
        }
    }
}
