#ifndef CANALTEXTO_H
#define CANALTEXTO_H

#include <iostream>
#include <vector>

#include "Canal.h"
#include "Mensagem.h"

class CanalTexto : Canal {

  private:
    std::vector<Mensagem> mensagens;

  public:
    CanalTexto();
    std::vector<Mensagem> getMensagens();
};


#endif