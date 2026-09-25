cmake_minimum_required(VERSION 3.10)
project(Treap)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Archivos fuente
set(TREAP_SOURCES
    src/treap/treap_core.cpp
    src/treap/insert.cpp
    src/treap/search.cpp
    src/treap/erase.cpp
)

# Ejecutable principal
add_executable(treap_demo src/main.cpp ${TREAP_SOURCES})

# Configuración de compilación
if(MSVC)
    target_compile_options(treap_demo PRIVATE /W4)
else()
    target_compile_options(treap_demo PRIVATE -Wall -Wextra -Wpedantic)
endif()
