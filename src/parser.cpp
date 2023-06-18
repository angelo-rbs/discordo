#ifndef PARSER_CPP
#define PARSER_CPP

#include <vector>
#include <iostream>
#include <sstream>
#include <string>

#include "constants.cpp"

class Parser {

  private:
    std::string command;
    std::vector<std::string> args;

  public:


    void parse(std::string entry) {

      if (entry.empty()) return;

      std::string word;
      std::stringstream ss(entry);
      args.clear();

      if (ss >> word) {
        command = word;

        int argc = cte::findHowManyArgs(command);
        int itr = argc;

        while (itr > 0) {
          if (ss >> word)
            args.push_back(word);
          else
            throw runtime_error(command + " espera " + to_string(argc) + " argumentos, mas recebeu " + to_string(argc - itr));

          --itr;
        }

        if (ss >> word)
          throw runtime_error(command + " espera apenas " + to_string(argc) + " argumentos");
      }
        
    }

    void print() {

      std::cout << "comando: " << command << std::endl;
      std::cout << args.size() << " argumentos:";

      for (auto itr = args.begin(); itr < args.end(); itr++)
        std::cout << " " << *itr;

      std::cout << std::endl;
    }

};


#endif