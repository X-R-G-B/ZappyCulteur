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
    ${CMAKE_CURRENT_SOURCE_DIR}/Egg.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Incantation.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Ressources.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/EndScreen.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/HUD.cpp
)
