#include "dialogs.h"

  Usuario* dialog::createUser() {
    std::string nome, email, senha;

    std::cout << "Qual o nome do usuário?" << std::endl;
    getline(std::cin, nome);

    std::cout << "Qual o email do usuário?" << std::endl;
    getline(std::cin, email);

    std::cout << "Qual a senha do usuário?" << std::endl;
    getline(std::cin, senha);

    return new Usuario(nome, email, senha);
  }

  Usuario* dialog::login() {
    std::string email, senha;

    std::cout << "Qual o email do usuário?" << std::endl;
    getline(std::cin, email);

    std::cout << "Qual a senha do usuário?" << std::endl;
    getline(std::cin, senha);

    Usuario *user = new Usuario();
    user->setEmail(email);
    user->setSenha(senha);

    return user;
  }