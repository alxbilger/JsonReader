cmake_minimum_required(VERSION 3.12)
project(JsonReader VERSION 1.0 LANGUAGES CXX)

find_package(SofaFramework REQUIRED)
sofa_find_package(Sofa.Simulation.Graph REQUIRED)

# List all files
set(JSONREADER_SRC_DIR src/${PROJECT_NAME})
set(HEADER_FILES
    ${JSONREADER_SRC_DIR}/config.h.in
    ${JSONREADER_SRC_DIR}/SceneLoaderJson.h
)
set(SOURCE_FILES
    ${JSONREADER_SRC_DIR}/init.cpp

    ${JSONREADER_SRC_DIR}/SceneLoaderJson.cpp
)
set(README_FILES
    README.md
)

# Create the plugin library.
add_library(${PROJECT_NAME} SHARED ${HEADER_FILES} ${SOURCE_FILES} ${README_FILES})

target_link_libraries(${PROJECT_NAME} Sofa.Simulation.Graph)

# Create package Config, Version & Target files.
# Deploy the headers, resources, scenes & examples.
# Set the plugin 'relocatable' if built within SOFA.
# --> see SofaMacros.cmake
sofa_create_package_with_targets(
    PACKAGE_NAME ${PROJECT_NAME}
    PACKAGE_VERSION ${PROJECT_VERSION}
    TARGETS ${PROJECT_NAME} AUTO_SET_TARGET_PROPERTIES
    INCLUDE_SOURCE_DIR "src"
    INCLUDE_INSTALL_DIR ${PROJECT_NAME}
    RELOCATABLE "plugins"
)

# Tests
# If SOFA_BUILD_TESTS exists and is OFF, then these tests will be auto-disabled
cmake_dependent_option(JSONREADER_BUILD_TESTS "Compile the automatic tests" ON "SOFA_BUILD_TESTS OR NOT DEFINED SOFA_BUILD_TESTS" OFF)
if(JSONREADER_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
