#ifndef CANALTEXTO_H
#define CANALTEXTO_H

#include <iostream>
#include <vector>

#include "Canal.cpp"
#include "Mensagem.cpp"

class CanalTexto : Canal {

  private:
    std::vector<Mensagem> mensagens;

  public:
    std::vector<Mensagem> getMensagens();
};


#endif