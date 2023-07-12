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
    Servidor(std::string nome, string descricao, int idDono, string codigoConvite);
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

    std::vector<Canal *>& getCanais();
    void addCanal(Canal* canal);

    std::vector<int> getParticipantesIds();

    int findParticipantInServer(int id);
    bool addParticipant(int id);
    Canal* findCanal();

    bool operator==(Servidor &servidor);

};

#endif