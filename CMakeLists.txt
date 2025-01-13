cmake_minimum_required(VERSION 3.29) # FetchContent is available in 3.11+
project(CG_Creto_work)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

# Include directories (se necessário)
include_directories(${CMAKE_SOURCE_DIR}) # Inclui o diretório de origem

# Our Project
add_executable(${PROJECT_NAME}
        Algebra.cpp
        src/Plano/Plano.cpp
        src/Plano/Plano.h
        src/Circulo/Circulo.cpp
        src/Circulo/Circulo.h
        src/Triangulo/Triangulo.cpp
        src/Triangulo/Triangulo.h
        src/Iluminacao/Iluminacao.cpp
        src/Iluminacao/Iluminacao.h
        src/Objeto/Objeto.cpp   # ADICIONE
        src/Objeto/Objeto.h
        src/Raio/Raio.cpp       # ADICIONE
        src/Raio/Raio.h
        src/Esfera/Esfera.cpp   # ADICIONE
        src/Esfera/Esfera.h
        src/Cilindro/Cilindro.cpp # ADICIONE
        src/Cilindro/Cilindro.h
        src/Cone/Cone.cpp       # ADICIONE
        src/Cone/Cone.h
        src/Material/Material.cpp # ADICIONE
        src/Material/Material.h
        src/Malha/Malha.cpp
        src/Malha/Malha.h
        src/Ponto/Ponto.cpp
        src/Ponto/Ponto.h
        src/Aresta/Aresta.cpp
        src/Textura/Textura.cpp
        src/Textura/Textura.h
        src/PlanoTextura/PlanoTextura.cpp
        src/PlanoTextura/PlanoTextura.h
        src/Camera/Camera3de.h
        src/Camera/Camera.cpp
        src/ObjetoComplexo/ObjetoComplexo.h
        src/ObjetoComplexo/ObjetoComplexo.cpp
        bin/tarefa6.cpp


)

target_link_libraries(${PROJECT_NAME} raylib)


# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
