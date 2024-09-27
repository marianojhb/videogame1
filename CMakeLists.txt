cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(videogame1 src/main.cpp
)
target_link_libraries(videogame1 PRIVATE sfml-graphics)
target_compile_features(videogame1 PRIVATE cxx_std_17)

# Añadir rutas adicionales para buscar cabeceras
#include_directories(/build/_deps/sfml-src/include)

# Definir la ruta de recursos
set(RESOURCES_DIR "${CMAKE_SOURCE_DIR}/resources")

# Añadirlo como un define para que esté disponible en el código C++
add_definitions(-DRESOURCES_DIR=${RESOURCES_DIR})

# Incluir directorios y añadir el ejecutable
include_directories(${CMAKE_SOURCE_DIR}/src)
add_executable(my_sfml_project src/main.cpp)

if(WIN32)
    add_custom_command(
        TARGET videogame1
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
