set(exe_name MonitorLoggerTest)
set(${exe_name}_srcs
  MonitorLoggerTest.cpp
  )
source_group("" FILES ${${exe_name}_srcs})
add_executable(${exe_name} ${${exe_name}_srcs})
target_link_libraries(${exe_name} PUBLIC monitorlogger TCP)
xpTargetExtern(${exe_name} PRIVATE boost protobuf)
set_property(TARGET ${exe_name} PROPERTY FOLDER ${folder}/UnitTest)
add_test(NAME ${exe_name} COMMAND ${exe_name})
xpSourceListAppend("${${exe_name}_srcs}")
