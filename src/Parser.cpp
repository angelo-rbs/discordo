#ifndef PARSER_CPP
#define PARSER_CPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "constants.cpp"

class Parser
{

  private:
    std::string command;
    std::vector<std::string> args;

  public:
    bool parse(std::string entry)
    {

        if (entry.empty())
            return false;

        std::string word, blank;
        std::stringstream ss(entry);
        args.clear();

        try {
            if (ss >> word) {
                command = word;

                int argc = cte::findHowManyArgs(command);
                int itr = argc;

                while (itr > 0) {
                    if (ss >> word)
                        args.push_back(word);
                    else
                        logic_error(command + " espera " + to_string(argc) +
                                    " argumentos, mas recebeu " +
                                    to_string(argc - itr));

                    --itr;
                }

                if (command == "create-user") {

                    ss >> blank;

                    while (ss >> word)
                        blank += " " + word;

                    args.push_back(blank);
                }

                if (command != "create-user" && ss >> word)
                    throw logic_error(command + " espera apenas " +
                                      to_string(argc) + " argumentos");
            } else
                return false;

            return true;

        } catch (logic_error& e) {
            std::cerr << e.what() << std::endl;
            return false;
        }
    }

    void print()
    {

        std::cout << "comando: " << command << std::endl;
        std::cout << args.size() << " argumentos:";

        for (auto itr = args.begin(); itr < args.end(); itr++)
            std::cout << " " << *itr;

        std::cout << std::endl;
    }

    std::string getCommand() { return command; }

    std::string getArg(int pos)
    {
        if (pos >= args.size())
            throw runtime_error("posição do argumento inválida.");

        return args[pos];
    }
};

#endif