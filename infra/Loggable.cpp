#ifndef LOGGABLE_H
#define LOGGABLE_H

#include <iostream>

class Loggable {

  public: 

    virtual void log(std::string msg) {

      std::string dirtyName = typeid(*this).name();

      int pos = 0;
      while (pos < dirtyName.size() && isdigit(dirtyName.at(pos))) ++pos;
      std::string cleanName = dirtyName.substr(pos);

      std::clog << "[log::" << cleanName << "] " << msg << std::endl;
    }

    virtual void logInstanciamento() { 
      log("instanciamento de objeto"); 
    }

    virtual void logRemocao() { 
      log("remocao de entidade"); 
    }

    virtual void logAdicao(std::string msg) { 
      log("adição de entidade");
    }

    virtual void logEdicao(std::string msg) { 
      log("edição de entidade");
    }
};

#endif