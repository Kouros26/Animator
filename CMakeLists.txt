include("FetchContent")
cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FOLDER src)
set(INCLUDE_FOLDER include)
set(DEPENDS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)

set(PROJECT_NAME Animator)

project(${PROJECT_NAME} LANGUAGES CXX)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})


file(GLOB_RECURSE HEADER_FILES
${INCLUDE_FOLDER}/*.hpp)

file(GLOB_RECURSE SOURCE_FILES
${SOURCE_FOLDER}/*.cpp)

FetchContent_Declare(
	GLFW
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG 3.3.8)

FetchContent_Declare(
    LibMath
    GIT_REPOSITORY https://github.com/Angel-2180/LibMaths.git
	GIT_TAG master)

set(CMAKE_FOLDER "${CMAKE_FOLDER_OLD}/vendor/glfw")
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
FetchContent_MakeAvailable(GLFW)
FetchContent_MakeAvailable(LibMath)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_FOLDER})
target_include_directories(${PROJECT_NAME} PRIVATE ${glfw_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${LIBMATHS_INCLUDE_DIR})

add_subdirectory(Engine)

target_include_directories(${PROJECT_NAME} PRIVATE "Engine/include")

add_compile_options(/Zc:__cplusplus)