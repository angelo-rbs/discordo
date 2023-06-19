#ifndef MENSAGEM_H
#define MENSAGEM_H

#include <iostream>

class Mensagem {

  private:

    std::string dataHora; // que tal usar uma entidade de Tempo do C++?
    int enviadaPor;
    std::string conteudo;

  public:

    // nao faz sentido criar uma mensagem vazia

    Mensagem();
    Mensagem(std::string dataHora, int enviadaPor, std::string conteudo);

    std::string getDataHora();
    void setDataHora(std::string dataHora);

    int getEnviadaPor();
    void setEnviadaPor(int id);

    std::string getConteudo();
    void setConteudo(std::string conteudo);

    bool operator==(Mensagem &mensagem);
};


#endif