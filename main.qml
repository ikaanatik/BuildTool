import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3
import QtQml.Models
import Qt.labs.qmlmodels
import QtQuick.Dialogs
import LineModel 1.0

ApplicationWindow {
    id:appWindow
    width:1400
    height: 760
    visible: true
    title: qsTr("Build Tool")
    color: "#4E535D"

    signal qmlStatusCollected()
    signal qmlCheckedStatusCollected()
    signal iReset()


    Connections{
        target: myClass
        function onOutlogText(parameter) {
            outlogId.text = parameter

        }}

    Connections{
        target: myClass
        function onRunAgainPressed() {


            outlogId.text = "\nThe program run has been interrupted. \n\n           Please Press one of the Run Buttons to run from the beginning"

        }}

    LineModel{
        id:myClass}

    FileDialog{
        id:openFileDialogId
        nameFilters:{"XML files (*.xml)"}

        onAccepted: {

            var path = openFileDialogId.selectedFile.toString();
            path= path.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/,"");
            var cleanPath = decodeURIComponent(path);
            myClass.setFileName(cleanPath)
            myClass.loadXML();
        }
        onRejected: {
            console.log("Canceled")
        }
    }

    FileDialog{
        id:saveFileDialogId
        fileMode: FileDialog.SaveFile
        nameFilters:{"XML File (*.xml)"}
        onAccepted: {
            var path = saveFileDialogId.selectedFile.toString();
            path= path.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/,"");
            var cleanPath = decodeURIComponent(path);
            myClass.setFileName(cleanPath)
            myClass.saveXML();

        }
    }

    header: ToolBar{

        Material.theme: Material.Dark
        Material.primary: Material.color(Material.Teal)

        Row{

            ToolButton{
                id:addActionId
                icon.source: "/qtIcons/add.png"
                ToolTip.visible: hovered
                ToolTip.text: "Adds new process line"
                ToolTip.delay: 1000
                ToolTip.timeout: pressed
                onClicked: {
                    myClass.addLine()
                }
            }

            ToolButton{
                id:deleteActionId
                icon.source: "/qtIcons/delete.png"
                ToolTip.visible: hovered
                ToolTip.text: "Deletes the selected lines of processes"
                ToolTip.delay: 1000
                ToolTip.timeout: pressed
                onClicked: {myClass.removeCheckedLines()}
            }

            ToolButton{
                id:clearActionId
                icon.source: "/qtIcons/clear.png"
                ToolTip.visible: hovered
                ToolTip.text: "Deletes all process lines"
                ToolTip.delay: 1000
                ToolTip.timeout: pressed
                onClicked: {
                    myClass.removeAllLines()
                }
            }

            ToolButton{
                id:runActionId
                icon.source: "/qtIcons/run.png"
                ToolTip.visible: hovered
                ToolTip.text: "Runs the selected lines of processes sequently"
                ToolTip.delay: 1000
                ToolTip.timeout: pressed
                onClicked: {

                    iReset()
                    qmlCheckedStatusCollected()
                    myClass.checkedArgCollector()
                    myClass.runCheckedLines()

                }
            }

            ToolButton{
                id:run_allActionId
                icon.source: "/qtIcons/run all.png"
                ToolTip.visible: hovered
                ToolTip.text: "Runs all process lines sequently"
                ToolTip.delay: 1000
                ToolTip.timeout: pressed
                onClicked: {

                    iReset()
                    qmlStatusCollected()
                    myClass.argCollector()
                    myClass.runAllLines()
                }
            }


            ToolButton{
                id:stopActionId
                icon.source: "/qtIcons/stop.png"
                ToolTip.visible: hovered
                ToolTip.text: "Stops the currently running process"
                ToolTip.delay: 1000
                ToolTip.timeout: pressed
                onClicked: {

                    myClass.stopProcess()
                    stopPopup.open()}

            }


            ToolButton{
                id:saveActionId
                icon.source: "/qtIcons/save.png"
                ToolTip.visible: hovered
                ToolTip.text: "Saves the process lines to XML"
                ToolTip.delay: 1000
                ToolTip.timeout: pressed
                onClicked: {
                    saveFileDialogId.open()
                }
            }

            ToolButton{
                id:loadActionId
                icon.source: "/qtIcons/load.png"
                ToolTip.visible: hovered
                ToolTip.text: "Loads the process lines from XML"
                ToolTip.delay: 1000
                ToolTip.timeout: pressed
                onClicked: {openFileDialogId.open();}
            }

            Popup{
                id: stopPopup
                x:rectId.width + rectId.width/4
                y:parent.height/2
                contentItem :Text{
                    text:"Process has stopped"}}
        }


        ToolButton{
            id:clearOutlogId
            icon.source:"/qtIcons/clearOutlog.png"
            ToolTip.visible: hovered
            ToolTip.text: "Clears the output area"
            ToolTip.delay: 1000
            ToolTip.timeout: pressed
            anchors.right:parent.right
            onClicked: {
                myClass.outputClear()
                outlogId.clear()
            }
        }
    }

    Rectangle{
        id:rectListViewId
        height:parent.height-11
        width:parent.width/2-8
        x:6;y:8
        radius: 10
        color: "#4E535D"

        DelegateModel{id:visualModel
            model:myClass
            delegate:OneLine{}
        }

        signal changeIndex(var index_src,var index_dest)
        onChangeIndex:(index_src,index_dest)=> {

                          if(index_src>index_dest){

                              visualModel.items.move(index_src,index_dest)
                              myClass.move(index_src,index_dest)}

                          else{
                              visualModel.items.move(index_dest,index_src)
                              myClass.move(index_dest,index_src)}

                      }


        ListView{
            id : mListView
            height:parent.height
            width:parent.width
            spacing: 10
            model: visualModel

        }
    }

    Rectangle{
        id: rectId
        height:parent.height-11
        width:parent.width/2-15
        anchors { left:OneLine.right; }
        x:parent.width/2+4 ;y:8

        color:"black"
        border.width: 2
        radius: 10

        ColumnLayout {
            height:parent.height
            width:parent.width-20
            x:30

            ScrollView{
                Material.theme: Material.Dark
                Material.accent: Material.LightGreen

                Layout.fillHeight: true
                Layout.fillWidth: true

                TextArea {
                    color: "LightGrey"
                    readOnly: true

                    id: outlogId
                    selectByKeyboard: true
                    selectByMouse: true
                    wrapMode: TextArea.WrapAtWordBoundaryOrAnywhere
                    placeholderText: "    Enter Command And Press Run Button To See Output"
                    placeholderTextColor: "LightGrey"
                    font.pixelSize: 15

                }

            }

        }

    }

}
