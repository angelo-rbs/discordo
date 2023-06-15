#include <iostream>
#include "Usuario.cpp"

int main() {

  Usuario *fstUser = new Usuario("angelo", "angeloblabla@hotmail.com", "cavaloatomico123");
  Usuario *sndUser = new Usuario("martinho davila", "123454321@gmail.com", "onodasuorelha");

  std::cout << fstUser->getNome() << ", " << fstUser->getEmail() << ", " << fstUser->getId() << ";" << std::endl;
  std::cout << sndUser->getNome() << ", " << sndUser->getEmail() << ", " << sndUser->getId() << ";" << std::endl;

}