#ifndef CANALVOZ_H
#define CANALVOZ_H

#include "Canal.cpp"
#include "Mensagem.cpp"
class CanalVoz : Canal {

  private:
    Mensagem ultimaMensagem;

  public:
    Mensagem getUltimaMensagem();

};

#endif