cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(706Face C CXX ASM)
set(CMAKE_C_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

# Initialize the SDK
pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        )

add_executable(706Face
	706Face.c
	)

# pull in common dependencies
target_link_libraries(706Face pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(706Face)

pico_enable_stdio_usb(706Face 1)
