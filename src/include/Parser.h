#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>

class Parser {
   private:
    std::string command;
    std::vector<std::string> args;

   public:
   
    bool parse(std::string entry);
    void print();
    std::string getCommand();
    std::string getArg(int pos);
    int findHowManyArgs(std::string command);
    
};

#endif