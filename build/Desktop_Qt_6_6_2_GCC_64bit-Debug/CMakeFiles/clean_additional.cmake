# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/consoleOgienWoda_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/consoleOgienWoda_autogen.dir/ParseCache.txt"
  "consoleOgienWoda_autogen"
  )
endif()
