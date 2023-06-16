#ifndef CANALVOZ_H
#define CANALVOZ_H

#include "Canal.cpp"
#include "Mensagem.cpp"

#include "../infra/Loggable.cpp"
class CanalVoz : public Canal, public Loggable {

  private:
    Mensagem ultimaMensagem;

  public:
    CanalVoz();
    Mensagem getUltimaMensagem();

};

#endif