set(lib_name DroneManagerLib)
set(${lib_name}_srcs
  DroneController.cpp
  DroneController.hpp
  DroneControllerCheckMsgToSend.cpp
  DroneControllerCheckMsgToSend.hpp
  DroneControllerMessagesToString.cpp
  DroneControllerMessagesToString.hpp
  DroneControllerState.cpp
  DroneControllerState.hpp
  DroneControllerStateChanges.cpp
  DroneControllerStateChanges.hpp
  DroneManager.cpp
  DroneManager.hpp
  )
source_group("" FILES ${${lib_name}_srcs})
add_library(${lib_name} ${${lib_name}_srcs})
target_link_libraries(${lib_name} PUBLIC udp DroneMessagesLib logger registry monitorlogger)
target_include_directories(${lib_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../)
xpTargetExtern(${lib_name} PUBLIC boost protobuf)
set_property(TARGET ${lib_name} PROPERTY FOLDER ${folder})
xpSourceListAppend(${${lib_name}_srcs})
