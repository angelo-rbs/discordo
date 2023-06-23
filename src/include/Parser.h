#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>

class Parser {
   private:
    std::string command;
    std::vector<std::string> args;
    std::string spacedArg;

   public:
   
    bool parse(std::string entry);
    void print();
    std::string getCommand();
    std::string getSimpleArg(int pos);
    std::string getSpacedArg();
    int findHowManyArgs(std::string command);
    
};

#endif