#ifndef CANALVOZ_H
#define CANALVOZ_H

#include "Canal.h"
#include "Mensagem.h"

class CanalVoz : public Canal {

  private:
    Mensagem* ultimaMensagem;

  public:
    CanalVoz(std::string nome);
    Mensagem* getUltimaMensagem();

    virtual void addMessage(Mensagem*);
    virtual void listMessages(std::vector<Usuario*> users);

};

#endif