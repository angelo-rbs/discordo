#include <iostream>
#include "Usuario.cpp"
#include "Mensagem.cpp"
#include "constants.cpp"
#include "parser.cpp"

int main()
{

  // Mensagem *fst = new Mensagem("15/06/2023", 1, "oi tudo bem");
  // Mensagem *snd = new Mensagem("18/06/2025", 1, "tudo e com voce");

  // std::cout << fst->getDataHora() << ": " << fst->getConteudo() << ", enviada por " << fst->getEnviadaPor() << ";" << std::endl;
  // std::cout << snd->getDataHora() << ": " << snd->getConteudo() << ", enviada por " << snd->getEnviadaPor() << ";" << std::endl;

  // std::cout << (fst == snd) << std::endl;

  // delete fst;
  // delete snd;
  try {
    Parser *p = new Parser();
    std::string in;

    getline(std::cin, in);

    p->parse(in);
    p->print();

  } catch (exception &e) {
    std::cerr << e.what() << std::endl;
  }
}