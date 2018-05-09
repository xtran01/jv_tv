#CMakeLists.txt to build project using cmake
#run $cmake CMakeLists.txt

cmake_minimum_required(VERSION 2.6)

project(jv_tv)

FIND_PACKAGE(OpenGL REQUIRED)
set(QT_USE_OPENGL TRUE)
FIND_PACKAGE(X11)


include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(
  GLOB_RECURSE
  source_files
  src/*.cpp
  src/*.hpp
  src/*.h
)

SET(CMAKE_BUILD_TYPE Debug)
ADD_DEFINITIONS( -Wall -Wextra -O2 -g -std=c++11 -Wno-unused-parameter -I/usr/include/irrlicht)


add_executable(
  jv_tv
  ${source_files}
)


TARGET_LINK_LIBRARIES(jv_tv -lm -ldl -lGLEW -lGL -lIrrlicht  ${OPENGL_LIBRARIES} ${QT_LIBRARIES} ${QT_GL_LIBRARIES} ${QT_QTOPENGL_LIBRARY} ${X11_LIBRARIES} /usr/lib/x86_64-linux-gnu/libXxf86vm.so.1)


