#include <stdio.h>
#include <algorithm>

#include "../infra/Exits.cpp"
#include "include/Canal.h"
#include "include/CanalTexto.h"
#include "include/CanalVoz.h"
#include "include/Constants.h"
#include "include/Parser.h"
#include "include/Sistema.h"


// variáveis estáticas

int Sistema::idUsuarioLogado = cte::USUARIO_NAO_LOGADO;
std::string Sistema::nomeCanalAtual = cte::CANAL_INDEFINIDO;
std::string Sistema::nomeServidorAtual = cte::SERVIDOR_INDEFINIDO;

// construtores

Sistema::~Sistema() {
    for (int i = 0; i < servidores.size(); i++)
        delete servidores[i];

    for (int i = 0; i < usuarios.size(); i++)
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

std::string Sistema::getNomeCanalAtual() {
    return nomeCanalAtual;
}

Canal* Sistema::getCanalAtual() {
    return findCanal(nomeCanalAtual);
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

Canal* Sistema::findCanal(std::string nome) {
    Servidor* atual = getServidorAtual();

    for (Canal* canal : atual->getCanais())
        if (canal->getNome() == nome)
            return canal;

    return nullptr;
}

std::string Sistema::tipoToString(int tipo) {
    if (tipo == cte::voz) {
        return "voz";
    } else if (tipo == cte::texto)
        return "texto";
    else
        return "";
}

Servidor* Sistema::getServidorAtual() {
    if (nomeServidorAtual == cte::SERVIDOR_INDEFINIDO)
        return nullptr;

    return findServidor(nomeServidorAtual);
}

bool Sistema::isComandoDeBoot(std::string comando) {
    return (comando == "create-user") || (comando == "login") || (comando == "quit");
}

bool Sistema::logado() {
    return idUsuarioLogado != cte::USUARIO_NAO_LOGADO;
}

bool Sistema::canalDefinido() {
    return nomeCanalAtual != cte::CANAL_INDEFINIDO;
}

bool Sistema::servidorDefinido() {
    return nomeServidorAtual != cte::SERVIDOR_INDEFINIDO;
}

// funcionalidades

void Sistema::quit() {
    throw quit_exit("lançado sinal de saída");
}

bool Sistema::createUser(std::string email, std::string senha, std::string nome) {
    try {
        if (findUsuarioByEmail(email) != nullptr)
            throw early_exit("já existe um usuário com este e-mail");

        usuarios.push_back(new Usuario(nome, email, senha));

        std::clog << "usuário criado com sucesso." << std::endl;
        return true;

    } catch (early_exit& e) {
        std::cerr << "erro ao tentar criar usuário: " << e.msg << std::endl;
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
    nomeServidorAtual = cte::SERVIDOR_INDEFINIDO;
    nomeCanalAtual = cte::CANAL_INDEFINIDO;

    std::cout << "desconectado" << std::endl;
}

bool Sistema::createServer(std::string nome) {
    try {
        if (findServidor(nome) != nullptr)
            throw early_exit("já existe um servidor com esse nome");

        Servidor* s = new Servidor(nome, idUsuarioLogado);
        s->addParticipant(idUsuarioLogado);

        servidores.push_back(s);
        nomeServidorAtual = nome;

        std::cout << "servidor criado." << std::endl;
        return true;

    } catch (early_exit& e) {
        std::cout << "erro ao criar servidor: " << e.msg << std::endl;
        return false;
    }
}

bool Sistema::setServerDescription(std::string serverName, std::string description) {
    try {
        Servidor* servidor = findServidor(serverName);

        if (servidor == nullptr)
            throw early_exit("esse servidor não existe");

        if (servidor->getUsuarioDonoId() != idUsuarioLogado)
            throw early_exit("você não pode mudar a descrição de um servidor que não é seu");

        servidor->setDescricao(description);
        std::cout << "descrição do servidor " << serverName << " alterada" << std::endl;
        return true;

    } catch (early_exit& e) {
        std::cerr << "erro ao mudar descrição do servidor: " << e.msg << std::endl;
        return false;
    }
}

bool Sistema::setInviteCode(std::string serverName, std::string newCode) {
    try {
        Servidor* servidor = findServidor(serverName);

        if (servidor == nullptr)
            throw early_exit("esse servidor não existe");

        if (servidor->getUsuarioDonoId() != idUsuarioLogado)
            throw early_exit("você não pode alterar o código de um servidor que não é dono");

        servidor->setCodigoConvite(newCode);
        std::cout << "código-convite alterado com sucesso" << std::endl;
        return true;

    } catch (early_exit& e) {
        std::cerr << "erro ao mudar código-convite: " << e.msg << std::endl;
        return false;
    }
}

void Sistema::listServers() {
    std::cout << "----------------------------------------" << std::endl;

    for (auto server : servidores)
        std::cout << server->getNome() << std::endl;

    std::cout << "----------------------------------------" << std::endl;
}

bool Sistema::removeServer(std::string serverName) {
    try {
        Servidor* server = findServidor(serverName);
        if (server == nullptr)
            throw early_exit("esse servidor não existe");

        if (server->getUsuarioDonoId() != idUsuarioLogado)
            throw early_exit("você não é dono do servidor");

        for (int i = 0; i < servidores.size(); i++) {
            if (servidores[i]->getNome() == serverName) {
                if (servidores[i]->getNome() == nomeServidorAtual) 
                    nomeServidorAtual = cte::SERVIDOR_INDEFINIDO;

                servidores.erase(servidores.begin() + i);
                delete server;  // essa linha deveria existir?
                std::cout << serverName << " removido" << std::endl;
                return true;
            }
        }

        return false;

    } catch (early_exit& e) {
        std::cerr << "erro ao remover servidor: " << e.msg << std::endl;
        return false;
    }
}

bool Sistema::enterServer(std::string serverName, std::string givenInviteCode = "") {
    try {
        Servidor* toEnter = findServidor(serverName);
        if (toEnter == nullptr)
            throw early_exit("esse servidor não existe");

        if (!toEnter->findParticipantInServer(idUsuarioLogado) == cte::USUARIO_NAO_ENCONTRADO)
            throw early_exit("você já está no servidor");

        if (toEnter->getUsuarioDonoId() != idUsuarioLogado) {
            if (toEnter->isFechado()) {
                if (givenInviteCode == "")
                    throw early_exit("o servidor requer código de convite");
                if (givenInviteCode != toEnter->getCodigoConvite())
                    throw early_exit("código errado. tente novamente.");
            }
        }

        toEnter->addParticipant(idUsuarioLogado);
        nomeServidorAtual = toEnter->getNome();

        std::cout << "entrou no servidor com sucesso" << std::endl;
        return true;

    } catch (early_exit& e) {
        std::cerr << e.msg << std::endl;
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
    Servidor* server = getServidorAtual();
    Usuario* user;

    if (server == nullptr)
        throw early_exit("não existe servidor atual definido");

    std::cout << "----------------------------------------" << std::endl;
    std::cout << server->getParticipantesIds().size() << " participantes de " << server->getNome() << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    for (int id : server->getParticipantesIds()) {
        user = findUsuarioById(id);
        std::cout << user->getNome() << std::endl;
    }

    std::cout << "----------------------------------------" << std::endl;
}

void Sistema::listChannels() {
    Servidor* servidor = getServidorAtual();

    std::vector<Canal*> canaisTexto;
    std::vector<Canal*> canaisVoz;

    for (Canal* canal : servidor->getCanais()) {
        if (canal->getTipo() == cte::texto)
            canaisTexto.push_back(canal);
        else if (canal->getTipo() == cte::voz)
            canaisVoz.push_back(canal);
    }

    std::cout << "servidor \"" << servidor->getNome() << "\"" << std::endl;
    std::cout << servidor->getCanais().size() << " canais totais" << std::endl;

    std::cout << "#canais de texto (" << canaisTexto.size() << ")" << std::endl;
    for (Canal* canal : canaisTexto)
        std::cout << canal->getNome() << std::endl;

    std::cout << "#canais de voz (" << canaisVoz.size() << ")" << std::endl;
    for (Canal* canal : canaisVoz)
        std::cout << canal->getNome() << std::endl;

    std::cout << std::endl;
}

bool Sistema::createChannel(std::string nome, std::string tipo) {
    Canal* canal;

    try {
        Servidor* atual = getServidorAtual();
        if (atual == nullptr)
            throw early_exit("servidor não encontrado");

        // verifica existência

        for (Canal* it : atual->getCanais())
            if (it->getNome() == nome && tipoToString(it->getTipo()) == tipo)
                throw early_exit("canal de " + tipo + " \"" + nome + "\" já existe.");

        // cria o canal

        if (tipo == "texto") {
            canal = new CanalTexto(nome);
        } else if (tipo == "voz")
            canal = new CanalVoz(nome);
        else
            throw early_exit("tipo de canal inexistente");

        atual->addCanal(canal);
        return true;

    } catch (early_exit& e) {
        std::cout << "erro ao tentar criar canal: " << e.msg << std::endl;
        return false;
    }
}

bool Sistema::enterChannel(std::string nome) {
    if (findCanal(nome) != nullptr) {
        nomeCanalAtual = nome;
        return true;

    } else {
        std::cout << "canal inexistente" << std::endl;
        return false;
    }
}

bool Sistema::leaveChannel() {
    if (!canalDefinido()) {
        std::cout << "você não está visualizando nenhum canal" << std::endl;
        return false;

    } else {
        Canal* canal = getCanalAtual();

        std::cout << "você saiu do canal " << canal->getNome() << std::endl;
        nomeCanalAtual = cte::CANAL_INDEFINIDO;
        return true;
    }
}


void Sistema::sendMessage(std::string msg) {
    Mensagem* toAdd = new Mensagem(idUsuarioLogado, msg);

    try {
        Canal* canalAtual = findCanal(nomeCanalAtual);
        if (canalAtual == nullptr)
            throw early_exit("entre num canal para continuar");

        canalAtual->addMessage(toAdd);

    } catch (early_exit& e) {
        std::cout << "erro ao tentar enviar mensagem: " << e.msg << std::endl;
    }
}

void Sistema::listMessages() {

    try {
        Canal* canalAtual = findCanal(nomeCanalAtual);
        if (canalAtual == nullptr)
            throw early_exit("entre num canal para continuar");

        canalAtual->listMessages(getAllUsuarios());

    } catch (early_exit& e) {
        std::cout << "erro ao tentar enviar mensagem: " << e.msg << std::endl;
    }
}

void Sistema::start() {
    Parser* p = new Parser();

    try {
        std::string commandLine, nome, email, senha, desc, codigo, command, tipo, mensagem;
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

            command = p->getCommand();

            if (command == cte::SAIR) {
                quit();
            } else if (command == cte::CRIAR_USUARIO) {
                email = p->getSimpleArg(0);
                senha = p->getSimpleArg(1);
                nome = p->getSpacedArg();

                createUser(email, senha, nome);
            } else if (command == cte::LOGIN) {
                email = p->getSimpleArg(0);
                senha = p->getSimpleArg(1);

                login(email, senha);
            } else if (command == cte::DESCONECTAR) {
                disconnect();

            } else if (command == cte::CRIAR_SERVIDOR) {
                nome = p->getSimpleArg(0);
                createServer(nome);
            } else if (command == cte::LISTAR_SERVIDORES) {
                listServers();
            } else if (command == cte::MUDAR_DESCRICAO_SERVIDOR) {
                nome = p->getSimpleArg(0);
                desc = p->getSpacedArg();

                setServerDescription(nome, desc);
            } else if (command == cte::MUDAR_CONVITE_SERVIDOR) {
                nome = p->getSimpleArg(0);
                codigo = p->getSpacedArg();

                setInviteCode(nome, codigo);
            } else if (command == cte::REMOVER_SERVIDOR) {
                nome = p->getSimpleArg(0);

                removeServer(nome);
            } else if (command == cte::ENTRAR_SERVIDOR) {
                nome = p->getSimpleArg(0);
                codigo = p->getSpacedArg();

                enterServer(nome, codigo);
            } else if (command == cte::SAIR_SERVIDOR) {
                leaveServer();
            } else if (command == cte::LISTAR_PARTICIPANTES) {
                listParticipants();
            } else if (command == cte::LISTAR_CANAIS) {
                listChannels();
            } else if (command == cte::CRIAR_CANAL) {
                nome = p->getSimpleArg(0);
                tipo = p->getSimpleArg(1);

                createChannel(nome, tipo);
            } else if (command == cte::ENTRAR_CANAL) {
                nome = p->getSimpleArg(0);

                enterChannel(nome);
            } else if (command == cte::SAIR_CANAL) {
                leaveChannel();
            } else if (command == cte::ENVIAR_MENSAGEM) {
                mensagem = p->getSpacedArg();

                sendMessage(mensagem);
            } else if (command == cte::LISTAR_MENSAGENS) {

                listMessages();
            } else {

                std::cout << "comando não reconhecido" << std::endl;
            }
        }

        delete p;
    } catch (quit_exit& exit) {
        delete p;
        std::clog << "sessão Discordo encerrada." << std::endl;
    } catch (std::exception& e) {
        std::cout << "erro no start(): " << e.what() << std::endl;
        throw exception();
        delete p;
    }
}