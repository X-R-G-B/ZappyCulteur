if (WIN32)
    include(FetchContent)
    set(SFML_BUILD_AUDIO OFF)
    set(SFML_BUILD_NETWORK OFF)
    set(SFML_BUILD_DOC OFF)
    set(SFML_BUILD_EXAMPLES OFF)
    set(SFML_BUILD_TEST_SUITE OFF)
    set(BUILD_SHARED_LIBS FALSE)
    set(SFML_USE_STATIC_STD_LIBS TRUE)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
    FetchContent_MakeAvailable(SFML)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
    )
else()
    find_library(SFML sfml-graphics sfml-window sfml-system)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        sfml-graphics sfml-window sfml-system
    )
endif()
