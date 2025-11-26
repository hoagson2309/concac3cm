# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/mnt/c/Users/hoang/Desktop/SAXION/QUARTER 3/Computer Networking/pico/project-template/build/_deps/picotool-src"
  "/mnt/c/Users/hoang/Desktop/SAXION/QUARTER 3/Computer Networking/pico/project-template/build/_deps/picotool-build"
  "/mnt/c/Users/hoang/Desktop/SAXION/QUARTER 3/Computer Networking/pico/project-template/build/_deps"
  "/mnt/c/Users/hoang/Desktop/SAXION/QUARTER 3/Computer Networking/pico/project-template/build/pico-sdk/src/rp2040/boot_stage2/picotool/tmp"
  "/mnt/c/Users/hoang/Desktop/SAXION/QUARTER 3/Computer Networking/pico/project-template/build/pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp"
  "/mnt/c/Users/hoang/Desktop/SAXION/QUARTER 3/Computer Networking/pico/project-template/build/pico-sdk/src/rp2040/boot_stage2/picotool/src"
  "/mnt/c/Users/hoang/Desktop/SAXION/QUARTER 3/Computer Networking/pico/project-template/build/pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/mnt/c/Users/hoang/Desktop/SAXION/QUARTER 3/Computer Networking/pico/project-template/build/pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/mnt/c/Users/hoang/Desktop/SAXION/QUARTER 3/Computer Networking/pico/project-template/build/pico-sdk/src/rp2040/boot_stage2/picotool/src/picotoolBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
