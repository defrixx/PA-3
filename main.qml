import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Window 2.3
import QtMultimedia 5.9
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0


/* Справка http://doc.qt.io/qt-5/qtqml-cppintegration-topic.html / http://doc.qt.io/qt-5/qtqml-cppintegration-overview.html
    4 типа взаимодействия QML и C++ кода:
        1) Привязка C++ - слотов к QML-сигналам
        2) Получение ссылок на QML-объекты в C++ коде (делает видимым QML-объект в C++)
        3) Помещение C++ функций и объектов в область видимости QML
        4) Привязка QML-слотов к сигналам C++ объектов
*/


ApplicationWindow {

    Window {
        id: splashWindow
        width: 640
        height: 520
        visible: true
        x: Screen.width / 2 - width / 2;
        y: Screen.height / 2  - height / 2;
        flags: Qt.SplashScreen;
        Rectangle {
            anchors.fill: parent
            color: "#2b2b2e";
        }
        Image{
            source: "file:///C:/Users/Defrixx/Documents/QtDefrixx/Images/logo.png"
            fillMode: Image.PreserveAspectFit
            width: parent.width
            height: parent.height
            clip: true
        }

        ProgressBar {
            id: progressBar
            anchors.centerIn: parent
            anchors.margins: 20
            value: 0.01
        }

        Timer {
            id: timer
            interval: 7
            repeat: true
            running: true
            onTriggered: {
                progressBar.value += 0.01
                if(progressBar.value >= 1.0) {
                    timer.stop();
                    appWindow.visible = true;
                    overlayHeader.visible = true;
                    splashWindow.destroy();
                }
            }
        }
    }

    signal sendAuth(string login, string password)
    signal doEncrypt()
    signal doDecrypt()
    signal sendMes(string message)
    signal sendFile(string fileUrl)
    signal sendFileD(string fileUrlD)
    signal sendPass(string pass)
    signal dbCreate()
    signal dbDelete()
    signal dbAdd(string id, string txt)
    id: appWindow
    visible: true
    width: 640
    height: 480


    header: ToolBar{
        id: overlayHeader
        visible: true
        width: parent.width
        background: Rectangle {
            implicitWidth: 100
            implicitHeight: 48
            border.color: "black"
            color: "#2b2b2e"
        }
        ToolButton{
            onClicked: {
                drawer.open();
            }
            Image{
                source: "file:///C:/Users/Defrixx/Documents/QtDefrixx/Images/menu.png"
                fillMode: Image.PreserveAspectFit
                width: parent.width
                clip: true
            }
        }

        Label {
            id: labelHeader
            anchors.centerIn: parent
            text: {
                if(swipeView.currentIndex == 0){qsTr("Безопасная аутентификация")}
                if(swipeView.currentIndex == 1){qsTr("VK - Friends")}
                if(swipeView.currentIndex == 2){qsTr("Parallax `n Co")}
                if(swipeView.currentIndex == 3){qsTr("Multimedia")}
                if(swipeView.currentIndex == 4){qsTr("Camera")}
                if(swipeView.currentIndex == 5){qsTr("Encryption")}
                if(swipeView.currentIndex == 6){qsTr("Narcissus")}
                if(swipeView.currentIndex == 7){qsTr("Database")}
            }
            font.family: "Areal"
            font.pointSize: 24
            color: "#b6c4cf"

        }

    }


    Drawer{
        id: drawer
        width: 1.3/3*parent.width
        height: parent.height
        interactive: false

        ListView{
            id: lstPagesMenu
            model: navModel
            //model: swipeView.count // цифрой, массивом и ListModel
            anchors.fill: parent
            anchors.margins: 10

            header: ToolButton{
                anchors.right: parent.right
                Image {
                    width: parent.width
                    source: "file:///C:/Users/Defrixx/Documents/QtDefrixx/Images/Back.png"
                    fillMode: Image.PreserveAspectFit
                    clip: true
                }
                onClicked: {
                    drawer.close();
                }
            }

            delegate: Button{
                text: fragment
                width: lstPagesMenu.width
                height: Screen.pixelDensity * 12
                onClicked: {
                    swipeView.currentIndex = index;
                    drawer.close();
                }
            }

        }


    }
    ListModel {
        id: navModel

        ListElement {fragment: "ЛР1: Безопасная аутентификация"}
        ListElement {fragment: "Friends VK"}
        ListElement {fragment: "ЛР2: Parallax `n Co"}
        ListElement {fragment: "ЛР3: Multimedia"}
        ListElement {fragment: "ЛР4: Camera"}
        ListElement {fragment: "ЛР5: Encryption"}
        ListElement {fragment: "ЛР6: Narcissus"}
        ListElement {fragment: "ЛР7: Database"}
    }

    FileDialog {
        id: fileDialog
        visible: fileDialogVisible.checked
        modality: fileDialogModal.checked ? Qt.WindowModal : Qt.NonModal
        title: fileDialogSelectFolder.checked ? "Choose a folder" :
                                                (fileDialogSelectMultiple.checked ? "Choose some files" : "Choose a file")
        selectExisting: fileDialogSelectExisting.checked
        selectMultiple: fileDialogSelectMultiple.checked
        selectFolder: fileDialogSelectFolder.checked
        nameFilters: [ "Txt files (*.txt)", "All files (*)" ]
        selectedNameFilter: "All files (*)"
        sidebarVisible: fileDialogSidebarVisible.checked
        onAccepted: {
            sendFile(fileUrls);
        }
        onRejected: { console.log("Rejected") }
    }
    FileDialog {
        id: fileDialog2
        visible: fileDialogVisible.checked
        modality: fileDialogModal.checked ? Qt.WindowModal : Qt.NonModal
        title: fileDialogSelectFolder.checked ? "Choose a folder" :
                                                (fileDialogSelectMultiple.checked ? "Choose some files" : "Choose a file")
        selectExisting: fileDialogSelectExisting.checked
        selectMultiple: fileDialogSelectMultiple.checked
        selectFolder: fileDialogSelectFolder.checked
        nameFilters: [ "Txt files (*.txt)", "All files (*)" ]
        selectedNameFilter: "All files (*)"
        sidebarVisible: fileDialogSidebarVisible.checked
        onAccepted: {
            sendFileD(fileUrls);
        }
        onRejected: { console.log("Rejected") }
    }


    SwipeView {

        id: swipeView
        anchors.fill: parent
        //currentIndex: tabBar.currentIndex

        Page {//auth

            ColumnLayout{
                anchors.fill: parent;

                Item{ // пустой заполнитель
                    Layout.fillHeight: true
                }

                TextField{
                    id: edtLogin
                    Layout.alignment: Qt.AlignHCenter // центровка
                    placeholderText: "Login"
                    horizontalAlignment: TextInput.AlignHCenter

                    passwordMaskDelay: 1000
                    echoMode: TextInput.Password

                    background: Rectangle{
                        id: loginHighLight
                        anchors.fill: parent;
                        implicitWidth: Screen.pixelDensity * 40
                        color: "transparent" // цвета можно вводить по ARGB "#00000000"
                        border.color: "transparent"

                        ScaleAnimator{
                            id: animation
                            target: loginHighLight; // по отношению к какому элементу применяется анимация
                            // easing: Easing.OutBounce // Тип кривой анимации

                            from: 0.8; // Стартовый масштаб 50%
                            to: 1; // Финальный масштаб 100%
                            duration: 1501 // длительность
                            running: false // по умолчанию анимация остановлена
                        }

                    }

                }

                TextField{
                    id: edtPassword

                    Layout.alignment: Qt.AlignHCenter // центровка
                    placeholderText: "Password"
                    horizontalAlignment: TextInput.AlignHCenter
                    implicitWidth: Screen.pixelDensity * 40

                    passwordMaskDelay: 1000
                    echoMode: TextInput.Password

                    background: Rectangle{
                        id: passwordHighLight
                        anchors.fill: parent;
                        implicitWidth: 200
                        color: "transparent" // цвета можно вводить по ARGB "#00000000"
                        border.color: "transparent"

                        ScaleAnimator{
                            id: animation2
                            target: passwordHighLight; // по отношению к какому элементу применяется анимация
                            // easing: Easing.OutBounce // Тип кривой анимации

                            from: 0.8; // Стартовый масштаб 50%
                            to: 1; // Финальный масштаб 100%
                            duration: 100 // длительность
                            running: false // по умолчанию анимация остановлена
                        }

                    }
                }

                Button{
                    id: btnAuth
                    text: "Auth"
                    Layout.alignment: Qt.AlignHCenter // центровка
                    Layout.minimumHeight: Screen.pixelDensity * 15
                    Layout.minimumWidth: Screen.pixelDensity * 20

                    onClicked: {
                        /* console.log("\n" + "Send Auth`s data" + "\n" + "Login: "+edtLogin.text
                                +"\n"+"Password: "+edtPassword.text + "\n");*/

                        if (edtLogin.text === "" && edtPassword.text === "")
                        {
                            //подсветка периметра красным
                            loginHighLight.border.color = "red";
                            animation.start();
                            edtLogin.placeholderText = "Wrong login!";
                            passwordHighLight.border.color = "red";
                            edtPassword.placeholderText = "Wrong password!";
                            animation2.start();

                            return;
                        }
                        else{
                            loginHighLight.border.color = "transparent";
                        }

                        if(edtLogin.text === "")
                        {
                            //подсветка периметра красным
                            loginHighLight.border.color = "red";
                            animation.start();
                            return;
                        }
                        else
                        {
                            loginHighLight.border.color = "transparent";
                        }

                        if(edtPassword.text === "")
                        {
                            //подсветка периметра красным
                            passwordHighLight.border.color = "red";
                            animation2.start();
                            return;
                        }
                        else
                        {
                            passwordHighLight.border.color = "transparent";
                        }
                        if (edtLogin.text !== "" && edtPassword.text !== "")
                        {
                            sendAuth(edtLogin.text /*Из поля логин*/,
                                     edtPassword.text /*Из поля пароль*/);

                        }

                    }

                }

                Item{ // пустой заполнитель
                    Layout.fillHeight: true
                }
            }
        }

        Page {//friends_VK
            Image{
                source: "file:///C:/Users/Defrixx/Documents/QtDefrixx/Images/Bck_VK.jpg"
                fillMode: Image.TileHorizontally
                y: -myListView.contentY/5
                width: Math.max(myListView.contentWidth, parent.width)
            }
            ListView{
                id: myListView
                model: friends;
                anchors.fill: parent
                anchors.margins: 10

                spacing: 40;

                delegate: Rectangle{ //C(ontrol) из MVC
                    width: parent.width
                    height: Screen.pixelDensity * 20
                    gradient: Gradient{
                        GradientStop {
                            position: 0
                            color: "#251a38"
                        }
                        GradientStop {
                            position: 0.500
                            color: "#ffffff"
                        }
                        GradientStop {
                            position: 1
                            color: "#251a38"
                        }
                    }
                    radius: 10
                    anchors.margins: 20
                    border.color: "purple"
                    border.width: 1
                    Text{text:index; font.bold: true; font.pixelSize: 20}

                    GridLayout {
                        anchors.fill: parent
                        opacity: 1
                        Image {
                            id: avatarVK
                            source: photo
                            anchors.left: parent.left
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.leftMargin: 25
                            anchors.topMargin: 10
                            Layout.row: 1
                            Layout.column: 1
                            Layout.rowSpan: 1
                        }
                    }
                    Text{
                        id: textName
                        font.bold: true;
                        font.pixelSize: 20
                        anchors{
                            verticalCenter: parent.verticalCenter
                            horizontalCenter: parent.horizontalCenter
                        }
                        text: friendname

                    }
                }
            }
        }

        Page {//паралакс

            Image{
                source: "file:///C:/Users/Defrixx/Documents/QtDefrixx/Images/parallax.jpg"
                fillMode: Image.TileHorizontally
                y: -myListView2.contentY/5
                width: Math.max(myListView2.contentWidth, parent.width)
            }
            ListView{
                id: myListView2
                anchors.fill: parent
                anchors.margins: 10
                model: 7 //число компонентов; ["элемен 1","элемен 2","элемен 3"] - число строк; exampleModel M(odel) из MVC

                spacing: 40;

                delegate:
                    Rectangle{ //C(ontrol) из MVC



                    Text{
                        id: textListView2
                        font.bold: true;
                        font.pixelSize: 20
                        anchors{
                            verticalCenter: parent.verticalCenter
                            horizontalCenter: parent.horizontalCenter
                        }
                        text: "TEST"

                    }
                    width: parent.width
                    height: Screen.pixelDensity * 10
                    gradient: Gradient{
                        GradientStop{
                            position:0.00;
                            color:"#fdd0d0";
                        }
                        GradientStop{
                            position:0.49;
                            color:"#ff0000";
                        }
                        GradientStop{
                            position:1.00;
                            color:"#fdd0d0";
                        }
                    }
                    radius: 5
                    border.color: "red"
                    border.width: 1
                    Image{
                        source: "file:///C:/Users/Defrixx/Documents/QtDefrixx/Images/Iconca.png"
                        width: 50
                        height: 50
                        anchors.verticalCenter: parent.verticalCenter
                        clip: true
                    }
                    /*Text{
                                   text:index
                                   font.bold: true
                                   font.pixelSize: 20
                               }*/
                }
            }


        }

        Page {//мультимедиа
            MediaPlayer {
                id: mediaplayer
                autoLoad: true //грузить файл сразу, без команды
                loops: MediaPlayer.Infinite //число повторений
                //autoPlay:true


                /* ТИПЫ URL в QML
                ссылка, рассчитанная на автоопределение источника (ресурсы или файлы)
                source: "sample.mp4"
                source: ":/...."
                source: ":///...."

                // явное указание на ресурсы
                source: "qrc:///...."
                source: "qrc:/...."

                // явное указание на файлы
                source: "file:/...."
                source: "file:///...."
                source: "file:...."*/

                // тернарное условие
                source: (Qt.platform.os === "android")?
                            ("file:///storage/emulated/0/Download/shark.gif"):
                            ("file:///C:/Users/Defrixx/Documents/QtDefrixx/Images/shark.gif")

            }
            ColumnLayout{
                anchors.fill: parent

                VideoOutput {
                    enabled: true
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    //anchors.fill: parent
                    source: mediaplayer //mediaplayer //либо камера
                }
                ProgressBar
                {
                    from:0
                    to:mediaplayer.duration
                    value: mediaplayer.position
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
                Item{ // пустой заполнитель
                    Layout.fillHeight: true
                }
                Item{ // пустой заполнитель
                    Layout.fillHeight: true
                }

                Pane{
                    id: pane2
                    Layout.fillWidth: true
                    RowLayout {
                        width: parent.width
                        Button
                        {
                            id: btnStartPause
                            clip: true
                            Layout.preferredWidth: Screen.pixelDensity * 22
                            Layout.preferredHeight:  Screen.pixelDensity * 8.2
                            //Layout.preferredHeight: Layout.preferrtdHeight/5
                            Layout.alignment: Qt.AlignHCenter
                            background: Item{
                                clip: true
                                id: button3
                                /*property color color: "white"
                                property color hoverColor: "#aaaaaa"
                                property color pressColor: "slategray"
                                property int fontSize: 10
                                property int borderWidth: 1
                                property int borderRadius: 2*/
                                scale: state === "Pressed" ? 0.2 : 1.0
                                onEnabledChanged: state = ""
                                signal clicked

                                //define a scale animation
                                Behavior on scale {
                                    NumberAnimation {
                                        duration: 130
                                        easing.type: Easing.InOutQuad
                                    }
                                }
                                //Mouse area to react on click events
                                MouseArea {
                                    hoverEnabled: true
                                    anchors.fill: button3
                                    onEntered: { button3.state='Hovering'}
                                    onClicked:{
                                        if(mediaplayer.playbackState == MediaPlayer.PausedState || mediaplayer.playbackState == MediaPlayer.StoppedState)
                                        {
                                            mediaplayer.play();
                                            imgIcon.y = -btnStartPause.height * 1.9;
                                        }
                                        else
                                        {
                                            mediaplayer.pause();
                                            imgIcon.y = 0;
                                        }
                                    }
                                    onPressed: { button3.state="Pressed" }
                                    onReleased: {
                                        if (containsMouse)
                                            button3.state="Hovering";
                                        else
                                            button3.state="";
                                    }
                                }
                                Image{//сделать так чтобы картинка кнопки продавливалась, то есть реагировала на нажатия
                                    id: imgIcon
                                    width: parent.width
                                    source: "file:///C:/Users/Defrixx/Documents/QtDefrixx/Images/buttons.png"
                                    fillMode: Image.PreserveAspectFit
                                    clip: true
                                }}
                        }

                        Button{
                            id: btnStartStop
                            clip: true
                            Layout.preferredWidth: Screen.pixelDensity * 22
                            Layout.preferredHeight: Screen.pixelDensity * 10
                            //Layout.preferredHeight: Layout.preferrtdHeight/5
                            Layout.alignment: Qt.AlignHCenter
                            background: Item{
                                clip: true
                                id: button4
                                /*property color color: "white"
                                property color hoverColor: "#aaaaaa"
                                property color pressColor: "slategray"
                                property int fontSize: 10
                                property int borderWidth: 1
                                property int borderRadius: 2*/
                                scale: state === "Pressed" ? 0.96 : 1.0
                                onEnabledChanged: state = ""
                                signal clicked

                                //define a scale animation

                                //Mouse area to react on click events
                                MouseArea {
                                    hoverEnabled: true
                                    anchors.fill: button4
                                    //onEntered: { button4.state='Hovering'}
                                    onClicked:{
                                        if(mediaplayer.playbackState == MediaPlayer.PlayingState || mediaplayer.playbackState == MediaPlayer.PausedState)
                                        {
                                            mediaplayer.stop();
                                            imgIcon.y = 0;
                                            //imgIcon2.y = -btnStartStop.height * 1.9;
                                        }
                                    }
                                    onPressed: { button4.state="Pressed" }
                                    onReleased: {
                                        if (containsMouse)
                                            button4.state="Hovering";
                                        else
                                            button4.state="";
                                    }
                                }
                                Image{//сделать так чтобы картинка кнопки продавливалась, то есть реагировала на нажатия
                                    id: imgIcon2
                                    width: 50
                                    height: 50
                                    source: "file:///C:/Users/Defrixx/Documents/QtDefrixx/Images/btn.png"
                                    fillMode: Image.PreserveAspectFit
                                    clip: true
                                }
                            }
                        }
                    }
                }
                /*


                        Image{//сделать так чтобы картинка кнопки продавливалась, то есть реагировала на нажатия
                            id: imgIcon
                            width: parent.width
                            source: "file:///C:/Users/Defrixx/Documents/QtDefrixx/Images/buttons.png"
                            fillMode: Image.PreserveAspectFit
                            clip: true
                        }}
                    onClicked:{
                        if(mediaplayer.playbackState == MediaPlayer.PausedState || mediaplayer.playbackState == MediaPlayer.StoppedState)
                        {
                            mediaplayer.play();
                            //text = "Stop"
                            imgIcon.y = -btnStartStop.height * 3.8;
                        }
                        else
                        {
                            mediaplayer.stop();
                            //text = "Start"
                            imgIcon.y = 0;
                        }
                    }
                }*/
                Item{ // пустой заполнитель
                    Layout.fillHeight: true
                }
                Item{ // пустой заполнитель
                    Layout.fillHeight: true
                }
                Item{ // пустой заполнитель
                    Layout.fillHeight: true
                }
                Item{ // пустой заполнитель
                    Layout.fillHeight: true
                }
            }

        }

        Page {//камера
            Camera{
                id:camera
            }
            ColumnLayout{
                anchors.fill: parent

                VideoOutput {
                    enabled: true
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    //anchors.fill: parent
                    source: camera //mediaplayer //либо camera
                }
                Pane{
                    id: pane3
                    Layout.fillWidth: true
                    RowLayout {
                        width: parent.width
                        Button{
                            text: "Сделать фото"
                            Layout.alignment: Qt.AlignHCenter // центровка
                            Layout.minimumHeight: Screen.pixelDensity * 10
                            Layout.minimumWidth: Screen.pixelDensity * 10
                            onClicked:{
                                camera.imageCapture.capture();
                            }
                        }
                        Button{

                            text: "Записать видео"
                            Layout.alignment: Qt.AlignHCenter // центровка
                            Layout.minimumHeight: Screen.pixelDensity * 10
                            Layout.minimumWidth: Screen.pixelDensity * 10
                            onClicked:{
                                camera.captureMode= Camera.CaptureVideo
                                console.log(camera.videoRecorder)
                                if(camera.videoRecorder.recorderState == CameraRecorder.StoppedState)
                                {
                                    camera.videoRecorder.record();
                                    text="Записать\nвидео"
                                    console.log("*** actualLocation =", camera.actualLocation)
                                    console.log("*** outputLocation =", camera.outputLocation)
                                }
                            }
                        }
                        Button{

                            text: "Остановить запись\nвидео"
                            Layout.alignment: Qt.AlignHCenter // центровка
                            Layout.minimumHeight: Screen.pixelDensity * 10
                            Layout.minimumWidth: Screen.pixelDensity * 10
                            onClicked:{
                                if (camera.videoRecorder.recorderState == CameraRecorder.RecordingState)
                                {
                                    camera.videoRecorder.stop();
                                    console.log("*** actualLocation =", camera.actualLocation)
                                    console.log("*** outputLocation =", camera.outputLocation)
                                }
                            }
                        }
                    }
                }
            }
        }

        Page{//шифрование

            ColumnLayout{
                anchors.fill: parent

                Item{ // пустой заполнитель
                    Layout.fillHeight: true
                }
               /* Pane {
                    id: paneAgree
                    Layout.fillWidth: true

                    RowLayout {
                        width: parent.width

                        TextField {
                            id: txtForAgree
                            Layout.fillWidth: true
                            placeholderText: qsTr("Compose password")
                            wrapMode: TextField.Wrap

                            passwordMaskDelay: 1000
                            echoMode: TextField.Password
                        }

                        Button {
                            id: sendAgree
                            text: qsTr("Send")
                            enabled: (txtForAgree.length > 0 )
                            onClicked: {
                                if (txtForAgree.text === "1234")
                                {
                                    paneAgree.visible = false;
                                    btnChFile.visible = true;
                                    btnDec.visible = true;
                                }
                            }
                        }
                    }
                }*/



                Button{
                    id: btnChFile
                    text: "Encrypt"
                    //visible: false
                    Layout.alignment: Qt.AlignHCenter // центровка
                    Layout.minimumHeight: Screen.pixelDensity * 15
                    Layout.minimumWidth: Screen.pixelDensity * 20

                    onClicked: {
                        fileDialog.open();
                    }
                }
                Pane {
                                    id: paneAgree
                                    Layout.fillWidth: true

                                    RowLayout {
                                        width: parent.width

                                        TextField {
                                            id: txtForAgree
                                            Layout.fillWidth: true
                                            placeholderText: qsTr("Compose key for Decrypt")
                                            wrapMode: TextField.Wrap
                                            passwordMaskDelay: 1000
                                            echoMode: TextField.Password
                                        }

                                        Button {
                                            id: sendAgree
                                            text: qsTr("Do")
                                            enabled: (txtForAgree.length > 0 )
                                            onClicked: {
                                                if (txtForAgree.text === "123456789"){
                                                fileDialog2.open();}
                                            }
                                        }
                                    }
                                }

                /*Button{
                    id: btnDec
                    text: "Decrypt"
                    visible: false
                    Layout.alignment: Qt.AlignHCenter // центровка
                    Layout.minimumHeight: Screen.pixelDensity * 15
                    Layout.minimumWidth: Screen.pixelDensity * 20

                    onClicked: {
                        fileDialog2.open();
                    }
                }*/
                Item{ // пустой заполнитель
                    Layout.fillHeight: true
                }
            }

        }

        Page{//чатик

            Image{
                source: "file:///C:/Users/Defrixx/Documents/QtDefrixx/Images/bck_Chat.png"
                fillMode: Image.TileHorizontally
                y: -listViewChat.content
                width: Math.max(listViewChat.contentWidth, parent.width)
            }

            ColumnLayout{
                anchors.fill: parent


                ListView {
                    id: listViewChat
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    //Layout.margins: pane.leftPadding + messageField.leftPadding
                    displayMarginBeginning: 40
                    displayMarginEnd: 40
                    verticalLayoutDirection: ListView.BottomToTop
                    spacing: 12
                    model: 10
                    delegate: Row {
                        readonly property bool sentByMe: index % 2 == 0

                        anchors.right: sentByMe ? parent.right : undefined
                        spacing: 6


                        Rectangle {
                            width: 80
                            height: 40
                            color: sentByMe ? "lightgrey" : "steelblue"

                            Label {
                                id: messageText
                                anchors.centerIn: parent
                                text: index
                                color: sentByMe ? "black" : "white"
                            }
                        }
                    }

                    ScrollBar.vertical: ScrollBar {}
                }
                Pane {
                    id: pane
                    Layout.fillWidth: true

                    RowLayout {
                        width: parent.width

                        TextArea {
                            id: txtForMes
                            Layout.fillWidth: true
                            placeholderText: qsTr("Compose message")
                            wrapMode: TextArea.Wrap
                        }

                        Button {
                            id: sendButton
                            text: qsTr("Send")
                            enabled: txtForMes.length > 0
                            onClicked: {
                                sendMes(txtForMes.text);
                            }
                        }
                    }
                }
                /*ListView{
                id: chatContent
                model: 2 //число компонентов; ["элемен 1","элемен 2","элемен 3"] - число строк; exampleModel M(odel) из MVC
                spacing: 40;
                Layout.alignment: Qt.AlignHCenter // центровка
                Layout.minimumHeight: Screen.pixelDensity * 30
                Layout.minimumWidth: Screen.pixelDensity * 30

                delegate: Rectangle{
                    id: recClient//C(ontrol) из MVC

                    Text{
                        anchors.right: recClient.left

                        text: "Client"

                    }
                }
                          Rectangle{
                    id: recServer

                    Text{
                        anchors.left: recServer.right
                        text: "Server"
                    }

                }
            }*/
            }

        }

        Page{//база данных
            ColumnLayout{
                anchors.fill: parent

                Item{ // пустой заполнитель
                    Layout.fillHeight: true
                }
                Button{
                    id: dbCreate2
                    text: "Create database"
                    Layout.alignment: Qt.AlignHCenter // центровка
                    Layout.minimumHeight: Screen.pixelDensity * 15
                    Layout.minimumWidth: Screen.pixelDensity * 20

                    onClicked: {
                        dbCreate();
                    }
                }
                Button{
                    id: dbDelete2
                    text: "Delete database"
                    Layout.alignment: Qt.AlignHCenter // центровка
                    Layout.minimumHeight: Screen.pixelDensity * 15
                    Layout.minimumWidth: Screen.pixelDensity * 20

                    onClicked: {
                        dbDelete();
                    }
                }
                Item{ // пустой заполнитель
                    Layout.fillHeight: true
                }
                /*Text{
                    horizontalAlignment: Text.AlignHCenter
                    color: "white"
                    text: "---------------------------------------------------------------------------------"
                }*/
                Item{ // пустой заполнитель
                    Layout.fillHeight: true
                }

                Pane {
                    id: paneDB
                    Layout.fillWidth: true

                    RowLayout {
                        width: parent.width

                        TextArea {
                            id: txtForDB
                            Layout.fillWidth: true
                            placeholderText: qsTr("Compose id")
                            wrapMode: TextArea.Wrap
                        }
                        TextArea {
                            id: txtForDBcompose
                            Layout.fillWidth: true
                            placeholderText: qsTr("Compose message")
                            wrapMode: TextArea.Wrap
                        }

                        Button {
                            id: sendButtonDB
                            text: qsTr("Send")
                            enabled: (txtForDB.length > 0 || txtForDBcompose.length > 0)
                            onClicked: {
                                dbAdd(txtForDB.text,
                                      txtForDBcompose.text);
                            }
                        }
                    }
                }
            }

        }
    }



    // панелька снизу с кнопками для перехода на нужные страницы
    /* header: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton {
            text: qsTr("Auth")
        }
        TabButton{
            text: qsTr("ListView")
        }
        TabButton{
            text: qsTr("MediaPlayer")
        }
        TabButton{
            text: qsTr("Camera")
        }
        TabButton{
            text: qsTr("Encryption")
        }
    }
    */

    /*Connections{
        target: authController // подсвечивается - значит успешно введен в область видимости QML из C++

        onAuthsuccess: {
            console.log ("*** authsuccess");
        }
    }*/
}
