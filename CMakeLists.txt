cmake_minimum_required(VERSION 4.0 FATAL_ERROR)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME Engine)

set(SOURCE_FOLDER src)
set(INCLUDE_FOLDER include)
set(DEPENDS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)
add_definitions(-DPROJECT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/")

project(${PROJECT_NAME} LANGUAGES CXX)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

file(GLOB_RECURSE HEADER_FILES
${INCLUDE_FOLDER}/*.hpp
${INCLUDE_FOLDER}/*.h)

file(GLOB_RECURSE SOURCE_FILES
${SOURCE_FOLDER}/*.cpp
${SOURCE_FOLDER}/*.c)

foreach(SOURCE_FILE ${SOURCE_FILES})
    file(RELATIVE_PATH RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FOLDER} ${SOURCE_FILE})
    string(REPLACE "\\" "/" GROUP_NAME ${RELATIVE_PATH})
	get_filename_component(GROUP_NAME ${GROUP_NAME} DIRECTORY)
	if (GROUP_NAME STREQUAL "")
		source_group("Source Files" FILES ${SOURCE_FILE})
		break()
    endif()
    source_group("Source Files\\${GROUP_NAME}" FILES ${SOURCE_FILE})
endforeach()

foreach(HEADER_FILE ${HEADER_FILES})
    file(RELATIVE_PATH RELATIVE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_FOLDER} ${HEADER_FILE})
    string(REPLACE "\\" "/" GROUP_NAME ${RELATIVE_PATH})
	get_filename_component(GROUP_NAME ${GROUP_NAME} DIRECTORY)
	if (GROUP_NAME STREQUAL "")
        source_group("Header Files" FILES ${HEADER_FILE})
		break()
    endif()
    source_group("Header Files\\${GROUP_NAME}" FILES ${HEADER_FILE})
endforeach()

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_FOLDER})

#Adding GLFW
add_subdirectory(${DEPENDS_DIR}/GLFW)
target_link_libraries(${PROJECT_NAME} glfw)

#Adding ASSIMP
add_subdirectory(${DEPENDS_DIR}/ASSIMP)
target_link_libraries(${PROJECT_NAME} assimp)

#Adding BULLET
set(BUILD_BULLET2_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_CPU_DEMOS OFF CACHE BOOL "" FORCE)
set(BUILD_UNIT_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_EXTRAS OFF CACHE BOOL "" FORCE)
set(BUILD_OPENGL3_DEMOS OFF CACHE BOOL "" FORCE)

add_subdirectory(${DEPENDS_DIR}/BULLET)

target_link_libraries(${PROJECT_NAME}
    BulletDynamics
    BulletCollision
    LinearMath
    BulletSoftBody
)

target_include_directories(${PROJECT_NAME} PRIVATE ${DEPENDS_DIR}/BULLET/src)

#Adding GLM
FetchContent_Declare(
	glm
	GIT_REPOSITORY	https://github.com/g-truc/glm.git
)

FetchContent_MakeAvailable(glm)

#Adding IMGUI
file(GLOB_RECURSE IMGUI_SOURCES ${DEPENDS_DIR}/IMGUI/*.cpp ${DEPENDS_DIR}/IMGUI/*.h)
add_library(ImGui STATIC ${IMGUI_SOURCES})
target_include_directories(ImGui PUBLIC ${DEPENDS_DIR}/IMGUI)
target_include_directories(ImGui PUBLIC ${DEPENDS_DIR}/GLFW/include)
target_link_libraries(${PROJECT_NAME} ImGui)

target_link_libraries(${PROJECT_NAME} glm::glm)
target_include_directories(${PROJECT_NAME} PRIVATE ${DEPENDS_DIR}/GLAD/include)

add_compile_options(/Zc:__cplusplus)