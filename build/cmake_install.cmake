# Install script for directory: /home/zhao/Desktop/AI/dde-dock-hwmonitor

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/share/dsg/configs/org.deepin.dde.shell/org.deepin.ds.dock.hwmonitor.json")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/share/dsg/configs/org.deepin.dde.shell" TYPE FILE FILES "/home/zhao/Desktop/AI/dde-dock-hwmonitor/configs/org.deepin.ds.dock.hwmonitor.json")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/share/applications/org.deepin.ds.dock.hwmonitor.desktop")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/share/applications" TYPE FILE FILES "/home/zhao/Desktop/AI/dde-dock-hwmonitor/data/org.deepin.ds.dock.hwmonitor.desktop")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/share/icons/hicolor/scalable/apps/org.deepin.ds.dock.hwmonitor.svg")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/share/icons/hicolor/scalable/apps" TYPE FILE FILES "/home/zhao/Desktop/AI/dde-dock-hwmonitor/data/icons/org.deepin.ds.dock.hwmonitor.svg")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/share/icons/hicolor/16x16/apps/org.deepin.ds.dock.hwmonitor.png")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/share/icons/hicolor/16x16/apps" TYPE FILE FILES "/home/zhao/Desktop/AI/dde-dock-hwmonitor/data/icons/hicolor/16x16/apps/org.deepin.ds.dock.hwmonitor.png")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/share/icons/hicolor/24x24/apps/org.deepin.ds.dock.hwmonitor.png")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/share/icons/hicolor/24x24/apps" TYPE FILE FILES "/home/zhao/Desktop/AI/dde-dock-hwmonitor/data/icons/hicolor/24x24/apps/org.deepin.ds.dock.hwmonitor.png")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/share/icons/hicolor/32x32/apps/org.deepin.ds.dock.hwmonitor.png")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/share/icons/hicolor/32x32/apps" TYPE FILE FILES "/home/zhao/Desktop/AI/dde-dock-hwmonitor/data/icons/hicolor/32x32/apps/org.deepin.ds.dock.hwmonitor.png")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/share/icons/hicolor/48x48/apps/org.deepin.ds.dock.hwmonitor.png")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/share/icons/hicolor/48x48/apps" TYPE FILE FILES "/home/zhao/Desktop/AI/dde-dock-hwmonitor/data/icons/hicolor/48x48/apps/org.deepin.ds.dock.hwmonitor.png")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/share/icons/hicolor/64x64/apps/org.deepin.ds.dock.hwmonitor.png")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/share/icons/hicolor/64x64/apps" TYPE FILE FILES "/home/zhao/Desktop/AI/dde-dock-hwmonitor/data/icons/hicolor/64x64/apps/org.deepin.ds.dock.hwmonitor.png")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/share/icons/hicolor/128x128/apps/org.deepin.ds.dock.hwmonitor.png")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/share/icons/hicolor/128x128/apps" TYPE FILE FILES "/home/zhao/Desktop/AI/dde-dock-hwmonitor/data/icons/hicolor/128x128/apps/org.deepin.ds.dock.hwmonitor.png")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/share/icons/hicolor/256x256/apps/org.deepin.ds.dock.hwmonitor.png")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/share/icons/hicolor/256x256/apps" TYPE FILE FILES "/home/zhao/Desktop/AI/dde-dock-hwmonitor/data/icons/hicolor/256x256/apps/org.deepin.ds.dock.hwmonitor.png")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/bin/hwmonitor-launcher")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/bin" TYPE PROGRAM RENAME "hwmonitor-launcher" FILES "/home/zhao/Desktop/AI/dde-dock-hwmonitor/data/hwmonitor-launcher.sh")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor" TYPE DIRECTORY FILES "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/packages/org.deepin.ds.dock.hwmonitor/")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/lib/x86_64-linux-gnu/dde-shell/org.deepin.ds.dock.hwmonitor.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/x86_64-linux-gnu/dde-shell/org.deepin.ds.dock.hwmonitor.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/lib/x86_64-linux-gnu/dde-shell/org.deepin.ds.dock.hwmonitor.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/lib/x86_64-linux-gnu/dde-shell/org.deepin.ds.dock.hwmonitor.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/lib/x86_64-linux-gnu/dde-shell" TYPE SHARED_LIBRARY FILES "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/plugins/org.deepin.ds.dock.hwmonitor.so")
  if(EXISTS "$ENV{DESTDIR}/usr/lib/x86_64-linux-gnu/dde-shell/org.deepin.ds.dock.hwmonitor.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/lib/x86_64-linux-gnu/dde-shell/org.deepin.ds.dock.hwmonitor.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/lib/x86_64-linux-gnu/dde-shell/org.deepin.ds.dock.hwmonitor.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/CMakeFiles/ds-dock-hwmonitor.dir/install-cxx-module-bmi-Release.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_ar.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_az.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_bo.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_ca.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_de.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_es.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_fi.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_fr.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_hu.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_it.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_ja.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_ko.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_lo.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_nb_NO.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_pl.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_pt_BR.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_ru.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_sq.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_uk.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_zh_CN.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_zh_HK.qm;/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations/org.deepin.ds.dock.hwmonitor_zh_TW.qm")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/share/dde-shell/org.deepin.ds.dock.hwmonitor/translations" TYPE FILE FILES
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_ar.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_az.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_bo.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_ca.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_de.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_es.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_fi.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_fr.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_hu.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_it.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_ja.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_ko.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_lo.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_nb_NO.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_pl.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_pt_BR.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_ru.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_sq.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_uk.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_zh_CN.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_zh_HK.qm"
    "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/org.deepin.ds.dock.hwmonitor_zh_TW.qm"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/zhao/Desktop/AI/dde-dock-hwmonitor/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
