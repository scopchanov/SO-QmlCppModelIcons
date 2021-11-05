import QtQuick 2.15
import QtQuick.Window 2.15

Window {
	width: 300
	height: 150
	visible: true
	title: qsTr("C++ Model Icons")

	ListView {
		anchors.fill: parent
		model: backend.model

		delegate: Row {
			Image {
				id: name
				source: "image://icons/" + index
			}

			Text {
				text: display
			}
		}
	}
}
