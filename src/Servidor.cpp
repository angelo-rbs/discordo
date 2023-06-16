#include "Servidor.h"


int Servidor::getUsuarioDonoId() {
  return this->usuarioDonoId;
}

void Servidor::setUsuarioDonoId(int usuarioDonoId) {
  this->usuarioDonoId = usuarioDonoId;
}

string Servidor::getNome() {
  return this->nome;
}

void Servidor::setNome(string nome) {
  this->nome = nome;
}

string Servidor::getDescricao() {
  return descricao;
}

void Servidor::setDescricao(string descricao) {
  this->descricao = descricao;
}

string Servidor::getCodigoConvite() {
  return this->codigoConvite;
}

void Servidor::setCodigoConvite(string codigoConvite) {
  this->codigoConvite = codigoConvite;
}

std::vector<Canal*> Servidor::getCanais() {
  return this->canais;
}

std::vector<int> Servidor::getParticipantesIds() {
  return this->participantesIds;
}

bool Servidor::operator==(Servidor &servidor) {
  return this->codigoConvite == servidor.getCodigoConvite();
}
