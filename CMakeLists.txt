cmake_minimum_required(VERSION 3.28)
project(LunarEngine LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIGURATION>")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDLIMAGE_JXL OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_TIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_AVIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_WEBP OFF CACHE BOOL "" FORCE)

add_subdirectory(third_party/SDL EXCLUDE_FROM_ALL)
add_subdirectory(third_party/SDL_image EXCLUDE_FROM_ALL)

add_executable(LunarEngine
   src/main.cpp
   src/bindings/r_types.cpp
   src/bindings/r_color.cpp
   src/bindings/r_audio.cpp
   src/bindings/r_input.cpp
   src/bindings/r_kernel.cpp
   src/bindings/r_vector_int.cpp
   src/bindings/r_vector_float.cpp
   src/bindings/r_bitmap.cpp
   src/bindings/r_sprite.cpp
   src/bindings/r_texture.cpp
   src/bindings/r_textures.cpp
   src/core/color.cpp
   src/core/bitmap.cpp
   src/core/sprite.cpp
   src/core/texture.cpp
   src/singletons/scene.cpp
   src/singletons/project.cpp
   src/singletons/runtime.cpp
   src/singletons/timestamp.cpp
   src/singletons/interpreter.cpp
   src/singletons/renderer.cpp
   src/interfaces/disposable.cpp
   src/interfaces/renderable.cpp
   src/utils/path.cpp
   src/utils/string.cpp
   src/utils/boolean.cpp
   src/utils/integer.cpp
   src/resources/font_manager.cpp
   src/resources/texture_manager.cpp
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
      ${CMAKE_SOURCE_DIR}/assets/fonts/Arial.ttf
      $<TARGET_FILE_DIR:LunarEngine>/fonts/Arial.ttf

   COMMAND ${CMAKE_COMMAND} -E copy_if_different
      ${CMAKE_SOURCE_DIR}/assets/game.cfg
      $<TARGET_FILE_DIR:LunarEngine>/game.cfg
)

target_link_libraries(LunarEngine
   PRIVATE
      SDL3::SDL3
      SDL3_image::SDL3_image
      ${CMAKE_CURRENT_SOURCE_DIR}/third_party/mruby/build/host/lib/libmruby.lib
      ws2_32
      iphlpapi
)

target_include_directories(LunarEngine
   PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR}/include
      ${CMAKE_CURRENT_SOURCE_DIR}/third_party/mruby/include
      ${CMAKE_CURRENT_SOURCE_DIR}/third_party/mruby/build/host/include
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT LunarEngine)
