#include "CanalVoz.h"

CanalVoz::CanalVoz() {

  logInstanciamento();
}

Mensagem CanalVoz::getUltimaMensagem() {
  return this->ultimaMensagem;
}
