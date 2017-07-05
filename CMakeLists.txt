cmake_minimum_required(VERSION 2.8.3)
project(aurora_vision)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  roscpp
  image_transport
  sensor_msgs
  std_msgs
  message_generation
)

add_message_files(
   FILES
   heart.msg
)

generate_messages(
   DEPENDENCIES
   std_msgs
 )

#include_directories(${catkin_INCLUDE_DIRS})

catkin_package(CATKIN_DEPENDS sensor_msgs message_runtime)

# ---------------------------- GUI --------------------------------------------------
# set header ans source files
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
set(GUI_SOURCE_FILES         
	src/main.cpp    
	src/filter.cpp  
	src/mainwindow.cpp
        src/polygon.cpp 
	src/polygon/chess_shape.cpp
	src/polygon/circle.cpp
	src/polygon/heart.cpp
	src/polygon/h_shape.cpp
	src/polygon/pentagon.cpp
	src/polygon/square.cpp
	src/polygon/star.cpp
	src/polygon/triangle.cpp
)

set(GUI_HEADER_FILES             
	src/filter.h  
	src/mainwindow.h
        src/polygon.h 
	src/polygon/chess_shape.h
	src/polygon/circle.h
	src/polygon/heart.h
	src/polygon/h_shape.h
	src/polygon/pentagon.h
	src/polygon/square.h
	src/polygon/star.h
	src/polygon/triangle.h
)

# *.ui
set(GUI_UI_FILES        
	src/mainwindow.ui 
)

# *.qrc
set(GUI_RESOURCE_FILES 
	src/source.qrc   
)

# do QT stuff
ADD_DEFINITIONS( -Wall )
find_package(Qt4 COMPONENTS QtCore QtGui QtNetwork REQUIRED )
include(${QT_USE_FILE})
QT4_ADD_RESOURCES(GUI_RESOURCE_FILES_CPP ${GUI_RESOURCE_FILES})
QT4_WRAP_UI(GUI_UI_FILES_HPP ${GUI_UI_FILES})
QT4_WRAP_CPP(GUI_HEADER_FILES_HPP ${GUI_HEADER_FILES})
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

# build!
add_executable(aurora_vision ${GUI_SOURCE_FILES} ${GUI_RESOURCE_FILES_CPP} ${GUI_UI_FILES_HPP} ${GUI_HEADER_FILES_HPP} ${GUI_RESOURCE_FILES})
target_link_libraries(aurora_vision ${catkin_LIBRARIES} ${QT_LIBRARIES} ${ROS_LIBRARIES} ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(aurora_vision ${PROJECT_NAME}_gencpp)
