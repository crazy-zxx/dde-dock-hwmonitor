// SPDX-FileCopyrightText: 2026 HwMonitor contributors
//
// SPDX-License-Identifier: GPL-3.0-or-later

import QtQuick
import QtQuick.Controls 2.15
import org.deepin.ds 1.0
import org.deepin.ds.dock 1.0
import org.deepin.dtk 1.0 as D

AppletItem {
    id: root

    // ---- 从 C++ Applet 获取后端与设置 ----
    readonly property var backend: Applet.monitor
    readonly property var settings: Applet.settings

    // ---- Dock 排序与可见性 ----
    // dockOrder 决定所在区域：左侧 0~10、中间 10~20、右侧 20~30（托盘附近）
    property int dockOrder: settings.dockPosition === "left" ? 5 : 21
    // shouldVisible 由 Dock 过滤：false 时插件从任务栏隐藏。
    property bool shouldVisible: settings ? settings.enabled : true

    // ---- 布局 ----
    readonly property bool inPanel: (typeof Panel !== "undefined") && Panel.rootObject !== null && Panel.rootObject !== undefined
    readonly property bool useColumnLayout: inPanel && (Panel.position % 2 === 1)
    readonly property int dockSize: inPanel ? Panel.rootObject.dockSize : 48

    // 文字大小与字体来自设置面板（默认 10px / Source Han Mono SC）
    readonly property int fontSize: settings && settings.fontSize > 0 ? settings.fontSize : 10
    readonly property string monoFontFamily: settings && settings.fontFamily ? settings.fontFamily : "Source Han Mono SC"
    // 拉丁字母和 CJK 字体回退的 ascent/descent 可能不同，统一行盒后再垂直居中。
    readonly property int textLineHeight: Math.max(fontSize + 4, 16)

    // 用于按字符数固定条目宽度
    TextMetrics {
        id: charMetrics
        font.family: root.monoFontFamily
        font.pixelSize: root.fontSize
        font.bold: true
        text: "0"
    }
    readonly property real charWidth: charMetrics.advanceWidth

    // ---- 主题感知的文字颜色 ----
    readonly property color textColor: {
        if (settings.useCustomColor) {
            return Applet.themeType === D.ApplicationHelper.DarkType
                    ? settings.textColorDark : settings.textColorLight
        }
        return Applet.themeType === D.ApplicationHelper.DarkType ? "#F2F2F2" : "#202020"
    }

    // ---- 按顺序过滤出可见的监控项 ----
    readonly property var items: {
        var result = []
        var keys = settings.itemOrder
        for (var i = 0; i < keys.length; i++) {
            var key = keys[i]
            if (settings.itemVisible[key] !== false)
                result.push(key)
        }
        return result
    }
    readonly property var row1Model: settings.displayMode === "double"
            ? items.slice(0, Math.ceil(items.length / 2)) : items
    readonly property var row2Model: settings.displayMode === "double"
            ? items.slice(Math.ceil(items.length / 2)) : []

    function formatSpeed(bps) {
        if (bps >= 1024 * 1024)
            return (bps / 1024 / 1024).toFixed(1) + "M"
        if (bps >= 1024)
            return (bps / 1024).toFixed(0) + "K"
        return Math.max(0, bps).toFixed(0) + "B"
    }

    function itemLabel(key) {
        switch (key) {
        case "cpu": return qsTr("CPU")
        case "memory": return qsTr("内存")
        case "gpu": return qsTr("GPU")
        case "gpumem": return qsTr("显存")
        case "cputemp": return qsTr("CPU")
        case "gputemp": return qsTr("GPU")
        case "netup": return "↑"
        case "netdown": return "↓"
        }
        return ""
    }

    function itemValue(key) {
        switch (key) {
        case "cpu": return backend.cpuUsage.toFixed(0) + "%"
        case "memory": return backend.memUsage.toFixed(0) + "%"
        case "gpu": return backend.gpuAvailable ? backend.gpuUsage.toFixed(0) + "%" : qsTr("N/A")
        case "gpumem": return backend.gpuMemoryAvailable ? backend.gpuMemoryUsage.toFixed(0) + "%" : qsTr("N/A")
        case "cputemp": return backend.cpuTempAvailable ? backend.cpuTemp.toFixed(0) + "°" : qsTr("N/A")
        case "gputemp": return backend.gpuTempAvailable ? backend.gpuTemp.toFixed(0) + "°" : qsTr("N/A")
        case "netup": return formatSpeed(backend.netUpSpeed)
        case "netdown": return formatSpeed(backend.netDownSpeed)
        }
        return ""
    }


    // 单行显示条目组件：数值可按字符数固定占位宽度，避免数值位数变化引起抖动
    component MonitorText: Row {
        property string itemKey: ""
        height: root.textLineHeight
        spacing: 2
        readonly property int reservedChars: (root.settings.itemWidth[itemKey] || 0)
        Text {
            text: root.itemLabel(itemKey)
            height: root.textLineHeight
            verticalAlignment: Text.AlignVCenter
            color: root.textColor
            font.family: root.monoFontFamily
            font.pixelSize: root.fontSize
            font.bold: true
        }
        Text {
            text: root.itemValue(itemKey)
            height: root.textLineHeight
            verticalAlignment: Text.AlignVCenter
            color: root.textColor
            font.family: root.monoFontFamily
            font.pixelSize: root.fontSize
            font.bold: true
            width: reservedChars > 0 ? reservedChars * root.charWidth : contentWidth
            horizontalAlignment: Text.AlignLeft
            clip: reservedChars > 0
        }
    }

    implicitWidth: useColumnLayout ? dockSize : (horizontalContent.visible ? horizontalContent.implicitWidth : 0) + 16
    implicitHeight: useColumnLayout ? (verticalContent.visible ? verticalContent.implicitHeight : 0) + 16 : dockSize

    // ================= 垂直 Dock（左/右）：纵向排列 =================
    Column {
        id: verticalContent
        visible: root.useColumnLayout
        anchors.centerIn: parent
        spacing: 1
        Repeater {
            model: root.items
            delegate: MonitorText { itemKey: modelData }
        }
    }

    // ================= 水平 Dock（上/下）：单行或双行 =================
    Column {
        id: horizontalContent
        visible: !root.useColumnLayout
        anchors.centerIn: parent
        spacing: 0

        Row {
            id: row1
            spacing: Math.max(4, Math.round(root.dockSize * 0.16))
            Repeater {
                model: root.row1Model
                delegate: MonitorText { itemKey: modelData }
            }
        }

        Row {
            id: row2
            visible: root.settings.displayMode === "double" && root.row2Model.length > 0
            spacing: Math.max(4, Math.round(root.dockSize * 0.16))
            Repeater {
                model: root.row2Model
                delegate: MonitorText { itemKey: modelData }
            }
        }
    }

    // ================= 交互：左键打开设置面板 =================
    MouseArea {
        id: clickArea
        anchors.fill: parent
        acceptedButtons: Qt.LeftButton
        hoverEnabled: true
        onClicked: root.openSettings()
    }

    function openSettings() {
        settingsPopup.DockPanelPositioner.bounding = Qt.binding(function () {
            var point = root.mapToItem(null, root.width / 2, root.height / 2)
            return Qt.rect(point.x, point.y, settingsPopup.width, settingsPopup.height)
        })
        settingsPopup.open()
    }

    // 退出监控：关闭设置面板并持久化禁用；后端收到 enabledChanged 后停止采集。
    // 不退出 dde-shell 进程，避免影响 Dock 的主题、窗口和其他插件状态。
    function quitApp() {
        settingsPopup.close()
        if (root.settings)
            root.settings.setEnabled(false)
    }

    PanelPopup {
        id: settingsPopup
        width: settingsPanel.width
        height: settingsPanel.height
        popupX: inPanel ? DockPanelPositioner.x : 0
        popupY: inPanel ? DockPanelPositioner.y : 0

        SettingsPanel {
            id: settingsPanel
            settings: root.settings
            monitor: Applet.monitor
            themeType: Applet.themeType
            onQuitRequested: root.quitApp()
        }
    }
}
