cmake_minimum_required(VERSION 3.25)

set(PROJECT_NAME zappy_gui)

project(
    ${PROJECT_NAME}
    VERSION 1.0
    DESCRIPTION "Tek2 | YEP | zappy_gui"
    LANGUAGES CXX
)

add_executable(${PROJECT_NAME})

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES UNITY_BUILD ON
)

##################### CMAKE OPTIONS #######################

if(UNIX)
    target_compile_options(
        ${PROJECT_NAME}
        PRIVATE
        -W -Wall -Wextra
    )
elseif(WIN32)
    target_compile_options(
        ${PROJECT_NAME}
        PRIVATE /W4
    )
endif()

##################### libs ##########################

include(Dependencies/build-SFML.cmake)

if(WIN32)
    target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE ws2_32
    )
endif()

target_compile_features(
    ${PROJECT_NAME}
    PRIVATE
    cxx_std_20
)

##################### SRC #################################

add_subdirectory(src)

##################### CUSTOM CMD ##########################

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_CURRENT_SOURCE_DIR}
)
