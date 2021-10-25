import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.5

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Badluev Erdem for Armo (Client)")

    signal showImage(string srvID, string filename)

    Text{
        id:captionOfSrvId
        text: qsTr("Put here server ID:")
        anchors.top: parent.top
    }

    TextEdit{
        id:srvIdInput
        anchors.top: captionOfSrvId.bottom
        readOnly: false
        selectByMouse: true
        selectByKeyboard: true
        height: 20
        anchors.left: parent.left
        anchors.right: parent.right
    }

    Button{
        id:fileChooseButton
        text: qsTr("Open file and send")
        onClicked: {
            if(srvIdInput.text == ""){
                mesDialog.open()
            }else{
                fileChooseDialog.open()
            }
        }
        anchors.top: srvIdInput.bottom
    }

    MessageDialog{
        id:mesDialog
        standardButtons: MessageDialog.Ok
        text: qsTr("Put server ID")
    }

    FileDialog{
        id:fileChooseDialog
        title: qsTr("Please choose an image")
        folder: shortcuts.home
        nameFilters: ["jpeg (*.jpeg)", "jpg (*.jpg)", "png (*.png)"]
        onAccepted: {
            showImage(srvIdInput.text, fileUrl)
        }
    }
}
