cmake_minimum_required(VERSION 3.25)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(
    ${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/AEntity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EntitiesManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Trantorian.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Floor.cpp
)
