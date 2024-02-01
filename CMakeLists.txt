cmake_minimum_required(VERSION 3.1)
project(CMakeDemo)

# Set this variable to ON to suppress CMake developer warnings
set(CMAKE_SUPPRESS_DEVELOPER_WARNINGS ON CACHE BOOL "Suppress warnings for project developers")

set(SDL_VERSION "2.0.5")

if (WIN32)
    # Download and extract SDL2
    set(SDL2_URL "https://www.libsdl.org/release/SDL2-devel-${SDL_VERSION}-VC.zip")
    set(SDL2_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/vendor/SDL2-${SDL_VERSION}")
    file(MAKE_DIRECTORY ${SDL2_FOLDER})

    # Download SDL2 quietly
    message(STATUS "Downloading SDL2 from ${SDL2_URL}")
    file(DOWNLOAD ${SDL2_URL} "${CMAKE_BINARY_DIR}/SDL2.zip"
            STATUS DOWNLOAD_STATUS
            QUIET)

    # Check download status
    list(GET DOWNLOAD_STATUS 0 DOWNLOAD_ERROR)
    if (DOWNLOAD_ERROR)
        message(FATAL_ERROR "Could not download SDL2: ${DOWNLOAD_STATUS}")
    endif ()

    # Extract SDL2
    message(STATUS "Extracting SDL2 to ${SDL2_FOLDER}")
    execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar xf "${CMAKE_BINARY_DIR}/SDL2.zip"
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/vendor"
            RESULT_VARIABLE EXTRACTION_RESULT
    )

    # Check extraction result
    if (EXTRACTION_RESULT)
        message(FATAL_ERROR "Could not extract SDL2: ${EXTRACTION_RESULT}")
    endif ()

    # Remove downloaded zip file
    file(REMOVE "${CMAKE_BINARY_DIR}/SDL2.zip")
endif ()

# Find SDL2
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")
find_package(SDL2 "2.0.5" REQUIRED COMPONENTS main)

# Define executable target
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2main_INCLUDE_DIRS} ${CMAKE_BINARY_DIR})
add_executable(CMakeDemo main.c)
target_link_libraries(CMakeDemo ${SDL2_LIBS})

# Copy SDL2 DLLs to output folder on Windows
if (WIN32)
    foreach (DLL ${SDL2_DLLS})
        add_custom_command(TARGET CMakeDemo POST_BUILD COMMAND
                ${CMAKE_COMMAND} -E copy_if_different ${DLL} $<TARGET_FILE_DIR:CMakeDemo>)
        message(STATUS "Copied ${DLL} to output folder")
    endforeach ()
endif ()
