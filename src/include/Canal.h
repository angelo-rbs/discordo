#ifndef CANAL_H
#define CANAL_H

#include <iostream>

#include "../../infra/Loggable.cpp"

class Canal {

  private:
    std::string nome;

  public:
    std::string getNome();
    void setNome(std::string nome);

    bool operator==(Canal &canal);
};

#endif