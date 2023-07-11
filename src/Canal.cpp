#include "include/Canal.h"
#include "include/Mensagem.h"
#include "include/Sistema.h"
#include "include/Usuario.h"

Canal::Canal(std::string nome) : nome(nome) {}

Canal::~Canal() {
    
}

std::string Canal::getNome() {
    return nome;
}

void Canal::setNome(std::string nome) {
    this->nome = nome;
}

int Canal::getTipo() {
    return tipo;
}

bool Canal::operator==(Canal& canal) {
    return this->nome == canal.nome;
}

// void Canal::addMessage(Mensagem* mensagem);
// void Canal::listMessages(std::vector<Usuario*> users);

std::string Canal::formatMessage(Mensagem* msg, Usuario* sender) {
    if (sender == nullptr)
        return "<rementente da mensagem não encontrado>";

    std::string formated;

    formated += sender->getNome();
    formated += " <" + msg->getDataHora() + ">: ";
    formated += msg->getConteudo();

    return formated;
}
