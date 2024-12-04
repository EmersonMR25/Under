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

# Enable testing framework (expand this as you add tests)
enable_testing()
add_executable(UnitTests tests/test.cpp)
target_link_libraries(UnitTests PRIVATE sfml-graphics sfml-system)
add_test(NAME UnitTests COMMAND UnitTests)

# Notes for future:
# 1. If you add more folders in `src/`, update the GLOB_RECURSE or manually specify new sources.
# 2. For complex assets, consider creating an `assets/CMakeLists.txt` to handle copying per subfolder.
# 3. Use `FetchContent` to manage additional libraries (if needed later).