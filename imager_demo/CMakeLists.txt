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
set(CMAKE_PROJECT_NAME "imager_demo")
set(LIBSATCAM_OUT_PATH "../../libsatcam/build")
set(LIBSATCAM_SOURCE_PATH "../libsatcam")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for C language
enable_language(C)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("CMAKE_BUILD_TYPE:       " ${CMAKE_BUILD_TYPE})


set(EXECUTABLE_OUTPUT_PATH bin)
message("EXECUTABLE_OUTPUT_PATH: " ${EXECUTABLE_OUTPUT_PATH})

file(GLOB files_under_src
     "src/*.c"
)
message("files_under_src:        " ${files_under_src})

add_executable(${CMAKE_PROJECT_NAME}
    ${files_under_src}
)

add_subdirectory(${LIBSATCAM_SOURCE_PATH} ${LIBSATCAM_OUT_PATH})
target_link_libraries(${CMAKE_PROJECT_NAME} satcam)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC SYSTEM
    inc
    ${LIBSATCAM_SOURCE_PATH}/inc
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC SYSTEM
	$<$<CONFIG:Debug>:DEBUG>
)
