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
    sistema->start();

    delete sistema;    

  } catch (exception &e) {
    std::cerr << "exceção capturada na main: " << e.what() << std::endl;
  }
}