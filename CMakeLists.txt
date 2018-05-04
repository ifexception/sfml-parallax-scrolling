cmake_minimum_required(VERSION 3.6)
project(lt47)

set(CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/cmake_modules"
     ${CMAKE_MODULE_PATH})

add_subdirectory(src)

add_executable(lt47 src/main.cpp)
target_link_libraries(lt47
                      libgame)

add_custom_command(TARGET lt47 POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/assets
                   $<TARGET_FILE_DIR:lt47>
                   COMMENT "Copying to output directory")
