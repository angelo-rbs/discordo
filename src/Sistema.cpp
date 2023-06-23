
#include "../include/Sistema.h"
#include "../include/Constants.h"
#include "../include/Parser.h"
#include "../infra/Exits.cpp"

// variáveis estáticas

int Sistema::idUsuarioLogado = cte::USUARIO_NAO_LOGADO;
int Sistema::idCanalAtual = cte::CANAL_INDEFINIDO;
std::string Sistema::nomeServidorAtual = cte::SERVIDOR_INDEFINIDO;

// construtores

Sistema::Sistema() {}

Sistema::~Sistema() {
    for (int i = servidores.size() - 1; i >= 0; i--)
        delete servidores[i];

    for (int i = usuarios.size() - 1; i >= 0; i--)
        delete usuarios[i];
}

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

std::string Sistema::getNomeServidorAtual() {
    return nomeServidorAtual;
}

int Sistema::getIdCanalAtual() {
    return idCanalAtual;
}

Usuario* Sistema::findUsuarioById(int id) {
    for (auto usuario : usuarios)
        if (usuario->getId() == id)
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

Servidor* Sistema::findServidor(std::string name) {
    for (auto servidor : servidores)
        if (servidor->getNome() == name)
            return servidor;

    return nullptr;
}

Servidor* Sistema::getServidorAtual() {

    if (nomeServidorAtual == cte::SERVIDOR_INDEFINIDO) return nullptr;

    return findServidor(nomeServidorAtual);
}

bool Sistema::isComandoDeBoot(std::string comando) {
    return (comando == "create-user") || (comando == "login") || (comando == "quit");
}

bool Sistema::logado() {
    return idUsuarioLogado != cte::USUARIO_NAO_LOGADO;
}

bool Sistema::canalDefinido() {
    return idCanalAtual != cte::CANAL_INDEFINIDO;
}

bool Sistema::servidorDefinido() {
    return nomeServidorAtual != cte::SERVIDOR_INDEFINIDO;
}

// funcionalidades

void Sistema::quit() {
    throw quit_exit(0);
}

bool Sistema::createUser(std::string email, std::string senha, std::string nome) {
    try {
        if (findUsuarioByEmail(email) != nullptr)
            throw early_exit("já existe um usuário com este e-mail");

        usuarios.push_back(new Usuario(nome, email, senha));

        std::clog << "usuário criado com sucesso." << std::endl;
        return true;

    } catch (early_exit& e) {
        std::cerr << "erro ao tentar criar usuário: " << e.what() << std::endl;
        return false;
    }
}

bool Sistema::login(std::string email, std::string senha) {
    if (Sistema::idUsuarioLogado != cte::USUARIO_NAO_LOGADO) {
        std::clog << "já existe um usuário logado." << std::endl;
        return false;
    }

    Usuario* user;

    try {
        user = findUsuarioByLogin(email, senha);

        if (user != nullptr) {
            idUsuarioLogado = user->getId();

            std::cout << "logado como " << email << "." << std::endl;
            return true;

        } else
            std::cout << "verifique suas credenciais e tente novamente." << std::endl;

        return false;

    } catch (exception& e) {
        std::cerr << "erro ao tentar login. verifique suas credenciais e tente "
                     "novamente."
                  << std::endl;
        delete user;
        return false;
    }
}

void Sistema::disconnect() {
    if (!logado()) {
        std::cout << "não existe usuário conectado" << std::endl;
        return;
    }

    Usuario* user = Sistema::findUsuarioById(idUsuarioLogado);
    std::cout << "desconectando usuário " << user->getEmail() << "..." << std::endl;

    idUsuarioLogado = cte::USUARIO_NAO_LOGADO;
    std::cout << "desconectado" << std::endl;
}

bool Sistema::createServer(std::string nome) {
    try {
        if (findServidor(nome) != nullptr)
            throw early_exit("já existe um servidor com esse nome");

        servidores.push_back(new Servidor(nome, idUsuarioLogado));
        std::cout << "servidor criado." << std::endl;
        return true;

    } catch (early_exit& e) {

        std::cout << "erro ao criar servidor: " << e.what() << std::endl;
        return false;
    }
}


bool Sistema::setServerDescription(std::string serverName, std::string description) {
    try {
        Servidor* servidor = findServidor(serverName);

        if (servidor == nullptr)
            throw early_exit("servidor referido não existe");

        servidor->setDescricao(description);
        std::cout << "descrição alterada com sucesso" << std::endl;
        return true;

    } catch (early_exit& e) {
        std::cerr << "erro ao mudar descrição do servidor: " << e.what() << std::endl;
        return false;
    }
}

bool Sistema::setInviteCode(std::string serverName, std::string newCode) {
    try {
        Servidor* servidor = findServidor(serverName);

        if (servidor == nullptr)
            throw early_exit("esse servidor não existe");

        servidor->setCodigoConvite(newCode);
        std::cout << "código-convite alterado com sucesso" << std::endl;
        return true;

    } catch (early_exit& e) {
        std::cerr << "erro ao mudar código-convite: " << e.what() << std::endl;
        return false;
    }
}

void Sistema::listServers() {
    std::cout << "----------------------------------------" << std::endl;

    for (auto server : servidores)
        std::cout << server->getNome() << std::endl;

    std::cout << "----------------------------------------" << std::endl;
}

bool Sistema::removeServer(std::string serverName, int idCommandCaller) {
    try {

        if (idCommandCaller != idUsuarioLogado) throw early_exit("você não é dono do servidor");

        Servidor *server = findServidor(serverName);
        if (server == nullptr) throw early_exit("servidor com esse nome não encontradp");

        for (int i = 0; i < servidores.size(); i++) {
            
            if (servidores[i]->getNome() == serverName) {
                servidores.erase(servidores.begin() + i);
                delete server;                                      // essa linha deveria existir?
                return true;
            }
        }

        return false;

    } catch (early_exit& e) {

        std::cerr << "erro ao remover servidor: " << e.what() << std::endl;
        return false;
    }
}

bool Sistema::enterServer(std::string serverName, std::string givenInviteCode = "") {

    try {

        Servidor *toEnter = findServidor(serverName);
        if (toEnter == nullptr) throw early_exit("o servidor referido não existe");

        if (toEnter->getUsuarioDonoId() != idUsuarioLogado) {

            if (toEnter->isFechado()) {
                if (givenInviteCode == "") throw early_exit("o servidor requer código de convite");
                if (givenInviteCode != toEnter->getCodigoConvite()) throw  early_exit("código errado. tente novamente.");
            }

            if (givenInviteCode == toEnter->getCodigoConvite() && !toEnter->findParticipant(idUsuarioLogado))
                toEnter->addParticipant(idUsuarioLogado);
        }

        nomeServidorAtual = toEnter->getNome();

        return true;

    } catch (early_exit &e) {
        std::cerr << "erro ao tentar entrar no servidor" << e.what() << std::endl;
        return false;
    }
}

bool Sistema::leaveServer() {

    if (nomeServidorAtual == cte::SERVIDOR_INDEFINIDO) {
        std::cout << "você não está visualizando nenhum servidor" << std::endl;
        return false;
    } else {
        std::cout << "saindo do servidor \"" << nomeServidorAtual << "\"" << std::endl; 
        nomeServidorAtual = cte::SERVIDOR_INDEFINIDO;
        return true;
    }
}

void Sistema::listParticipants() {

    Servidor *server = getServidorAtual();
    Usuario *user;

    for (int id : server->getParticipantesIds()) {
        user = findUsuarioById(id);
        std::cout << user->getNome() << std::endl;
    }

}

void Sistema::start() {
    Parser* p = new Parser();

    try {
        std::string commandLine, nome, email, senha;
        bool parserOk;
        int exit_flag = 0;

        while (!exit_flag) {
            getline(std::cin, commandLine);

            if (!p->parse(commandLine))
                continue;

            if (!isComandoDeBoot(p->getCommand()) && !logado()) {
                std::cout << "comando indisponível antes do login" << std::endl;
                continue;
            }

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
    } catch (quit_exit& exit) {
        delete p;
        std::clog << "sessão Discordo encerrada." << std::endl;
    }
}