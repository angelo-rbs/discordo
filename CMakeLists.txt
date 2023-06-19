cmake_minimum_required(VERSION 3.20.0)
project(Discordo)

include_directories( src/include )

add_executable(Discordo
               src/Canal.cpp
               src/CanalTexto.cpp
               src/CanalVoz.cpp
               src/include/Constants.h            
               src/Mensagem.cpp
               src/Parser.cpp
               src/Servidor.cpp
               src/Sistema.cpp
               src/Usuario.cpp
               src/main.cpp )
