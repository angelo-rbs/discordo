#include "../include/Canal.h"


std::string Canal::getNome() {
    return this->nome;
}

void Canal::setNome(std::string nome) {
    this->nome = nome;
}

bool Canal::operator==(Canal &canal) {
  this->nome == canal.nome;
}

