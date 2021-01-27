cmake_minimum_required(VERSION 3.0.2)
project(roomabot)

set(RPLIDAR_SDK_PATH "./sdk/")

FILE(GLOB RPLIDAR_SDK_SRC 
  "${RPLIDAR_SDK_PATH}/src/arch/linux/*.cpp"
  "${RPLIDAR_SDK_PATH}/src/hal/*.cpp"
  "${RPLIDAR_SDK_PATH}/src/*.cpp"
)

find_package(catkin REQUIRED COMPONENTS
  rosconsole
  roscpp
  sensor_msgs
  std_msgs
  std_srvs
  tf2
  tf2_ros
  message_generation
)

add_message_files(
	FILES
    serviceCommand.msg
)

generate_messages(
   DEPENDENCIES
   std_msgs
)

include_directories(
  ${RPLIDAR_SDK_PATH}/include
  ${RPLIDAR_SDK_PATH}/src
  ${catkin_INCLUDE_DIRS}
)

catkin_package(
	CATKIN_DEPENDS message_runtime
)

add_executable(dataProcessor src/dataProcessor.cpp ${RPLIDAR_SDK_SRC})
target_link_libraries(dataProcessor ${catkin_LIBRARIES})

add_executable(user_input src/user_input.cpp)
target_link_libraries(user_input ${catkin_LIBRARIES})

add_executable(serviceHandler src/serviceHandler.cpp)
add_dependencies(serviceHandler roomabot_generate_messages_cpp)
target_link_libraries(serviceHandler ${catkin_LIBRARIES})

install(TARGETS dataProcessor
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY launch rviz sdk
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
  USE_SOURCE_PERMISSIONS
)
