SET(SRC
    game/resources/ResourceManager.cpp
    game/scene_graph/SceneNode.cpp
    game/scene_graph/SpriteNode.cpp
    game/World.cpp
    game/Game.cpp)

find_package(SFML 2 COMPONENTS system window graphics REQUIRED)

add_library(libgame ${SRC})

target_compile_features(libgame
                        PUBLIC
                        cxx_std_17)

target_compile_options(libgame
                       PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /Tp>
                       $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>)

target_include_directories(libgame
                           PUBLIC
                           ${SFML_INCLUDE_DIR}
                           ${CMAKE_CURRENT_SOURCE_DIR}/game
                           PRIVATE
                           ${CMAKE_CURRENT_SOURCE_DIR}/game/resources
                           ${CMAKE_CURRENT_SOURCE_DIR}/game/scene_graph)

target_link_libraries(libgame
                      PRIVATE
                      ${SFML_LIBRARIES})
