import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Window {
	width: 640
	height: 480
	visible: true
	title: Qt.application.name + " " + Qt.application.version
	Rectangle {
		anchors.fill: parent
		color: "#f0f0f0"
	}
	ColumnLayout {
		anchors.fill: parent
		Text {
			Layout.alignment: Qt.AlignHCenter
			Layout.margins: 15
			id: statusText
			text: ol.status
		}
		Rectangle {
			z: 1
			color: "white"
			border.color: "darkgrey"
			Layout.alignment: Qt.AlignHCenter
			Layout.preferredWidth: 400
			Layout.bottomMargin: 25
			Layout.fillHeight: true

			ListView{
				id: logView
				anchors.fill: parent
				anchors.leftMargin: 5
				model: ol.logModel
				spacing: 5
				delegate: Text {
					anchors.margins: 10
					text: "<b>Start:</b> " + Qt.formatDateTime(startTimestamp, "yyyy-MM-dd hh:mm:ss") +
						  " | <b>End:</b> " + Qt.formatDateTime(endTimestamp, "yyyy-MM-dd hh:mm:ss")
				}
			}
		}
		Text {
			id: name
			text: qsTr("by Gabriel Espinoza <virtuosonic at github>")
			Layout.alignment: Qt.AlignRight
			Layout.rightMargin: 10
		}
	}

}
