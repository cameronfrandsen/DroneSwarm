set(lib_name monitorlogger)
set(${lib_name}_srcs
  MonitorLogger.cpp
  MonitorLogger.hpp
  )
source_group("" FILES ${${lib_name}_srcs})
add_library(${lib_name} ${${lib_name}_srcs})
target_link_libraries(${lib_name} PUBLIC logger TCP)
target_include_directories(${lib_name} PUBLIC ${CMAKE_SOURCE_DIR}/Shared/MonitorLoggerLIB)
include(CheckLibraryExists)
check_library_exists(dl dlerror "" CRT_HAS_DL)
if(CRT_HAS_DL)
  target_link_libraries(${lib_name} PRIVATE dl) # for boost dll
endif()
xpTargetExtern(${lib_name} PUBLIC boost)
set_property(TARGET ${lib_name} PROPERTY FOLDER ${folder})
add_subdirectory(Test)
xpSourceListAppend(${${lib_name}_srcs})
