#include <iostream>
#include <exception>

#include "include/Sistema.h"
#include "include/Usuario.h"
#include "include/Mensagem.h"
#include "include/Constants.h"
#include "include/Parser.h"


int main()
{

  // TODO: entrada de lista de comandos externa

  try {
    
    Sistema *sistema = new Sistema();

    try {
      sistema->carregar();
    } catch (std::exception &e) {
      std::cerr << "erro ao tentar carregar dados na inicialização" << std::endl;
    }

    sistema->start();

    try {
      sistema->salvar();
    } catch (std::exception &e) {
      std::cerr << "erro ao salvar no encerramento" << e.what() << std::endl;
    }

    delete sistema;    

  } catch (exception &e) {
    std::cerr << "exceção capturada na main: " << e.what() << std::endl;
  }
}