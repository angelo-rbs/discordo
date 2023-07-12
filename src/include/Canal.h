#ifndef CANAL_H
#define CANAL_H

#include <iostream>

#include "Constants.h"
#include "Mensagem.h"
#include "Usuario.h"

class Canal {

  private:
    std::string nome;

  protected:
    int tipo;
    std::string formatMessage(Mensagem *msg, Usuario* sender);

  public:
    Canal(std::string nome);
    virtual ~Canal();

    std::string getNome();
    void setNome(std::string nome);

    int getTipo();

    bool operator==(Canal &canal);
    
    virtual void addMessage(Mensagem* mensagem) = 0;
    virtual void listMessages(std::vector<Usuario*> users) = 0;
    virtual vector<Mensagem*> getMensagens() = 0;
};

#endif