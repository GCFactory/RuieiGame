# CMakeList.txt : CMake project for Engine, include source and define
# project specific logic here.
#

# Add source to this project's executable.
set (SOURCE_FILES "Engine.cpp" "Engine.h")


if(WIN32)
    set(LIB_DIR ${PROJECT_SOURCE_DIR}/Thirdparty/Win)
    set(SHRD_EXT dll)
else()
    set(LIB_DIR ${PROJECT_SOURCE_DIR}/Thirdparty/Linux)
    set(SHRD_EXT so)
endif(WIN32)

if(WIN32)   
    set(SFML_STATIC_LIBRARIES TRUE)
endif(WIN32)

set(SFML_DIR ${LIB_DIR}/SFML-2.6.0/lib/cmake/SFML/)
find_package(SFML 2.6 COMPONENTS graphics window system audio network REQUIRED)

add_executable (Engine ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Engine PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(Engine sfml-main sfml-system sfml-graphics sfml-audio)

target_include_directories(Engine
    PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
