#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>

#include "../infra/Loggable.cpp"

static int USUARIO_GLOBAL_ID = 1;

class Usuario : Loggable {

  private:
    int id;
    std::string nome;
    std::string email;
    std::string senha;

  public:

    Usuario();
    Usuario(std::string nome, std::string email, std::string senha);


    int getId();
    void setId(int id);

    std::string getNome();
    void setNome(std::string nome);

    std::string getEmail();
    void setEmail(std::string email);

    std::string getSenha();
    void setSenha(std::string senha);

    static int getAndIncrementGlobalId();

    bool operator==(Usuario &usuario);
};

#endif