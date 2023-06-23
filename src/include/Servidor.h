#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <iostream>
#include <vector>

#include "Canal.h"

using std::string;
class Servidor {

  private:
    int usuarioDonoId;
    string nome;
    string descricao;
    string codigoConvite;
    std::vector<Canal *> canais;
    std::vector<int> participantesIds;

  public:
    Servidor();
    Servidor(std::string nome, int idDono);
    ~Servidor();

    int getUsuarioDonoId();
    void setUsuarioDonoId(int usuarioDonoId);

    string getNome();
    void setNome(string nome);

    string getDescricao();
    void setDescricao(string descricao);

    string getCodigoConvite();
    void setCodigoConvite(string codigoConvite);
    bool isFechado();

    std::vector<Canal *> getCanais();

    std::vector<int> getParticipantesIds();

    int findParticipant(int id);
    bool addParticipant(int id);
    Canal* findCanal();

    bool operator==(Servidor &servidor);

};

#endif