cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico-wifi-example)

pico_sdk_init()

# Add WiFi-specific configurations
set(PICO_BOARD pico_w)  # ← Critical for WiFi

add_executable(${PROJECT_NAME} 
    main.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/..
)

target_link_libraries(${PROJECT_NAME} 
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
)

pico_add_extra_outputs(${PROJECT_NAME})