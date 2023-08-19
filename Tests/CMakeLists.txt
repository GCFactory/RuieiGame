file(GLOB HEADER_FILES
        "include/*.h"
        "*.h"
)
file(GLOB ENGINE_HEADER_FILES
        "../Engine/include/*.h"
)
file(GLOB ENGINE_SOURCE_FILES
        "../Engine/src/*.cpp"
)

set (SOURCE_FILES "main.cpp"
        TestTextureManager.cpp
)

if(WIN32)
    set(gtest_force_shared_crt on)

    include(FetchContent)
    FetchContent_Declare(googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG main)
    FetchContent_MakeAvailable(googletest)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif(WIN32)


execute_process(COMMAND cmake -S. -B${googletest_BINARY_DIR} WORKING_DIRECTORY ${googletest_SOURCE_DIR})
execute_process(COMMAND cmake --build . WORKING_DIRECTORY ${googletest_BINARY_DIR})

set(GTEST_LIBRARY ${googletest_BINARY_DIR}/lib/libgtest.a)
set(GTEST_INCLUDE_DIR ${googletest_SOURCE_DIR}/googletest/include)
set(GTEST_MAIN_LIBRARY ${googletest_BINARY_DIR}/lib/libgtest_main.a)

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


find_package(GTest REQUIRED)
enable_testing()

add_executable (Test ${SOURCE_FILES} ${HEADER_FILES} ${ENGINE_HEADER_FILES} ${ENGINE_SOURCE_FILES})


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Test PROPERTY CXX_STANDARD 20)
endif()


target_include_directories(Test
        PRIVATE
        "${PROJECT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/Engine/include"
)
target_link_libraries(Test
        GTest::gtest_main
        sfml-window sfml-system sfml-graphics sfml-audio
)

# Post-build Resources dir
add_custom_target(TestCopyAssets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/Resources ${CMAKE_CURRENT_BINARY_DIR}/Resources
)
add_dependencies(Test TestCopyAssets)

include(GoogleTest)
gtest_discover_tests(Test)