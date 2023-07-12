#ifndef SISTEMA_H
#define SISTEMA_H

#include <exception>
#include <iostream>
#include <vector>

#include "Canal.h"
#include "Servidor.h"
#include "Usuario.h"


class Sistema {
   private:
    std::vector<Usuario*> usuarios;
    std::vector<Servidor*> servidores;
    static int idUsuarioLogado;
    static std::string nomeServidorAtual;
    static std::string nomeCanalAtual;
    std::string tipoToString(int);
    std::string formatMessage(Mensagem *msg);

   public:
    Sistema() = default;
    ~Sistema();

    std::vector<Usuario*> getAllUsuarios();
    std::vector<Servidor*> getAllServidores();
    int getIdUsuarioLogado();
    std::string getNomeServidorAtual();
    std::string getNomeCanalAtual();
    Canal* getCanalAtual();
    int incrementAndGetIdUsuarioLogado();
    int incrementAndGetServidorAtual();
    int incrementAndGetCanalAtual();

    Servidor* findServidor(std::string nome);
    Usuario* findUsuarioById(int id);
    Usuario* findUsuarioByLogin(std::string email, std::string senha);
    Usuario* findUsuarioByEmail(std::string email);
    Usuario* findUsuarioByServidor(std::string nomeServidor, int idUsuario);
    Canal* findCanal(std::string nome);
    Servidor* getServidorAtual();
    void addServer(Servidor *toAdd);

    bool logado();
    bool servidorDefinido();
    bool canalDefinido();

    bool isComandoDeBoot(std::string comando);

    // funcionalidesdes A1

    void start();
    void quit();
    bool createUser(std::string email, std::string senha, std::string nome);
    bool login(std::string email, std::string senha);

    // funcionalidades A2

    void disconnect();
    bool createServer(std::string nome);
    bool setServerDescription(std::string nome, std::string desc);
    bool setInviteCode(std::string nome, std::string newCode);
    void listServers();
    bool removeServer(std::string nome);
    bool enterServer(std::string serverName, std::string inviteCode);
    bool leaveServer();
    void listParticipants();

    // funcionalidades B1

    void listChannels();
    bool createChannel(std::string nome, std::string tipo);
    bool enterChannel(std::string nome);
    bool leaveChannel();

    // funcionalidades B2

    void sendMessage(std::string msg);
    void listMessages();

    // funcionalidades C1

    private:

    void salvarUsuarios();
    void salvarServidores();

    public:

    void salvar();

    // funcionalidades C2

    private:

    void carregarUsuarios();
    void carregarServidores();

    public:

    void carregar();

};

#endif