#include "include/Canal.h"

Canal::Canal(std::string nome) : nome(nome) {

}

std::string Canal::getNome() {
    return nome;
}

void Canal::setNome(std::string nome) {
    this->nome = nome;
}

int Canal::getTipo() {
  return tipo;
}

bool Canal::operator==(Canal &canal) {
  return this->nome == canal.nome;
}

