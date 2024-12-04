# Minimum required CMake version
cmake_minimum_required(VERSION 3.28)

# Project name and language
project(Under LANGUAGES CXX)

# Set output directory for the binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Explicitly set C++17 as the standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Option to build shared libraries (if needed in the future)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Fetch SFML from the repository
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Fetch Google Test
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Collect all source files in the src directory
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Create the main executable
add_executable(Under ${SOURCES})

# Link SFML libraries
target_link_libraries(Under PRIVATE sfml-graphics sfml-system)

# Windows-specific settings to copy OpenAL DLL
if(WIN32)
    message(STATUS "Configuring for Windows")
    add_custom_command(
        TARGET Under
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
        ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll
        $<TARGET_FILE_DIR:Under>
        VERBATIM)
elseif(APPLE)
    message(STATUS "Configuring for macOS")
    # macOS-specific settings
    # Link additional frameworks if necessary (future features may need these)
    target_link_libraries(Under PRIVATE "-framework Cocoa" "-framework IOKit" "-framework CoreFoundation")
endif()

# Copy assets directory to the build directory (future proof for asset changes)
add_custom_command(
    TARGET Under POST_BUILD
    COMMENT "Copy assets to build directory"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:Under>/assets
)

# Enable testing framework and integrate Google Test
enable_testing()

# Add UnitTests executable
add_executable(UnitTests tests/test.cpp)

# Link UnitTests with Google Test and SFML
target_link_libraries(UnitTests PRIVATE gtest gtest_main sfml-graphics sfml-system)

# Define a test using Google Test
add_test(NAME UnitTests COMMAND UnitTests)