#include "include/CanalTexto.h"
#include "include/Canal.h"
#include "include/Constants.h"

CanalTexto::CanalTexto(std::string nome) : Canal(nome) {
  tipo = cte::texto;
}

std::vector<Mensagem*> CanalTexto::getMensagens() {
  return mensagens;    
}

void CanalTexto::addMessage(Mensagem *msg) {
  this->mensagens.push_back(msg);
}

void CanalTexto::listMessages(std::vector<Usuario*> users) {

  Usuario *sender = nullptr;

  for (Mensagem *msg : mensagens) {

    for (Usuario *user : users)
      if (user->getId() == msg->getEnviadaPor()) {
        sender = user;
        break;
      }

    std::cout << formatMessage(msg, sender) << std::endl;
  }
}
