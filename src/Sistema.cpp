#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <limits>

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

void Sistema::addServer(Servidor *toAdd) {
    this->servidores.push_back(toAdd);
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

        if (toEnter->addParticipant(idUsuarioLogado))
            std::cout << "participante adicionado ao servidor" << std::endl;
        else
            std::cout << "ERRO AO ADICIONAR PARTICIPANTE" << std::endl;


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

    try {
        if (server == nullptr)
            throw early_exit("você não conectado a um servidor");

        std::cout << "----------------------------------------" << std::endl;
        std::cout << server->getParticipantesIds().size() << " participantes de " << server->getNome() << std::endl;
        std::cout << "----------------------------------------" << std::endl;

        for (int id : server->getParticipantesIds()) {
            user = findUsuarioById(id);
            std::cout << user->getNome() << std::endl;
        }

        std::cout << "----------------------------------------" << std::endl;
    } catch (early_exit &e) {
        std::cout << e.msg << std::endl;
    }
}

void Sistema::listChannels() {

    try {

        std::clog << "entrou no try do listChannels" << std::endl;
        Servidor* servidor = getServidorAtual();
        if (servidor == nullptr)
            throw early_exit("você não está conectado a um servidor");

        std::vector<Canal*> canaisTexto;
        std::vector<Canal*> canaisVoz;

        std::clog << "servidor conectado: " << servidor->getNome() << std::endl;

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

    } catch (early_exit &e) {
        std::cerr << e.msg << std::endl;
    }
}

