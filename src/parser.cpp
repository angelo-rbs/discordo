#include <vector>
#include <iostream>
#include <string_view>
#include <sstream>

#include "constants.h"

class parser {

  private:
    static std::string command;
    static std::vector<std::string> args;

  public:

    void parse(std::string entry) {

      if (entry.empty()) return;

      std::string word;
      std::stringstream ss(entry);
      args.clear();

      if (ss >> word) {
        command = word;

        int argc = cte::findHowManyArgs(word);

        while (argc-- && ss >> word)
          args.push_back(word);

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
