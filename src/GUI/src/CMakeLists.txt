cmake_minimum_required(VERSION 3.13)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(
    ${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/App.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/CommandHandler.cpp
)

add_subdirectory(Display)
add_subdirectory(Maths)
add_subdirectory(Entities)
add_subdirectory(Components)
add_subdirectory(network)
add_subdirectory(Events)
