#
#   project
#

cmake_minimum_required(VERSION 3.20)
project(nyx C)

#
#   executable
#

file(GLOB_RECURSE source_files CONFIGURE_DEPENDS src/*.c)
add_executable(nyx ${source_files})

target_link_libraries(nyx PRIVATE
    opengl32
    gdi32
    user32
)

set_target_properties(nyx PROPERTIES
    C_STANDARD 17
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
