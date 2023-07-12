#ifndef CANALTEXTO_H
#define CANALTEXTO_H

#include <iostream>
#include <vector>

#include "Canal.h"
#include "Mensagem.h"

class CanalTexto : public Canal {

  private:
    std::vector<Mensagem*> mensagens;

  public:
    CanalTexto(std::string nome);

    virtual void addMessage(Mensagem* mensagem);
    virtual void listMessages(std::vector<Usuario*> users);
    virtual vector<Mensagem*> getMensagens();

};


#endif