#ifndef SISTEMA_H
#define SISTEMA_H

#include <iostream>
#include <vector>

#include "Usuario.h"
#include "Servidor.h"
#include "../infra/Loggable.cpp"

class Sistema : Loggable {

  private:
    std::vector<Usuario> usuarios;
    std::vector<Servidor> servidores;
    static int idUsuarioLogado;
    static int servidorAtual;
    static int canalAtual;

  public:
    std::vector<Usuario> getAllUsuarios();
    std::vector<Servidor> getAllServidores();
    int getIdUsuarioLogado();
    int getIdServidorAtual();
    int getIdCanalAtual();

};


#endif