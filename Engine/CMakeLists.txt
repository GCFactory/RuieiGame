# CMakeList.txt : CMake project for Engine, include source and define
# project specific logic here.
#

# Auto add headers to executable
file(GLOB HEADER_FILES
        "include/*.h"
        "*.h"
)
# Add source to this project's executable.
set (SOURCE_FILES "main.cpp"
        src/EngineBase.cpp
        src/GameObject.cpp
        src/TextureManager.cpp
        src/Engine.cpp
)

# Autoload library dir on different OS
if(WIN32)
    set(LIB_DIR ${PROJECT_SOURCE_DIR}/Thirdparty/Win)
    set(SHRD_EXT dll)
else()
    set(LIB_DIR ${PROJECT_SOURCE_DIR}/Thirdparty/Linux)
    set(SHRD_EXT so)
endif(WIN32)

# SFMl Library load
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "${LIB_DIR}/SFML-2.6.0/lib/cmake/SFML/")
if(WIN32)
find_package(SFML 2.6 COMPONENTS graphics window system audio network REQUIRED)
else()
include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)
endif(WIN32)


add_executable (Engine ${SOURCE_FILES} ${HEADER_FILES})
if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Engine PROPERTY CXX_STANDARD 20)
endif()

# Link library
target_link_libraries(Engine sfml-window sfml-system sfml-graphics sfml-audio)
# Link headers
target_include_directories(Engine
    PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
# Post-build Resources dir
add_custom_target(EngineCopyAssets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Resources ${CMAKE_CURRENT_BINARY_DIR}/Resources
)
add_dependencies(Engine EngineCopyAssets)