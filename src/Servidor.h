#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <iostream>
#include <vector>

#include "Canal.h"

#include "../infra/Loggable.cpp"

using std::string;
class Servidor : Loggable {

  private:
    int usuarioDonoId;
    string nome;
    string descricao;
    string codigoConvite;
    std::vector<Canal *> canais;
    std::vector<int> participantesIds;

  public:
    int getUsuarioDonoId();
    void setUsuarioDonoId(int usuarioDonoId);

    string getNome();
    void setNome(string nome);

    string getDescricao();
    void setDescricao(string descricao);

    string getCodigoConvite();
    void setCodigoConvite(string codigoConvite);

    std::vector<Canal *> getCanais();

    std::vector<int> getParticipantesIds();

    bool operator==(Servidor &servidor);

};

#endif