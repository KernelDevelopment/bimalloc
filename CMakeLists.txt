cmake_minimum_required(VERSION 3.0)
project(bimalloc C)

set(CMAKE_C_STANDARD 99)

include(CheckIncludeFile)
include(CheckSymbolExists)
include(GNUInstallDirs)

macro(setup_include_and_definitions TARGET_NAME)
    target_include_directories(${TARGET_NAME}
            PUBLIC  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
            PUBLIC  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/internal>)
endmacro()

macro(add_BIMALLOC_headers_and_sources HDRS_LIST_NAME SRCS_LIST_NAME)
    file(GLOB IMPL_SOURCES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/bimalloc_*.c")
    list(APPEND ${SRCS_LIST_NAME} ${IMPL_SOURCES})
    list(APPEND ${HDRS_LIST_NAME} ${PROJECT_SOURCE_DIR}/include/internal/bimalloc_message.h)
    list(APPEND ${HDRS_LIST_NAME} ${PROJECT_SOURCE_DIR}/include/internal/bimalloc_macros.h)
    list(APPEND ${HDRS_LIST_NAME} ${PROJECT_SOURCE_DIR}/include/internal/bimalloc_assert.h)
    list(APPEND ${HDRS_LIST_NAME} ${PROJECT_SOURCE_DIR}/include/bimalloc.h)
endmacro()

set (BIMALLOC_HDRS)
set (BIMALLOC_SRCS)
add_BIMALLOC_headers_and_sources(BIMALLOC_HDRS BIMALLOC_SRCS)
add_library(BIMALLOC_lib ${BIMALLOC_HDRS} ${BIMALLOC_SRCS})
set_target_properties(BIMALLOC_lib PROPERTIES PUBLIC_HEADER "${BIMALLOC_HDRS}")
setup_include_and_definitions(BIMALLOC_lib)
target_link_libraries(BIMALLOC_lib PUBLIC ${CMAKE_DL_LIBS})
target_include_directories(BIMALLOC_lib
        PUBLIC $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/BIMALLOC_lib>
        )
add_library(bimalloc::BIMALLOC_lib ALIAS BIMALLOC_lib)

#
# program : bimalloc_example
#

add_executable(bimalloc_example ${PROJECT_SOURCE_DIR}/src/examples/main.c)
target_link_libraries(bimalloc_example PRIVATE BIMALLOC_lib)
add_executable(bimalloc::bimalloc_example ALIAS bimalloc_example)

#
# tests
#
include(CTest)
if(BUILD_TESTING)
    enable_language(CXX)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    if(NOT TARGET gtest OR NOT TARGET gmock_main)
        # Download and unpack googletest at configure time.
        configure_file(
                cmake/googletest.CMakeLists.txt.in
                googletest-download/CMakeLists.txt
        )

        execute_process(
                COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)

        if(result)
            message(FATAL_ERROR "CMake step for googletest failed: ${result}")
        endif()

        execute_process(
                COMMAND ${CMAKE_COMMAND} --build .
                RESULT_VARIABLE result
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)

        if(result)
            message(FATAL_ERROR "Build step for googletest failed: ${result}")
        endif()

        # Prevent overriding the parent project's compiler/linker settings on
        # Windows.
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

        # Add googletest directly to build. This defines the gtest and
        # gtest_main targets.
        add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                ${CMAKE_BINARY_DIR}/googletest-build
                EXCLUDE_FROM_ALL)
    endif()
    add_subdirectory(test)
endif()