#include <iostream>
#include <exception>

#include "Sistema.cpp"
#include "Usuario.cpp"
#include "Mensagem.cpp"
#include "constants.cpp"
#include "Parser.cpp"

int main()
{

  try {
    
    Sistema *sistema = new Sistema();
    sistema->start();

    delete sistema;

  } catch (exception &e) {
    std::cerr << e.what() << std::endl;
  }
}