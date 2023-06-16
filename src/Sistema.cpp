#include "Sistema.h"


std::vector<Usuario> Sistema::getAllUsuarios() {
  return this->usuarios;
}

std::vector<Servidor> Sistema::getAllServidores() {
  return this->servidores;
}

int Sistema::getIdUsuarioLogado() {
  return this->idUsuarioLogado;
}

int Sistema::getIdServidorAtual() {
  return this->servidorAtual;
}

int Sistema::getIdCanalAtual() {
  return this->canalAtual;
}
