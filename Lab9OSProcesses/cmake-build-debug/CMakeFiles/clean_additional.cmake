# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Lab9OSProcesses_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Lab9OSProcesses_autogen.dir\\ParseCache.txt"
  "Lab9OSProcesses_autogen"
  )
endif()
