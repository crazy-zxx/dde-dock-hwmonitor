// SPDX-FileCopyrightText: 2026 HwMonitor contributors
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls 2.15
import Qt.labs.platform 1.1 as LP
import org.deepin.dtk 1.0 as D

Item {
    id: root

    // 由 main.qml 显式传入，避免在弹窗窗口内解析 Applet 附加属性
    property var settings: null
    property var monitor: null
    property int themeType: 0

    readonly property bool isDark: themeType === D.ApplicationHelper.DarkType
    readonly property color textColor: isDark ? "#E6E6E6" : "#202020"
    readonly property color subTextColor: isDark ? "#99E6E6E6" : "#66202020"

    width: 370
    readonly property real contentHeight: contentCol.childrenRect.height + 40
    height: Math.min(560, Math.max(340, contentHeight))

    // 点击“退出监控”时发出，由 main.qml 负责关闭弹窗并禁用插件
    signal quitRequested()


    function itemName(key) {
        switch (key) {
        case "cpu": return qsTr("CPU 使用率")
        case "memory": return qsTr("内存使用率")
        case "gpu": return qsTr("GPU 使用率")
        case "gpumem": return qsTr("显存占用")
        case "cputemp": return qsTr("CPU 温度")
        case "gputemp": return qsTr("GPU 温度")
        case "netup": return qsTr("上传速度")
        case "netdown": return qsTr("下载速度")
        }
        return key
    }

    readonly property var fontModel: ["Source Han Mono SC", "Noto Sans Mono CJK SC", "DejaVu Sans Mono", "Noto Mono", "Source Code Pro", "Liberation Mono", qsTr("系统默认")]

    readonly property var netIfModel: [qsTr("全部接口")].concat(root.monitor ? root.monitor.netInterfaces : [])
    readonly property int netIfIndex: {
        var target = root.settings && root.settings.netInterface ? root.settings.netInterface : ""
        var idx = root.netIfModel.indexOf(target)
        return idx < 0 ? 0 : idx
    }

    function moveItem(index, direction) {
        var list = settings.itemOrder.slice()
        var to = index + direction
        if (to < 0 || to >= list.length)
            return
        var tmp = list[index]
        list[index] = list[to]
        list[to] = tmp
        settings.setItemOrder(list)
    }

    Flickable {
        id: flick
        anchors.fill: parent
        clip: true
        contentWidth: width
        contentHeight: contentCol.childrenRect.height + 40
        boundsBehavior: Flickable.StopAtBounds
        ScrollBar.vertical: ScrollBar {
            policy: ScrollBar.AsNeeded
        }

        Column {
            id: contentCol
            x: 16
            y: 16
            width: flick.width - 32
            spacing: 12


        // ---------- 标题 ----------
        Text {
            text: qsTr("硬件监控设置")
            font.pixelSize: 16
            font.bold: true
            color: root.textColor
        }

        // ---------- 显示模式 ----------
        Text {
            text: qsTr("显示模式")
            font.pixelSize: 13
            color: root.subTextColor
        }
        Row {
            spacing: 16
            D.RadioButton {
                text: qsTr("单行")
                checked: root.settings && root.settings.displayMode === "single"
                onToggled: if (checked && root.settings) root.settings.setDisplayMode("single")
            }
            D.RadioButton {
                text: qsTr("双行")
                checked: root.settings && root.settings.displayMode === "double"
                onToggled: if (checked && root.settings) root.settings.setDisplayMode("double")
            }
        }

        // ---------- 显示位置 ----------
        Text {
            text: qsTr("显示位置")
            font.pixelSize: 13
            color: root.subTextColor
        }
        Row {
            spacing: 16
            D.RadioButton {
                text: qsTr("左侧")
                checked: root.settings && root.settings.dockPosition === "left"
                onToggled: if (checked && root.settings) root.settings.setDockPosition("left")
            }
            D.RadioButton {
                text: qsTr("右侧")
                checked: root.settings && root.settings.dockPosition === "right"
                onToggled: if (checked && root.settings) root.settings.setDockPosition("right")
            }
        }

        // ---------- 监视网卡 ----------
        Text {
            text: qsTr("监视网卡")
            font.pixelSize: 13
            color: root.subTextColor
        }
        D.ComboBox {
            id: netIfCombo
            width: 220
            height: 30
            model: root.netIfModel
            Component.onCompleted: currentIndex = root.netIfIndex
            onActivated: function (index) {
                if (root.settings)
                    root.settings.setNetInterface(index === 0 ? "" : root.netIfModel[index])
            }
        }

        // ---------- 监控项 ----------
        Text {
            text: qsTr("监控项（勾选显示，可排序）")
            font.pixelSize: 13
            color: root.subTextColor
        }
        Column {
            spacing: 2
            height: root.settings ? root.settings.itemOrder.length * 30 : 0
            Repeater {
                model: root.settings ? root.settings.itemOrder : []
                delegate: Row {
                    id: itemRow
                    required property string modelData
                    spacing: 8
                    height: 28

                    D.CheckBox {
                        width: 24
                        height: 24
                        anchors.verticalCenter: parent.verticalCenter
                        checked: root.settings.itemVisible[itemRow.modelData] !== false
                        onToggled: root.settings.setItemVisible(itemRow.modelData, checked)
                    }
                    Text {
                        text: root.itemName(itemRow.modelData)
                        font.pixelSize: 13
                        color: root.textColor
                        anchors.verticalCenter: parent.verticalCenter
                        width: 96
                        elide: Text.ElideRight
                    }

                    D.SpinBox {
                        id: widthSpin
                        width: 56
                        height: 26
                        anchors.verticalCenter: parent.verticalCenter
                        from: 0
                        to: 20
                        editable: true
                        property bool initialized: false
                        Component.onCompleted: {
                            value = root.settings.itemWidth[itemRow.modelData] || 0
                            initialized = true
                        }
                        // 与字体大小一致：DTK SpinBox 聚焦后上下按钮不发射 valueModified，
                        // 通过 valueChanged 仅在初始化完成且数值变化时写回设置。
                        onValueChanged: {
                            if (initialized && root.settings) {
                                var saved = root.settings.itemWidth[itemRow.modelData] || 0
                                if (Math.round(value) !== saved)
                                    root.settings.setItemWidth(itemRow.modelData, Math.round(value))
                            }
                        }
                        onValueModified: {
                            if (root.settings)
                                root.settings.setItemWidth(itemRow.modelData, Math.round(value))
                        }
                        ToolTip.visible: hovered
                        ToolTip.text: qsTr("数值占位字符数，0 表示自动")
                    }
                    Text {
                        text: qsTr("字符")
                        font.pixelSize: 11
                        color: root.subTextColor
                        anchors.verticalCenter: parent.verticalCenter
                        width: 26
                    }
                    Item { width: 4; height: 1 }

                    D.ToolButton {
                        text: "↑"
                        width: 24
                        height: 24
                        anchors.verticalCenter: parent.verticalCenter
                        enabled: root.settings.itemOrder.indexOf(itemRow.modelData) > 0
                        onClicked: {
                            var idx = root.settings.itemOrder.indexOf(itemRow.modelData)
                            root.moveItem(idx, -1)
                        }
                    }
                    D.ToolButton {
                        text: "↓"
                        width: 24
                        height: 24
                        anchors.verticalCenter: parent.verticalCenter
                        enabled: root.settings.itemOrder.indexOf(itemRow.modelData) < root.settings.itemOrder.length - 1
                        onClicked: {
                            var idx = root.settings.itemOrder.indexOf(itemRow.modelData)
                            root.moveItem(idx, 1)
                        }
                    }
                }
            }
        }

        // ---------- 文字字体 ----------
        Text {
            text: qsTr("文字字体")
            font.pixelSize: 13
            color: root.subTextColor
        }
        Row {
            spacing: 12
            D.ComboBox {
                id: fontCombo
                width: 172
                height: 30
                model: root.fontModel
                Component.onCompleted: {
                    var fam = root.settings ? root.settings.fontFamily : ""
                    var idx = root.fontModel.indexOf(fam)
                    if (idx < 0 && fam === "monospace")
                        idx = root.fontModel.length - 1
                    currentIndex = idx >= 0 ? idx : 0
                }
                onActivated: function (index) {
                    if (root.settings)
                        root.settings.setFontFamily(index === root.fontModel.length - 1 ? "monospace" : root.fontModel[index])
                }
            }
            D.SpinBox {
                id: fontSizeSpin
                width: 70
                height: 30
                from: 6
                to: 24
                editable: true
                // 初始化完成标志：SpinBox 在 C++ componentComplete 阶段会把默认值 0 钳制到
                // from(6) 并发射 valueChanged，若此时写回会污染设置，故完成初始化前不写。
                property bool initialized: false
                Component.onCompleted: {
                    value = root.settings ? root.settings.fontSize : 10
                    initialized = true
                }
                // DTK SpinBox 在获得焦点（例如输入回车后）时，上下按钮会切换到内部 Button，
                // 其 onClicked 直接调用 increase()/decrease()，此时不会发射 valueModified 信号，
                // 导致设置不会保存（表现为“上下按钮失效”）。因此再监听 valueChanged，
                // 仅在初始化完成且数值与当前设置不同时写回。
                onValueChanged: {
                    if (initialized && root.settings && Math.round(value) !== root.settings.fontSize)
                        root.settings.setFontSize(Math.round(value))
                }
                onValueModified: {
                    if (root.settings)
                        root.settings.setFontSize(Math.round(value))
                }
                ToolTip.visible: hovered
                ToolTip.text: qsTr("文字大小（像素）")
            }
            Text {
                text: qsTr("px")
                font.pixelSize: 13
                color: root.subTextColor
                anchors.verticalCenter: parent.verticalCenter
            }
        }

        // ---------- 文字颜色 ----------
        Row {
            width: parent.width
            Text {
                text: qsTr("文字颜色")
                font.pixelSize: 13
                color: root.subTextColor
                anchors.verticalCenter: parent.verticalCenter
            }
            Item { width: 8; height: 1 }

            D.ToolButton {
                width: 24
                height: 24
                ToolTip.visible: hovered
                ToolTip.text: qsTr("还原默认文字颜色")
                onClicked: if (root.settings) root.settings.resetTextColors()
                contentItem: D.DciIcon {
                    name: "edit-undo"
                    sourceSize: Qt.size(14, 14)
                }
            }
        }
        Row {
            spacing: 12
            D.Switch {
                anchors.verticalCenter: parent.verticalCenter
                checked: root.settings && root.settings.useCustomColor
                onToggled: root.settings.setUseCustomColor(checked)
            }
            Text {
                text: qsTr("使用自定义颜色")
                font.pixelSize: 13
                color: root.textColor
                anchors.verticalCenter: parent.verticalCenter
            }
        }
        Row {
            spacing: 24
            // 亮色主题颜色
            Row {
                spacing: 8
                Text {
                    text: qsTr("亮色主题")
                    font.pixelSize: 13
                    color: root.textColor
                    anchors.verticalCenter: parent.verticalCenter
                }
                Rectangle {
                    width: 36
                    height: 24
                    radius: 4
                    border.color: "#66000000"
                    color: root.settings ? root.settings.textColorLight : "#000000"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: lightColorDialog.open()
                    }
                }
            }
            // 暗色主题颜色
            Row {
                spacing: 8
                Text {
                    text: qsTr("暗色主题")
                    font.pixelSize: 13
                    color: root.textColor
                    anchors.verticalCenter: parent.verticalCenter
                }
                Rectangle {
                    width: 36
                    height: 24
                    radius: 4
                    border.color: "#66000000"
                    color: root.settings ? root.settings.textColorDark : "#FFFFFF"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: darkColorDialog.open()
                    }
                }
            }
        }

        // ---------- 退出监控 ----------
        Item { width: 1; height: 6 }
        D.Button {
            text: qsTr("退出监控")
            onClicked: root.quitRequested()
        }
            }
    }

    LP.ColorDialog {
        id: lightColorDialog
        title: qsTr("选择亮色主题文字颜色")
        color: root.settings ? root.settings.textColorLight : "#000000"
        onAccepted: if (root.settings) root.settings.setTextColorLight(color.toString())
    }

    LP.ColorDialog {
        id: darkColorDialog
        title: qsTr("选择暗色主题文字颜色")
        color: root.settings ? root.settings.textColorDark : "#FFFFFF"
        onAccepted: if (root.settings) root.settings.setTextColorDark(color.toString())
    }

}
