cmake_minimum_required(VERSION 3.28)
project(LunarEngine LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(LunarEngine
   src/main.cpp
   src/bindings/r_types.cpp
   src/bindings/r_font.cpp
   src/bindings/r_fonts.cpp
   src/bindings/r_color.cpp
   src/bindings/r_audio.cpp
   src/bindings/r_input.cpp
   src/bindings/r_vector_int.cpp
   src/bindings/r_vector_float.cpp
   src/bindings/r_bitmap.cpp
   src/bindings/r_sprite.cpp
   src/bindings/r_graphics.cpp
   src/core/font.cpp
   src/core/color.cpp
   src/core/bitmap.cpp
   src/core/sprite.cpp
   src/singletons/debug.cpp
   src/singletons/scene.cpp
   src/singletons/project.cpp
   src/singletons/runtime.cpp
   src/singletons/renderer.cpp
   src/interfaces/disposable.cpp
   src/interfaces/renderable.cpp
   src/utils/path.cpp
   src/utils/string.cpp
   src/utils/boolean.cpp
   src/utils/integer.cpp
   src/resources/ruby_loader.cpp
   src/resources/fonts_cache.cpp
   src/resources/fonts_loader.cpp
   src/resources/graphics_cache.cpp
   src/resources/graphics_loader.cpp
)

add_custom_command(
   TARGET LunarEngine POST_BUILD

   COMMAND ${CMAKE_COMMAND} -E make_directory
      $<TARGET_FILE_DIR:LunarEngine>/fonts

   COMMAND ${CMAKE_COMMAND} -E make_directory
      $<TARGET_FILE_DIR:LunarEngine>/scripts

   COMMAND ${CMAKE_COMMAND} -E make_directory
      $<TARGET_FILE_DIR:LunarEngine>/graphics

   COMMAND ${CMAKE_COMMAND} -E copy_if_different
      ${CMAKE_SOURCE_DIR}/templates/fonts/Arial.ttf
      $<TARGET_FILE_DIR:LunarEngine>/fonts/Arial.ttf

   COMMAND ${CMAKE_COMMAND} -E copy_if_different
      ${CMAKE_SOURCE_DIR}/templates/game.cfg
      $<TARGET_FILE_DIR:LunarEngine>/game.cfg
)

target_link_libraries(LunarEngine
   PRIVATE
      SFML::Graphics
      ${CMAKE_CURRENT_SOURCE_DIR}/libraries/mruby/build/host/lib/libmruby.a
)

target_include_directories(LunarEngine
   PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/include
      ${CMAKE_CURRENT_SOURCE_DIR}/libraries/mruby/include
      ${CMAKE_CURRENT_SOURCE_DIR}/libraries/mruby/build/host/include
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT LunarEngine)
