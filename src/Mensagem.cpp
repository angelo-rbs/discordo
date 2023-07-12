#include "include/Mensagem.h"
#include "../infra/Utils.cpp"

using std::string;

// construtor

Mensagem::Mensagem() = default;

Mensagem::Mensagem(int enviadaPor, std::string conteudo, std::string timestamp) {

  if (timestamp.empty())
    timestamp = currentDateTime();

  this->dataHora = timestamp;
  this->enviadaPor = enviadaPor;
  this->conteudo = conteudo;

}



// getters e setters

string Mensagem::getDataHora() {
  return this->dataHora;
} 

int Mensagem::getEnviadaPor() {
  return this->enviadaPor;
}

string Mensagem::getConteudo() {
  return this->conteudo;
}

void Mensagem::setDataHora(string dataHora) {
  this->dataHora = dataHora;
} 

void Mensagem::setEnviadaPor(int id) {

  // checagem se o usuario existe no sistema

  this->enviadaPor = id;
}

void Mensagem::setConteudo(string conteudo) {
  this->conteudo = conteudo;
}



// sobrescrita de operadores

bool Mensagem::operator==(Mensagem &msg) {
  return this->dataHora == msg.getDataHora()
      && this->conteudo == msg.getConteudo()
      && this->enviadaPor == msg.getEnviadaPor();
}

