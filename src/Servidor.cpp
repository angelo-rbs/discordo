
#include <vector>

#include "../include/Servidor.h"
#include "../include/Constants.h"
#include "../include/Canal.h"

// construtores

Servidor::Servidor() {

  this->nome = "";
  this->descricao = "";
  this->usuarioDonoId = -1;
  this->canais;
  this->participantesIds;
  this->codigoConvite = "";

}

Servidor::Servidor(std::string nome, int idDono) {

  this->nome = nome;
  this->descricao = "";
  this->usuarioDonoId = idDono;
  this->canais;
  this->participantesIds;
  this->codigoConvite = "";

}

Servidor::~Servidor() {

  for (int i = canais.size(); i >= 0; --i)
    delete canais[i];

}


// métodos de acesso

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

int Servidor::findParticipant(int id) {
  
  for (int i = 0; i < participantesIds.size(); i++)
    if (participantesIds[i] == id) return id;

  return -1;
}

bool Servidor::addParticipant(int id) {

  if (findParticipant(id) == cte::USUARIO_NAO_ENCONTRADO) {
    participantesIds.push_back(id);
    return true;
  } else 
    return false;
}


//

bool Servidor::isFechado() {
  return this->codigoConvite != "";
}

// sobrecarga de operadores

bool Servidor::operator==(Servidor &servidor) {
  return this->nome == servidor.getNome();
} 
