import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs
import QtQuick3D
import QtQuick3D.AssetUtils
import QtQuick3D.Helpers
import POiGK1
import QtMultimedia
import "models"



Window {
    width: Screen.width
    height: Screen.height
    visible: true
    visibility: "Maximized"

    title: qsTr("Szachy")
    property string chess_data: ""
    property bool camera_control: false
    property bool auto_on: false;
    property variant instances: []

    Node{
        id: standAloneScene
        DirectionalLight{
            ambientColor: Qt.rgba(1, 1, 1, 1.0)
            brightness: 2.0
        }
        Node{
            id: originPerspective
            PerspectiveCamera {
                id: cameraPerspectiveOne
                eulerRotation.x:-90
                y: 1000;
            }
        }

        // Stationary orthographic camera viewing from Top
        OrthographicCamera {
            id: cameraOrthographicTop
            eulerRotation.x: -90
            position: Qt.vector3d(0,800,0)
        }
    }

    DataParser{
        id:parser;
        onParsedMoveText: (data) =>{
            chess_data = data;
        }
        onParsedTagRoster: (tags) =>{
            tag_players_text.text = tags[3] +" v. " + tags[4];
            tag_players_text.font.pointSize = 40;
            tag_description_text.text = "Event: " +tags[0] + " Date: " + tags[1] + " Result: " + tags[2];
        }

    }

    FileLoader{
        id: myFileLoader
        onMovesEmitted: (data) =>{
            chess.loadGame(parser.pMoveText(data));
            b_next_turn.enabled = true;
        }
        onTagsEmitted: (data) =>{
            parser.pTagRoster(data);
        }
    }
    SoundEffect{
        id:capture_sound
        source: "sound_effects/capture.wav";
    }
    SoundEffect{
        id:move_sound
        source: "sound_effects/move.wav";
    }
    Timer{
        id:timer;
        interval: 1000; running: false; repeat: true
        onTriggered: chess.game();
    }

    Rectangle{
        id:rect1
        width:parent.width*0.5
        height:parent.height
        color: "#4b4847"

        View3D{
            id:chessView
            anchors.fill:parent
            importScene: standAloneScene;
            camera: cameraOrthographicTop;

            OrbitCameraController{
                id:orbit;
                anchors.fill:parent
                origin: originPerspective
                camera: cameraPerspectiveOne
                enabled: camera_control;

             }


            ChessControler{
                id: chess;
                Component.onCompleted:{
                    console.log("AAAAAA");
                    chess.init();
                }
                onInitFinished: {
                    // check if declared, if yes delete pieces and clear list
                    if(instances.length != 0){
                        do{
                            instances[instances.length-1].destroy();
                            instances.pop();
                        }while(instances.length != 0)
                        move_model.clear();
                        while(move_list.count !== 0){
                            move_list.remove(move_list.currentIndex);
                            move_list.decrementCurrentIndex();
                        }

                    }
                    console.log(instances.length);
                    for(let i = 0; i<32;i++){
                        var component
                        if(i < 8) component = Qt.createComponent("models/White_Pawn.qml");
                        if(i == 8 || i == 15) component = Qt.createComponent("models/White_Rook.qml");
                        if(i == 9 || i == 14) component = Qt.createComponent("models/White_Knight.qml");
                        if(i == 10 || i == 13) component = Qt.createComponent("models/White_Bishop.qml");
                        if(i == 11) component = Qt.createComponent("models/White_Queen.qml");
                        if(i == 12) component = Qt.createComponent("models/White_King.qml");
                        if(i > 15 && i <24) component = Qt.createComponent("models/Black_Pawn.qml");
                        if(i == 24 || i == 31) component = Qt.createComponent("models/Black_Rook.qml");
                        if(i == 25 || i == 30) component = Qt.createComponent("models/Black_Knight.qml");
                        if(i == 26 || i == 29) component = Qt.createComponent("models/Black_Bishop.qml");
                        if(i == 27) component = Qt.createComponent("models/Black_Queen.qml");
                        if(i == 28) component = Qt.createComponent("models/Black_King.qml");

                        let instance = component.createObject(pieceContainer);

                        instances.push(instance);
                    }


                }
                onLocationEmitted:(data)=> {
                    console.log(data);
                    let i = data[0];

                    instances[i].x = data[1];
                    instances[i].z = data[2];


                }
                onCapture:(data)=>{
                    instances[data].visible = false;
                }
                onPromotion:(data)=>{
                    instances[data[0]].destroy();
                    let mesh_color;
                    let mesh_type;
                    if(data[0] < 16) mesh_color = "models/White_";
                    else mesh_color = "models/Black_";
                    if(data[1] == "Q") mesh_type = "Queen.qml";
                    if(data[1] == "R") mesh_type = "Rook.qml";
                    if(data[1] == "B") mesh_type = "Bishop.qml";
                    if(data[1] == "N") mesh_type = "Knight.qml";
                    let selected_model = mesh_color+mesh_type;
                    let component = Qt.createComponent(selected_model);
                    instances[data[0]] = component.createObject(pieceContainer);
                }
                onMoveEmitted: (m)=>{
                    if(move_model.count !== m[0]+1){
                        move_model.append({"turn":m[0]+1,"w_move":m[1], "b_move":""})
                        move_list.incrementCurrentIndex();
                    }else{
                        move_model.set(m[0],{"b_move":m[1]});
                    }
                }
                onEmitSound: (cap)=>{
                    if(cap) capture_sound.play();
                    else move_sound.play();
                }
            }

            Chess_board{}
            Chess_base{}

            Node{
                id:pieceContainer

               }
            }
    }




    Rectangle{

        id:rect2
        color : "#4b4847"
        anchors.left:rect1.right;
        width:parent.width*0.5
        height:parent.height
        Rectangle{
            id: tag_container
            width:parent.width;
            height:parent.height*0.2
            color: "#2C2B29";
            z: 1;
            Rectangle{
                id: tag_players;
                width:parent.width;
                height:parent.height*0.6;
                color: "#2C2B29";
                Text{
                    id: tag_players_text;
                    anchors.fill: parent;
                    horizontalAlignment: Text.AlignHCenter;
                    verticalAlignment: Text.AlignVCenter;
                    text:"Wprowadź plik aby rozpocząć wizualizacje."
                    font.pointSize: 20;
                    color:"white";
                    fontSizeMode: Fit;

                }
            }
            Rectangle{
                id: tag_description;
                width:parent.width;
                height:parent.height*0.4;
                anchors.top:tag_players.bottom;
                color: "#2C2B29";
                Text{
                    id: tag_description_text;
                    anchors.fill: parent;

                    horizontalAlignment: Text.AlignHCenter;
                    text:"";
                    font.pointSize: 20;
                    fontSizeMode: Fit;
                    color:"white";
                }
            }
        }
        Rectangle{
            width:parent.width;
            height:parent.height*0.65
            anchors.top: tag_container.bottom;


            color: 	"#3C3A38";
            id: move_container
            ListModel{
                id: move_model;
            }
            Component{
                id: move_delegate;
                Row{
                    spacing : 20;

                    Text{text: turn+".";font.pointSize: 20;color:"white"}
                    Text{text: w_move;font.pointSize:20; color:"white"}
                    Text{text: b_move;font.pointSize:20; color:"white"}
                }
            }

            ListView{
                id: move_list
                model:move_model
                anchors.fill: parent;
                anchors.leftMargin: 20;
                ScrollBar.vertical: ScrollBar{}
                delegate: move_delegate;
                highlight: Rectangle{color:"#4B4847"; width:parent}
                highlightFollowsCurrentItem: true;
            }
        }
        Rectangle{
            id:button_container
            width:parent.width;
            height:parent.height*0.15
            anchors.top: move_container.bottom;
            color:"#2C2B29"
            Button{
                id: b_file
                text: qsTr("Choose File...")
                onClicked: fileDialog.open()
            }
            Button{
                id: b_cam
                anchors.left: b_file.right;
                text:"change camera"
                onClicked: {
                    if(!camera_control){
                        chessView.camera = cameraPerspectiveOne;
                        camera_control = true;
                    }else{
                        chessView.camera = cameraOrthographicTop;
                        camera_control = false;
                    }

                }
            }
            Button{
                id:b_auto
                anchors.left:b_cam.right;
                text:"auto";
                onClicked:{
                    if(auto_on){
                        timer.running = false;
                    }else{
                        timer.running = true;
                    }
                }
            }
            Button{
                enabled: false;
                id: b_next_turn
                anchors.left: b_auto.right;
                text: "następna tura"
                onClicked: chess.game();
            }


        }





    }
    FileDialog {
        id: fileDialog
        onAccepted: {
            var path = selectedFile.toString();
                    // remove prefixed "file:///"
                    path = path.replace(/^(file:\/{3})/,"");
                    // unescape html codes like '%23' for '#'
                    var cleanPath = decodeURIComponent(path);
            myFileLoader.loadFile(cleanPath)
        }
    }
}
