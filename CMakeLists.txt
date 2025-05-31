#
#   project
#

cmake_minimum_required(VERSION 3.20)
project(nyx C)

set(common_bin_dir ${CMAKE_SOURCE_DIR}/bin/$<0:>)

#
#   submodules
#

add_subdirectory(external/lux)

#
#   executable
#

file(GLOB_RECURSE source_files CONFIGURE_DEPENDS src/*.c)
add_executable(nyx ${source_files})

set_target_properties(nyx PROPERTIES
    C_STANDARD 17

    RUNTIME_OUTPUT_DIRECTORY ${common_bin_dir}
    ARCHIVE_OUTPUT_DIRECTORY ${common_bin_dir}
    LIBRARY_OUTPUT_DIRECTORY ${common_bin_dir}
)

target_link_libraries(nyx PRIVATE
    lux
)

target_include_directories(nyx PRIVATE
    ${CMAKE_SOURCE_DIR}/external/rias/include
    ${CMAKE_SOURCE_DIR}/external/lux/include
)
