import QtQuick
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Controls.Material 2.3
import QtQml.Models
import Qt.labs.qmlmodels

Rectangle {
    id:dragRect
    height: 40
    width: rectListViewId.width
    radius: 15

    Material.accent: Material.Lime
    color: "lightslategray"
    property int i:0

    property string src:{if(model.status === "Status"){""} else model.status}
    property int _index:index

    signal released(var index)
    signal dropped(var srcIndex,var destIndex)

    onDropped: (srcIndex,destIndex)=>{rectListViewId.changeIndex(srcIndex,destIndex)}



    Connections{
        target:appWindow
        function onIReset() {i=0; if(dragRect._index==0){ animation.source="/qtIcons/pending.gif"}else{animation.source=""}}
    }

    Connections{
        target:appWindow
        function onQmlStatusCollected() { if (dragRect._index===0){src="/qtIcons/pending.gif"}else src=""}
    }
    Connections{
        target:appWindow
        function onQmlCheckedStatusCollected(){ if (dragRect._index===0){src="/qtIcons/pending.gif"}else src=""}}



    Connections{target:myClass
        function onStatusCode(value){
            if (dragRect._index===i){

                if(value===1||value===62097){animation.source="/qtIcons/xmark.gif"}
                else if (value===0){animation.source="/qtIcons/tick.png"}

            }

            else if (dragRect._index===i+1){animation.source="/qtIcons/pending.gif"}


            i++

        }

    }

    Connections{target:myClass
        function onUncheckedLinesSignal(val)
        {if(dragRect._index===val){animation.source=""}}
    }

    Connections{
        target: myClass
        function onRunAgainPressed() {

            if (dragRect._index==1)
{
         if (animation.source=="/qtIcons/pending.gif"){animation.source=""}
           }
        }}


    Rectangle{id:animationRect
        width: 30
        height: 30
        color:"transparent"
        border.color: "transparent"
        anchors.rightMargin: 5
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right

        AnimatedImage { id: animation;
            anchors.fill: parent
            source:src


        }
    }


    MouseArea{
        id:area
        hoverEnabled:true
        anchors.fill: parent
        drag.target: dragRect

        onReleased: {
            dragRect.released(index);
        }

        drag.onActiveChanged: {
            dropA.enabled=!dropA.enabled
            dragRect.Drag.drop()
            dragRect.z=2

            if (dropA.enabled){
                dragRect.z=1
                dragRect.x=0
                dragRect.y=index*(dragRect.height + mListView.spacing)

            }
        }
    }

    DropArea{
        id:dropA
        anchors.fill: parent
        onEntered:{
            dragRect.border.color=Material.color(Material.Lime)
            dragRect.border.width=15
        }
        onExited: {
            dragRect.border.color="transparent"

        }
        onDropped: (drop)=> {
                       dragRect.border.color="transparent"
                       dragRect.dropped(drop.source._index,index)
                   }
    }
    Drag.active: area.drag.active
    Drag.hotSpot.x:dragRect.width/2
    Drag.hotSpot.y:dragRect.height/2


    RowLayout{
        id:rlid

        CheckBox{
            id : cBoxId
            Layout.fillWidth: true
            Layout.topMargin: -4
            checked: model.checkBoxState
            Layout.alignment: Qt.AlignVCenter
            Layout.rightMargin: 10
            onCheckStateChanged:{
                model.checkBoxState = checked
            }

        }

        Text{
            id: processNumId
            text : index+1
            color: "White"
            Layout.alignment: Qt.AlignVCenter
            Layout.rightMargin: 20
            font.pointSize: 14.2
            Layout.topMargin:-7
            onWindowChanged: {if(text>9){
                    Layout.rightMargin=15
                    Layout.leftMargin=-5
                }

            }}

        TextField{

            id:processNameId
            placeholderText: model.processName
            onPressed: {if (placeholderText!=="Name"){processNameId.text=model.processName}}
            color: "White"
            placeholderTextColor: "LightGrey"
            selectByMouse: true
            font.pointSize: 11
            Layout.rightMargin: 10
            ToolTip.visible: hovered
            ToolTip.text: text
            ToolTip.delay: 1000
            ToolTip.timeout: hovered
            Layout.preferredWidth:44
            Layout.alignment: Qt.AlignVCenter
            Layout.topMargin: -1
            horizontalAlignment:TextInput.AlignHCenter
            onDisplayTextChanged: {model.processName = text
                if(processNameId.text.length===0){processNameId.placeholderText="Name"; Layout.preferredWidth=44}
            }

        }

        TextField{
            id:commandNameId
            selectByMouse: true
            color: "white"
            placeholderTextColor: "LightGrey"
            placeholderText : model.commandName
            font.pointSize: 11
            onPressed: {if (placeholderText!=="Command"){commandNameId.text=model.commandName}}
            Layout.topMargin: -1
            Layout.alignment: Qt.AlignVCenter
            Layout.preferredWidth:{if (placeholderText.length>9){placeholderText.length*7} else if(placeholderText=="Command"){placeholderText.length*10}else placeholderText.length*8}
            Layout.maximumWidth: dragRect.width-200

            onDisplayTextChanged: {
                model.commandName = text
                if(commandNameId.text.length>7){Layout.preferredWidth=commandNameId.text.length*7}
                else{Layout.preferredWidth=55}

                if(commandNameId.text.length===0){commandNameId.placeholderText="Command"; Layout.preferredWidth=70}
            }
        }
        Text{id:txt
            width: 30
            height: 30



        }
    }
}








