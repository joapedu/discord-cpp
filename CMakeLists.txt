cmake_minimum_required(VERSION 3.22.1)
project(teste VERSION 0.1 LANGUAGES CXX )

set( CMAKE_CXX_FLAGS "-Wall")

include_directories( include )

add_executable( Concordo
                src/usuario.cpp
                src/sistema.cpp
                src/servidor.cpp
                src/executor.cpp
                src/concordo.cpp
                src/canal.cpp
                )

set_property(TARGET Concordo PROPERTY CXX_STANDARD 14)