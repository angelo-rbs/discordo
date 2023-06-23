
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "include/Constants.h"
#include "include/Parser.h"
#include "../infra/Exits.cpp"

int Parser::findHowManyArgs(std::string command) {
    for (auto pair : cte::commands_simple_args) {
        if (pair.first == command)
            return pair.second;
    }

    throw logic_error("comando \"" + command + "\" não encontrado!");
}

bool Parser::parse(std::string entry) {
    if (entry.empty())
        return false;

    std::string word;
    std::vector<std::string> tokens;
    std::stringstream ss(entry);
    int amountSimpleArgsByCommand = -1;
    args.clear();
    spacedArg.clear();

    try {
        
        // splita pelo delimitador ' '

        while (getline(ss, word, ' '))
            tokens.push_back(word);

        command = tokens.at(0);
        amountSimpleArgsByCommand = findHowManyArgs(command);

        if (tokens.size() - 1 < amountSimpleArgsByCommand)
            throw logic_error("espero mais argumentos");

        // coleta os argumentos simples (sem espaço interno)

        int i = 1;

        while (i < tokens.size() && i <= amountSimpleArgsByCommand) {
            args.push_back(tokens.at(i));
            ++i;
        }

        // opcionalmente coleta o argumento composto (com espaços internos

        word.clear();
        
        i = amountSimpleArgsByCommand + 1;
        if (i < tokens.size())
            word += tokens.at(i);

        ++i;
        while (i < tokens.size()) {
            word += (" " + tokens.at(i));
            ++i;
        }

        spacedArg = word;

        return true;

    } catch (early_exit& e) {
        std::cerr << e.msg << std::endl;
        return false;
    } catch (logic_error &e) {
        std::clog << e.what() << std::endl;
        return false;

    } catch (std::exception &e) {
        std::cerr << "erro no parsing: " << e.what() << std::endl;
        throw exception();
    }
}

void Parser::print() {
    std::cout << "comando: " << command << std::endl;
    std::cout << args.size() << " argumentos:";

    for (auto itr = args.begin(); itr < args.end(); itr++)
        std::cout << " " << *itr;

    std::cout << std::endl;
}

std::string Parser::getCommand() {
    return command;
}

std::string Parser::getSimpleArg(int pos) {
    if (pos >= args.size())
        throw runtime_error("posição do argumento inválida.");

    return args[pos];
}

std::string Parser::getSpacedArg() {
    return spacedArg;
}
