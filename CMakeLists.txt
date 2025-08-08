#
#   project
#

cmake_minimum_required(VERSION 3.20)
project(nyx C)

set(common_bin_dir ${CMAKE_SOURCE_DIR}/bin/$<0:>)

#
#   dependencies
#

include(FetchContent)

FetchContent_Declare(
    lux
    GIT_REPOSITORY https://github.com/nidheimr/lux.git
    GIT_TAG main
    GIT_SHALLOW TRUE
)

set(FETCHCONTENT_UPDATES_DISCONNECTED FALSE)

FetchContent_MakeAvailable(lux)

#
#   executable
#

file(GLOB_RECURSE src_files CONFIGURE_DEPENDS src/*.c)
add_executable(nyx ${src_files})

target_link_libraries(nyx PRIVATE
    lux
)

set_target_properties(nyx PROPERTIES
    C_STANDARD 17
    RUNTIME_OUTPUT_DIRECTORY ${common_bin_dir}
    ARCHIVE_OUTPUT_DIRECTORY ${common_bin_dir}
    LIBRARY_OUTPUT_DIRECTORY ${common_bin_dir}
)
