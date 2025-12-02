import QtQuick

Window {
	width: 640
	height: 480
	visible: true
	title: Qt.application.name
	Text {
		id: statusText
		text: qsTr("Starting ping...")
	}
	Connections{
		target: ping
		function onConnectionChanged(isConnected,timestamp) {
			statusText.text = isConnected ? "<font color='green'>Online</font>" : "<font color='red'>Offline</font>"
		}
	}
}
