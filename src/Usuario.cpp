#include "Usuario.h"

using std::string;

int Usuario::getAndIncrementGlobalId() {
  return USUARIO_GLOBAL_ID++;
}


// construtores

Usuario::Usuario() {
  id = getAndIncrementGlobalId();
  nome = "";
  senha = "";
  email = "";
}

Usuario::Usuario(string nome, string email, string senha) {
  id = getAndIncrementGlobalId();
  this->nome = nome;
  this->email = email;
  this->senha = senha;
}


// getters e setters

int Usuario::getId() {
  return this->id;
}

string Usuario::getNome() {
  return this->nome;
} 

string Usuario::getEmail() {
  return this->email;
}

string Usuario::getSenha() {
  return this->senha;
}

void Usuario::setId(int id) {
  this->id = id;
}

void Usuario::setNome(string nome) {
  this->nome = nome;
} 

void Usuario::setEmail(string email) {
  this->email = email;
}

void Usuario::setSenha(string senha) {
  this->senha = senha;
}


// sobrescrita de operadores

bool Usuario::operator==(Usuario &usuario) {
  return this->getId() == usuario.getId();
}


// funcionalidades

