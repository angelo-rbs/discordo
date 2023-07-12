#include "include/CanalVoz.h"
#include "include/Canal.h"
#include "include/Mensagem.h"

CanalVoz::CanalVoz(std::string nome) : Canal(nome) {
  tipo = cte::voz;
}


Mensagem* CanalVoz::getUltimaMensagem() {
  return this->ultimaMensagem;
}

void CanalVoz::addMessage(Mensagem *msg) {
  this->ultimaMensagem = msg;
}


void CanalVoz::listMessages(std::vector<Usuario*> users) {

  Usuario *sender = nullptr;
  Mensagem *msg = this->ultimaMensagem;

  for (Usuario *user : users)
    if (user->getId() == msg->getEnviadaPor()) {
      sender = user;
      break;
    }

  std::cout << formatMessage(msg, sender) << std::endl;
}

vector<Mensagem*> CanalVoz::getMensagens() {
  vector<Mensagem*> msgs;

  if (ultimaMensagem != nullptr)
    msgs.push_back(ultimaMensagem);

  return msgs;
}