bool Sistema::createChannel(std::string nome, std::string tipo) {
    Canal* canal;

    try {
        Servidor* atual = getServidorAtual();
        if (atual == nullptr)
            throw early_exit("você não está conectado a um servidor");

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
    string empty;
    Mensagem* toAdd = new Mensagem(idUsuarioLogado, msg, empty);

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

void Sistema::salvarUsuarios() {
    // std::cout << "entrou no salvar usuários" << std::endl;

    vector<Usuario*> users = usuarios;
    ofstream file("usuarios.txt");

    file << users.size() << std::endl;
 
    for (Usuario *user : users) {
        file << user->getId() << std::endl;
        file << user->getNome() << std::endl;
        file << user->getEmail() << std::endl;
        file << user->getSenha() << std::endl;
    }
}

void Sistema::salvarServidores() {
    std::clog << "entrou no salvar servidores" << std::endl;

    vector<Servidor*> servers = servidores;
    
    ofstream file("servidores.txt");

    file << servers.size() << std::endl;

    for (Servidor *server : servers) {
        file << server->getUsuarioDonoId() << std::endl;
        file << server->getNome() << std::endl;
        file << server->getDescricao() << std::endl;
        file << server->getCodigoConvite() << std::endl;
        file << server->getParticipantesIds().size() << std::endl;

        for  (int id : server->getParticipantesIds())
            file << id << std::endl;

        file << server->getCanais().size() << std::endl;
        
        for (Canal *channel : server->getCanais()) {

            file << channel->getNome() << std::endl;

            if (channel->getTipo() == cte::texto)
                file << "TEXTO" << std::endl;
            else if (channel->getTipo() == cte::voz)
                file << "VOZ" << std::endl;

            file << channel->getMensagens().size() << std::endl;

            for (Mensagem *message : channel->getMensagens()) {
                file << message->getEnviadaPor() << std::endl;
                file << message->getDataHora() << std::endl;
                file << message->getConteudo() << std::endl;
            }
        }
    }

    // std::cout << "saiu do salvar servidores" << std::endl;
}

void Sistema::salvar() {
    try {
        salvarUsuarios();
        salvarServidores();
    } catch (std::exception &e) {
        cerr << "erro ao salvar: " << e.what() << std::endl;
        return;
    }
}

void Sistema::carregarUsuarios() {

    ifstream file("usuarios.txt");

    if (file.bad()) {
        std::clog << "arquivo de dados de usuários não encontrado. inicialização crua." << std::endl;
        return;
    }

    int howMany, id;
    string nome, email, senha;

    file >> howMany;

    while (howMany--) {
        file >> id;

        file.get();
        std::getline(file, nome);
        std::getline(file, email);
        std::getline(file, senha);

        usuarios.push_back(new Usuario(nome, email, senha));
    }
}

void Sistema::carregarServidores() {

    std::clog << "vai carregar os servidores" << std::endl;

    try {

        ifstream file("servidores.txt");
        ifstream previousFile("usuarios.txt");

        if (previousFile.bad() || file.bad()) {
            std::clog << "arquivo de dados não encontrados. inicialização crua." << std::endl;
            return;
        }

        int numberOfServers, ownerId, numberOfParticipants, participantId;
        int numberOfChannels;
        int numberOfMessages, messageOwnerId;

        string serverName, description, inviteCode;
        string channelName, channelType;
        string timestamp, content, trash;

        std::clog << "vai começar as leituras" << std::endl;

        file >> numberOfServers;
        file.get();
        
        while (numberOfServers--) {

            std::clog << "início de servidor" << std::endl;

            file >> ownerId; file.get();
            getline(file, serverName);
            getline(file, description);
            getline(file, inviteCode);

            Servidor *newServer = new Servidor(serverName, description, ownerId, inviteCode);

            std::clog << "criou servidor" << std::endl;
            std::clog << "nome: " << newServer->getNome() << std::endl;
            std::clog << "descricao: " << newServer->getDescricao() << std::endl;
            std::clog << "ownerId: " << newServer->getUsuarioDonoId() << std::endl;
            std::clog << "inviteCode: " << newServer->getCodigoConvite() << std::endl;
            std::clog << std::endl;

            file >> numberOfParticipants;
            while (numberOfParticipants--) {
                file >> participantId;
                newServer->addParticipant(participantId);
            }

            std::clog << "adicionou " << newServer->getParticipantesIds().size() << " participantes" << std::endl;

            // CHECKPOINT

            file >> numberOfChannels;
            while (numberOfChannels--) {

                std::clog << "início de canais" << std::endl;

                // file.ignore(numeric_limits<std::streamsize>::max(), '\n');
                // file.get();

                // while (!getline(file, channelName));
                // getline(file, channelName);

                getline(file, trash);

                if (!trash.empty())
                    channelName = trash;
                else
                    getline(file, channelName);

                
                getline(file, channelType);
                file >> numberOfMessages;

                std::clog << "trash: " << trash << std::endl;
                std::clog << "nome antes: *" << channelName << "*" << std::endl;
                std::clog << "tipo antes: " << channelType << std::endl;
                std::clog << "msgs antes: " << numberOfMessages << std::endl;
                std::clog << std::endl;

                Canal *newChannel;

                if (channelType == "TEXTO")
                    newChannel = new CanalTexto(channelName);
                else if (channelType == "VOZ")
                    newChannel = new CanalVoz(channelName);

                std::clog << "criou canal" << std::endl;
                std::clog << "nome: " << newChannel->getNome() << std::endl;
                std::clog << "tipo: " << newChannel->getTipo() << std::endl;
                std::clog << "número msg (deve ser 0): " << newChannel->getMensagens().size() << std::endl;

                // return;

                while (numberOfMessages-- > 0) {

                    std::clog << "início de mensagens" << std::endl;

                    file >> messageOwnerId;
                    file.get();
                    getline(file, timestamp);
                    getline(file, content);

                    std::clog << "ownerId: " << messageOwnerId << std::endl;
                    std::clog << "timestamp: " << timestamp << std::endl;
                    std::clog << "content: " << content << std::endl;

                    std::clog << "leu mensagens" << std::endl;

                    newChannel->addMessage(new Mensagem(messageOwnerId, content, timestamp));
                }

                std::cout << "vai adicionar canal" << std::endl;
                newServer->addCanal(newChannel);
            }

            std::cout << "vai adicionar servidor" << std::endl;
            addServer(newServer);
            std::cout << "vai inicializar com " << getAllServidores().size() << " servidores" << std::endl;
        }

    } catch (std::exception &e) {
        std::cerr << "erro ao tentar carregar servidores: " << e.what() << std::endl;
    }
}

void Sistema::carregar() {
    carregarUsuarios();
    carregarServidores();
}

void Sistema::start() {
    Parser* p = new Parser();

    try {
        std::string commandLine, nome, email, senha, desc, codigo, command, tipo, mensagem;
        bool changeCommand = false;
        int exit_flag = 0;

        while (!exit_flag) {
            getline(std::cin, commandLine);
            changeCommand = false;

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

                changeCommand = true;
                createUser(email, senha, nome);
            } else if (command == cte::LOGIN) {
                email = p->getSimpleArg(0);
                senha = p->getSimpleArg(1);

                login(email, senha);
            } else if (command == cte::DESCONECTAR) {
                disconnect();

            } else if (command == cte::CRIAR_SERVIDOR) {
                nome = p->getSimpleArg(0);

                changeCommand = true;
                createServer(nome);
            } else if (command == cte::LISTAR_SERVIDORES) {
                listServers();
            } else if (command == cte::MUDAR_DESCRICAO_SERVIDOR) {
                nome = p->getSimpleArg(0);
                desc = p->getSpacedArg();

                changeCommand = true;
                setServerDescription(nome, desc);
            } else if (command == cte::MUDAR_CONVITE_SERVIDOR) {
                nome = p->getSimpleArg(0);
                codigo = p->getSpacedArg();

                changeCommand = true;
                setInviteCode(nome, codigo);
            } else if (command == cte::REMOVER_SERVIDOR) {
                nome = p->getSimpleArg(0);

                changeCommand = true;
                removeServer(nome);
            } else if (command == cte::ENTRAR_SERVIDOR) {
                nome = p->getSimpleArg(0);
                codigo = p->getSpacedArg();

                changeCommand = true;
                enterServer(nome, codigo);
            } else if (command == cte::SAIR_SERVIDOR) {

                changeCommand = true;
                leaveServer();
            } else if (command == cte::LISTAR_PARTICIPANTES) {
                listParticipants();
            } else if (command == cte::LISTAR_CANAIS) {
                listChannels();
            } else if (command == cte::CRIAR_CANAL) {
                nome = p->getSimpleArg(0);
                tipo = p->getSimpleArg(1);

                changeCommand = true;
                createChannel(nome, tipo);

                std::clog << "criou o canal" << std::endl;
            } else if (command == cte::ENTRAR_CANAL) {
                nome = p->getSimpleArg(0);

                changeCommand = true;
                enterChannel(nome);
            } else if (command == cte::SAIR_CANAL) {
                leaveChannel();
            } else if (command == cte::ENVIAR_MENSAGEM) {
                mensagem = p->getSpacedArg();

                changeCommand = true;
                sendMessage(mensagem);
            } else if (command == cte::LISTAR_MENSAGENS) {

                listMessages();
            } else {

                std::cout << "comando não reconhecido" << std::endl;
            }

            // std::cout << "vai tentar salvar ao fim do comando" << std::endl;
            if (changeCommand) salvar();
            // std::cout << "salvou ao fim do comando" << std::endl;
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