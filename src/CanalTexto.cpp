#include "include/CanalTexto.h"
#include "include/Constants.h"

CanalTexto::CanalTexto(std::string nome) : Canal(nome) {
  tipo = cte::texto;
}

std::vector<Mensagem> CanalTexto::getMensagens() {
  return this->mensagens;    
}
