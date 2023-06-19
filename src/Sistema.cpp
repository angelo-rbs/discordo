
#include "../include/Sistema.h"
#include "../include/Parser.h"
#include "../include/Constants.h"

// variáveis estáticas

int Sistema::idUsuarioLogado = cte::USUARIO_NAO_LOGADO;
int Sistema::idCanalAtual = cte::CANAL_INDEFINIDO;
int Sistema::idServidorAtual = cte::SERVIDOR_INDEFINIDO;

// métodos de acesso

std::vector<Usuario*> Sistema::getAllUsuarios() {
    return this->usuarios;
}

std::vector<Servidor*> Sistema::getAllServidores() {
    return this->servidores;
}

int Sistema::getIdUsuarioLogado() {
    return idUsuarioLogado;
}

int Sistema::getIdServidorAtual() {
    return idServidorAtual;
}

int Sistema::getIdCanalAtual() {
    return idCanalAtual;
}

int Sistema::incrementAndGetIdUsuarioLogado() {
    return Sistema::idUsuarioLogado++;
}

int Sistema::incrementAndGetServidorAtual() {
    return Sistema::idServidorAtual++;
}

int Sistema::incrementAndGetCanalAtual() {
    return Sistema::idCanalAtual++;
}

Usuario* Sistema::findUsuarioById(Usuario* user) {
    for (auto usuario : usuarios)
        if (usuario == user)
            return usuario;

    return nullptr;
}

Usuario* Sistema::findUsuarioByLogin(std::string email, std::string senha) {
    for (auto usuario : usuarios)
        if (usuario->getEmail() == email && usuario->getSenha() == senha)
            return usuario;

    return nullptr;
}

Usuario* Sistema::findUsuarioByEmail(std::string email) {
    for (auto usuario : usuarios)
        if (usuario->getEmail() == email)
            return usuario;

    return nullptr;
}

// funcionalidades

void Sistema::quit() {
    throw my_exit(0);
}

bool Sistema::createUser(std::string email, std::string senha, std::string nome) {
    Usuario* user = new Usuario(nome, email, senha);

    try {
        if (findUsuarioByLogin(email, senha) != nullptr)
            throw logic_error("já existe um usuário com este e-mail");

        usuarios.push_back(user);
        std::clog << "usuário criado com sucesso." << std::endl;
        return true;
    } catch (exception& e) {
        std::cerr << "erro ao tentar criar usuário: " << e.what() << std::endl;
        delete user;
        return false;
    }
}

bool Sistema::login(std::string email, std::string senha) {
    if (Sistema::idUsuarioLogado != cte::USUARIO_NAO_LOGADO) {
        std::clog << "já existe um usuário logado." << std::endl;
        return false;
    }

    Usuario* user = new Usuario();

    try {
        user = findUsuarioByLogin(email, senha);

        if (user != nullptr) {
            idUsuarioLogado = user->getId();

            std::cout << "usuário logado." << std::endl;
            return true;
        } else
            std::cout << "verifique suas credenciais e "
                         "tente novamente."
                      << std::endl;

        return false;
    } catch (exception& e) {
        std::cerr << "erro ao tentar login. verifique suas credenciais e tente "
                     "novamente."
                  << std::endl;
        delete user;
        return false;
    }
}

void Sistema::start() {
    try {
        Parser* p = new Parser();
        std::string commandLine, nome, email, senha;
        bool parserOk;
        int exit_flag = 0;

        while (!exit_flag) {
            getline(std::cin, commandLine);
            if (!p->parse(commandLine))
                continue;

            if (p->getCommand() == cte::SAIR) {
                quit();
            } else if (p->getCommand() == cte::CRIAR_USUARIO) {
                email = p->getArg(0);
                senha = p->getArg(1);
                nome = p->getArg(2);

                createUser(email, senha, nome);
            } else if (p->getCommand() == cte::LOGIN) {
                email = p->getArg(0);
                senha = p->getArg(1);

                login(email, senha);
            }
        }

        delete p;
    } catch (Sistema::my_exit& exit) {
        std::clog << "sessão Discordo encerrada." << std::endl;
    }
}