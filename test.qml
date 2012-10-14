import QtQuick 1.0
import QtGui 1.0

Widget {
  windowTitle: qsTr("Cool Test App")
  size: Qt.size(300, 500)

  property int counter: 0

  function myFunc()
  {
    counter++;
  }

  Component.onCompleted: _timer.timeout.connect(myFunc)

  VBoxLayout {
    Label {
      text: "Hallo ASCII-safe Kevin!!! " + counter
    }
    Label {
      id: secondLabel
      text: "Wie geht es"
    }
    Label {
      id: lastLabel
      text: secondLabel.text
    }
    Label {
      id: urlLabel
      text: "Hallo <a href=\"http://www.kde.org\">Welt</a>"

      onLinkActivated: console.log("link=" + link)
    }
    PushButton {
      text: "Click me"
      onClicked: {
        secondLabel.text = "Changed"
        counter++
      }
    }
    HBoxLayout {
      CheckBox {
        id: checkBox
      }
      Label {
        text: checkBox.checked ? "Is checked" : "Is not checked"
      }
    }
    TabWidget {
      Label {
        text: "Page 1"
      }
      Label {
        text: "Page 2"
      }
      Label {
        text: "Page 3"
      }
    }
  }
}
