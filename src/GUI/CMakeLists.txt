cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME zappy_gui)

project(
    ${PROJECT_NAME}
    VERSION 1.0
    DESCRIPTION "Tek2 | YEP | zappy_gui"
    LANGUAGES CXX
)

add_executable(${PROJECT_NAME})

##################### CMAKE OPTIONS #######################

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(UNIX)
    target_compile_options(${PROJECT_NAME} PRIVATE -W -Wall -Wextra)
elseif(WIN32)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
endif()

##################### libs ##########################

include(Dependencies/build-SFML.cmake)

##################### SRC #################################

add_subdirectory(src)

##################### CUSTOM CMD ##########################

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_CURRENT_SOURCE_DIR}
)
