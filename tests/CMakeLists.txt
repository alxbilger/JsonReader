cmake_minimum_required(VERSION 3.1)

project(JsonReader_test VERSION 1.0)

find_package(Sofa.Testing REQUIRED)

set(SOURCE_FILES
    SceneLoaderJson_test.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} Sofa.Testing JsonReader)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
