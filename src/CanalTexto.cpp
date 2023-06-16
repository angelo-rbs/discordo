#include "CanalTexto.h"

CanalTexto::CanalTexto() {


  logInstanciamento();
}

std::vector<Mensagem> CanalTexto::getMensagens() {
  return this->mensagens;    
}
