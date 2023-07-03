#include "include/CanalVoz.h"
#include "include/Mensagem.h"

CanalVoz::CanalVoz(std::string nome) : Canal(nome) {
  tipo = cte::voz;
}


Mensagem CanalVoz::getUltimaMensagem() {
  return this->ultimaMensagem;
}
