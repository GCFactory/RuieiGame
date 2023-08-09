# CMakeList.txt : CMake project for Engine, include source and define
# project specific logic here.
#

# Add source to this project's executable.
set (SOURCE_FILES "main.cpp")

if(WIN32)
    set(LIB_DIR ${PROJECT_SOURCE_DIR}/Thirdparty/Win)
    set(SHRD_EXT dll)
else()
    set(LIB_DIR ${PROJECT_SOURCE_DIR}/Thirdparty/Linux)
    set(SHRD_EXT so)
endif(WIN32)

add_executable(HellowWorld ${SOURCE_FILES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET HellowWorld PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(Engine
        PRIVATE
        "${PROJECT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)