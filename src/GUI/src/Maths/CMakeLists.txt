cmake_minimum_required(VERSION 3.25)

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(
    ${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Vector2F.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Vector3F.cpp
)
