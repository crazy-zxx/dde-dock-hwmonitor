cmake_minimum_required(VERSION 3.16)

project(dde-shell-hwmonitor VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(DDEShell REQUIRED)
find_package(Dtk6Core REQUIRED)
find_package(Dtk6Gui REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick LinguistTools)

set(PLUGIN_ID org.deepin.ds.dock.hwmonitor)

add_library(ds-dock-hwmonitor SHARED
    hwmonitorapplet.h
    hwmonitorapplet.cpp
    monitorbackend.h
    monitorbackend.cpp
    settings.h
    settings.cpp
)
target_link_libraries(ds-dock-hwmonitor PRIVATE
    Dde::Shell
    Dtk6::Core
    Dtk6::Gui
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

# DConfig 元数据：appId=org.deepin.dde.shell（与 dde-shell 插件一致），configId=插件 ID
install(FILES configs/${PLUGIN_ID}.json
        DESTINATION /usr/share/dsg/configs/org.deepin.dde.shell/)

# 开始菜单启动图标（.desktop + 图标 + 启动脚本）
install(FILES data/${PLUGIN_ID}.desktop
        DESTINATION /usr/share/applications/)
install(FILES data/icons/${PLUGIN_ID}.svg
        DESTINATION /usr/share/icons/hicolor/scalable/apps/)
# 多尺寸 PNG 图标（开始菜单对各尺寸 PNG 兼容性最好）
foreach(ICON_SIZE 16 24 32 48 64 128 256)
    install(FILES data/icons/hicolor/${ICON_SIZE}x${ICON_SIZE}/apps/${PLUGIN_ID}.png
            DESTINATION /usr/share/icons/hicolor/${ICON_SIZE}x${ICON_SIZE}/apps/)
endforeach()
install(PROGRAMS data/hwmonitor-launcher.sh
        DESTINATION /usr/bin RENAME hwmonitor-launcher)

ds_install_package(PACKAGE ${PLUGIN_ID} TARGET ds-dock-hwmonitor)
ds_handle_package_translation(PACKAGE ${PLUGIN_ID})
