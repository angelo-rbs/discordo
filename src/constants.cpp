
#include <iostream>
#include <vector>

using namespace std;

namespace cte {

  const string SAIR = "quit";
  const string CRIAR_USUARIO = "create-user";
  const string LOGIN = "login";
  const string DESCONECTAR = "disconnect";
  const string CRIAR_SERVIDOR = "create-server";
  const string MUDAR_DESCRICAO_SERVIDOR = "set-server-desc";
  const string MUDAR_CONVITE_SERVIDOR = "set-server-invite-code";
  const string LISTAR_SERVIDORES = "list-servers";
  const string REMOVER_SERVIDOR = "remove-server";
  const string ENTRAR_SERVIDOR = "enter-server";
  const string SAIR_SERVIDOR = "leave-server";
  const string LISTAR_PARTICIPANTES = "list-participants";
  const string LISTAR_CANAIS = "list-channels";
  const string CRIAR_CANAL = "create-channel";
  const string ENTRAR_CANAL = "enter-channel";
  const string SAIR_CANAL = "leave-channel";
  const string ENVIAR_MENSAGEM = "send-message";
  const string LISTAR_MENSAGENS = "list-messages";

  const int USUARIO_NAO_LOGADO = -1;
  const int SERVIDOR_INDEFINIDO = -1;
  const int CANAL_INDEFINIDO = -1;


  const vector<pair<string, int>> commands_args = {

      pair(SAIR, 0),
      pair(CRIAR_USUARIO, 2),
      pair(LOGIN, 2),
      pair(DESCONECTAR, 0),
      pair(CRIAR_SERVIDOR, 1),
      pair(MUDAR_DESCRICAO_SERVIDOR, 2),
      pair(MUDAR_CONVITE_SERVIDOR, 2),
      pair(LISTAR_SERVIDORES, 0),
      pair(REMOVER_SERVIDOR, 1),
      pair(ENTRAR_SERVIDOR, 1),
      pair(SAIR_SERVIDOR, 0),
      pair(LISTAR_PARTICIPANTES, 0),
      pair(LISTAR_CANAIS, 0),
      pair(CRIAR_CANAL, 2),
      pair(ENTRAR_CANAL, 1),
      pair(SAIR_CANAL, 0),
      pair(ENVIAR_MENSAGEM, 1),
      pair(LISTAR_MENSAGENS, 0)

  };

  int findHowManyArgs(string command) {
    for (auto pair : commands_args) {
      if (pair.first == command) return pair.second;
    }

    throw runtime_error("comando não encontrado!");
  }

}
