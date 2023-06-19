#ifndef SISTEMA_H
#define SISTEMA_H

#include <iostream>
#include <vector>
#include <exception>

#include "Usuario.h"
#include "Servidor.h"
#include "../infra/Loggable.cpp"

class Sistema : Loggable
{

private:
  std::vector<Usuario*> usuarios;
  std::vector<Servidor*> servidores;
  static int idUsuarioLogado;
  static int idServidorAtual;
  static int idCanalAtual;

public:
  Sistema() { }

  struct my_exit : public std::exception
  {
    int value;
    my_exit(int value) : value(value) {}
  };

  std::vector<Usuario*> getAllUsuarios();
  std::vector<Servidor*> getAllServidores();
  int getIdUsuarioLogado();
  int getIdServidorAtual();
  int getIdCanalAtual();
  int incrementAndGetIdUsuarioLogado();
  int incrementAndGetServidorAtual();
  int incrementAndGetCanalAtual();

  Servidor* findServidor(Servidor *server);
  Usuario* findUsuarioById(Usuario *user);
  Usuario* findUsuarioByLogin(std::string email, std::string senha);
  Usuario* findUsuarioByEmail(std::string email);

  void start();
  void quit();
  bool createUser(std::string email, std::string senha, std::string nome);
  bool login(std::string email, std::string senha);
};

#endif