#ifndef CANALTEXTO_H
#define CANALTEXTO_H

#include <iostream>
#include <vector>

#include "Canal.cpp"
#include "Mensagem.cpp"

class CanalTexto : Canal, Loggable {

  private:
    std::vector<Mensagem> mensagens;

  public:
    CanalTexto();
    std::vector<Mensagem> getMensagens();
};


#endif