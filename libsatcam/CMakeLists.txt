cmake_minimum_required(VERSION 3.22)

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(TOOLCHAIN_PREFIX                "/usr/bin/")

set(CMAKE_C_COMPILER                ${TOOLCHAIN_PREFIX}gcc)
set(CMAKE_ASM_COMPILER              ${CMAKE_C_COMPILER})
set(CMAKE_CXX_COMPILER              ${TOOLCHAIN_PREFIX}g++)
set(CMAKE_LINKER                    ${TOOLCHAIN_PREFIX}g++)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME "libsatcam")
set(LIB_NAME "satcam")

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("CMAKE_BUILD_TYPE:       " ${CMAKE_BUILD_TYPE})
message("LIB_NAME:               " ${LIB_NAME})


set(EXECUTABLE_OUTPUT_PATH bin)
message("EXECUTABLE_OUTPUT_PATH: " ${EXECUTABLE_OUTPUT_PATH})


set(LIBRARY_OUTPUT_PATH ../lib)
message("EXECUTABLE_OUTPUT_PATH: " ${LIBRARY_OUTPUT_PATH})

file(GLOB files_under_src
     "src/*.c"
)
message("files_under_src:        " ${files_under_src})

add_library(${LIB_NAME} SHARED
    ${files_under_src}
)
