#ifndef CANAL_H
#define CANAL_H

#include <iostream>

#include "Constants.h"

class Canal {

  private:
    std::string nome;

  protected:
    int tipo;

  public:
    Canal(std::string nome);

    std::string getNome();
    void setNome(std::string nome);

    int getTipo();

    bool operator==(Canal &canal);
};

#endif