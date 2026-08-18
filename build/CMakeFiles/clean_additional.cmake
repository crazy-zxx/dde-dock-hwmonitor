# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles/ds-dock-hwmonitor_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/ds-dock-hwmonitor_autogen.dir/ParseCache.txt"
  "ds-dock-hwmonitor_autogen"
  )
endif()
