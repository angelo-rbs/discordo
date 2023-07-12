# discordo
Trabalho da 3ª unidade da disciplina Linguagem de Programação I, ministrada no curso de Bacharel em Tecnologia da Informação da UFRN Informação da Universidade Federal do Rio Grande do Norte 

# Identificação Pessoal

Preencha os dados abaixo para identificar a autoria do trabalho.

- Nome: Ângelo Raphael Campelo de Araújo Barbosa
- Email: angeloraphael1@hotmail.com
- Turma: Turma 01

# Compilação

Para compilar o programa deve-se, na pasta raiz, criar o Makefile através do software CMake segundo o comando

``cmake -S . -B build``,

que gerará um diretório **build** com os arquivos necessários e suficientes à compilação.
Dirija-se à pasta build e execute então 

``make``

e o programa será compilado num arquivo único nomeado Discordo. Para executá-lo no sistema operacional Linux siga com o comando

``./Discordo``.

O Discordo suporta todos as funcionalidades de manipulação de Usuario, Servidor, Canal e Mensagem sugeridos no documento de orientação do projeto segundo a sintaxe CLI sugerida, bem como identifica e adverte seu mau uso.

# Acompanhamento da implementação

## Classes base 

### Classes
- [X] Usuario
- [X] Mensagem
- [X] Canal 
- [X] CanalTexto
- [X] CanalVoz
- [X] Servidor
- [X] Sistema

### Funcionalidades (Parte 1)

**Se não estiver logado (Assim que entra no sistema)**

- [X] A1.1 - Sair do sistema
- [X] A1.2 - Criar usuário
- [X] A1.3 - Entrar no sistema

**Interações básicas com Servidores (Se estiver logado)**

- [X] A2.1 - Desconectar do Concorda
- [X] A2.2 - Criar servidores (nome)
- [X] A2.3 - Mudar a descrição do servidor
- [X] A2.4 - Setar código de convite para o servidor
- [X] A2.5 - Listar servidores
- [X] A2.6 - Remover servidor
- [X] A2.7 - Entrar em um servidor
- [X] A2.8 - Sair do servidor
- [X] A2.9 - Listar pessoas no servidor

### Funcionalidades (Parte 2)

**Gestão de canais**

- [X] B1.1 - Listar canais do servidor (de áudio ou texto)
- [X] B1.2 - Criar um canal do servidor 
- [X] B1.3 - Entrar em um canal
- [X] B1.4 - Sair do canal

**Gestão de mensagens**

- [X] B2.1 - Enviar mensagem para o canal
- [X] B2.2 - Visualizar mensagens do canal

### Funcionalidades (Parte 3)

- [X] Persistência dos dados em disco
- [X] Restauração dos dados do disco na inicialização do sistema


# Infra

- [X] Configurar CMake
- [X] Teste com Valgrind 

--------

